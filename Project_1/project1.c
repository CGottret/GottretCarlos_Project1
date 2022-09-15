/*
Name: Carlos Mauricio Gottret Murillo
U_ID: 115297371
Directory ID: cgottret
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAX_NUM_ASSIGNMENT 50

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void swap_double(double* xp, double* yp)
{
    double temp = *xp;
    *xp = *yp;
    *yp = temp;
}
/* Function to perform Selection Sort to drop */
void selection_sort(int penalized_scores[], double weighted_scores[], int n)
{
    int i, j, min_idx;
 
    /* One by one move boundary of unsorted subarray */
    for (i = 0; i < n - 1; i++) {
 
        /* Find the minimum element in unsorted array */
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (weighted_scores[j] < weighted_scores[min_idx])
                min_idx = j;
 
        /* Swap the found minimum element */
        /* with the first element */
        swap_double(&weighted_scores[min_idx], &weighted_scores[i]);
        swap(&penalized_scores[min_idx], &penalized_scores[i]);
    }
}

double calculate_numeric_score(int penalized_scores[], double weighted_scores[], int size, int x){
    int sum = 0;
    int i;
    selection_sort(penalized_scores,weighted_scores, size);
    for (i = x; i < size; i++){
        sum += penalized_scores[i];
    }
    return sum / (size - x);
}
double calculate_mean(int penalized_scores[], int size) {
    double sum = 0.0;
    int i;
    for (i = 0; i < size; i++) {
        sum += penalized_scores[i];
    }
    return sum / size;
}

double calculate_standard_deviation(int penalized_scores[], double mean, int size) {
    double standard_deviation = 0.0;
    int i;
    for (i = 0; i < size; i++) {
        standard_deviation += pow(penalized_scores[i] - mean, 2);
    }

    return sqrt(standard_deviation / size);
}

/* read assignment info and return total weight */
int rw_read_assignment_info(int original_scores[], int weights[], int penalties[], double weighted_scores[], int penalized_scores[], int size) {
    int total_weights = 0;
    int i;
    for (i = 0; i < size; i++) {
        int index;
        int score;
        int weight;
        int days_late;
        int penalized_score;

        scanf ("%d, %d, %d, %d", &index, &score, &weight, &days_late);

        total_weights += weight;
        original_scores[index] = score;
        weights[index] = weight;
        penalties[index] = days_late;
        weighted_scores[index] = score * weight;
        penalized_score = score - 10 * days_late;
        penalized_scores[index] = penalized_score < 0 ? 0 : penalized_score;
    }
    return total_weights;
}

void generate_report(char w, int p, int x, int original_scores[], int weights[], int penalties[], double numerice_score, double mean, double standard_devation, int size) {
    int j;
    if (w == 'Y' || w == 'y') {
        printf("Numeric Score: %5.4f\n", numerice_score);
        printf("Points Penalty Per Day Late: %d\n", p);
        printf("Number of Assignments Dropped: %d\n", x);
        printf("Values Provided:\n");
        printf("Assignment, Score, Weight, Days Late\n");
        for (j = 0; j < size; j++) {
            printf("%d, %d, %d, %d\n", j+1, original_scores[j], weights[j], penalties[j]);
        }
        printf("Mean: %5.4f, Standard Deviation: %5.4f \n", mean, standard_devation);
    }
}

int main() {
    /* p for penalty */
    int p;
    /* x for num assignments dropped */
    int x;
    /* w whether we want stat info */
    char w;
    /* n for num of assignments */
    int n;
    /* original_scores for original score */
    int original_scores[MAX_NUM_ASSIGNMENT];

    /* weighted_scores for applying weight to original score */
    double weighted_scores[MAX_NUM_ASSIGNMENT];

    /* penalized_scores for applying penalties to original score */
    int penalized_scores[MAX_NUM_ASSIGNMENT];

    /* weight for weight of assignment */
    int weights[MAX_NUM_ASSIGNMENT];

    /* this is to check whether weights add up to 100 */
    int total_weights;

    /* penalties for numbers of days assignment was turn in late */
    int penalties[MAX_NUM_ASSIGNMENT];

    /* numeric score */
    double numeric_score;

    /* means */
    double mean;

    /* standard deviation */
    double standard_devation;

    /* this is reading the first line */
    scanf ("%d %d %c", &p, &x, &w);

    /* this is reading the second line */
    scanf("%d", &n);

    if (n > MAX_NUM_ASSIGNMENT) {
        n = MAX_NUM_ASSIGNMENT;
    }

    total_weights = rw_read_assignment_info(
        original_scores, 
        weights, 
        penalties,
        weighted_scores, 
        penalized_scores, 
        n
    );

    /* check if total weights match to 100*/
    if (total_weights != 100) {
        printf("ERROR: Invalid values provided.\n");
        return -1;
    }

    mean = calculate_mean(penalized_scores, n);


    standard_devation = calculate_standard_deviation(penalized_scores, mean, n);

    numeric_score = calculate_numeric_score(penalized_scores, weighted_scores, n, x);


    generate_report(
        w, 
        p, 
        x, 
        original_scores, 
        weights, 
        penalized_scores, 
        numeric_score, 
        mean, 
        standard_devation, 
        n
    );

    return 0;
}

