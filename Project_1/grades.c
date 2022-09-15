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

/* Function to perform Selection Sort to drop */
void selection_sort(int penalized_scores[], double weighted_scores[], int n)
{
    int i, j, min_idx;
    double tmp_double;
    int tmp_int;
 
    /* One by one move boundary of unsorted subarray */
    for (i = 0; i < n - 1; i++) {
 
        /* Find the minimum element in unsorted array */
        min_idx = i;
        for (j = i + 1; j < n; j++){
            if ((weighted_scores[j] < weighted_scores[min_idx]) ||
                (weighted_scores[j] == weighted_scores[min_idx] && j > min_idx)) {
                min_idx = j;
            }
        }
        /* Swap the found minimum element */
        /* with the first element */

        tmp_double = weighted_scores[min_idx];
        weighted_scores[min_idx] = weighted_scores[i];
        weighted_scores[i] = tmp_double;

        tmp_int = penalized_scores[min_idx];
        penalized_scores[min_idx] = penalized_scores[i];
        penalized_scores[i] = tmp_int;
    }
}

/* This function calculates numeric score */
double calculate_numeric_score(int penalized_scores[], double weighted_scores[], int weights[], int size, int x){
    double sum = 0.0;
    double adjusted_score = 0.0;
    int i;

    /* if no assignments are dropped */
    if (x == 0){
        for (i = 0; i < size; i++){
            adjusted_score = penalized_scores[i] * weights[i];
            sum += adjusted_score / 100;
        }
        return sum;
    }
    selection_sort(penalized_scores,weighted_scores, size);

    for (i = x; i < size; i++){
        sum += penalized_scores[i];
    }
    return sum / (size - x);
}
/* this function calculates mean */
double calculate_mean(int penalized_scores[], int size) {
    double sum = 0.0;
    int i;
    for (i = 0; i < size; i++) {
        sum += penalized_scores[i];
    }
    return sum / size;
}
/* This function calculates the standard deviation */
double calculate_standard_deviation(int penalized_scores[], double mean, int size) {
    double standard_deviation = 0.0;
    int i;
    for (i = 0; i < size; i++) {
        standard_deviation += pow(penalized_scores[i] - mean, 2);
    }

    return sqrt(standard_deviation / size);
}

/* read assignment info and return total weight */
int rw_read_assignment_info(int original_scores[], int weights[], int penalties[], double weighted_scores[], int penalized_scores[], int size, int p) {
    int total_weights = 0;
    int i;

    for (i = 0; i < size; i++) {
        int index;
        int score;
        int weight;
        int days_late;
        int penalized_score;

        scanf (" %d, %d, %d, %d", &index, &score, &weight, &days_late);

        total_weights += weight;
        original_scores[index - 1] = score;
        weights[index - 1] = weight;
        penalties[index - 1] = days_late;
        weighted_scores[index - 1] = (score * weight) / 100;
        penalized_score = score - (p * days_late);
        penalized_scores[index - 1] = penalized_score < 0 ? 0 : penalized_score;
    }

    return total_weights;
}
/* This function builds the generates the report */
void generate_report(char w, int p, int x, int original_scores[], int weights[], int penalties[], double numeric_score, double mean, double standard_devation, int size) {
    int j;

    printf("Numeric Score: %5.4f\n", numeric_score);
    printf("Points Penalty Per Day Late: %d\n", p);
    printf("Number of Assignments Dropped: %d\n", x);
    printf("Values Provided:\n");
    printf("Assignment, Score, Weight, Days Late\n");
    for (j = 0; j < size; j++) {
        printf("%d, %d, %d, %d\n", j+1, original_scores[j], weights[j], penalties[j]);
    }
    /* if user wants full report */
    if (w == 'Y' || w == 'y') {
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
    scanf (" %d %d %c", &p, &x, &w);

    /* this is reading the second line */
    scanf(" %d", &n);

    /* If number of assignments exceeds 50 */
    if (n > MAX_NUM_ASSIGNMENT) {
        n = MAX_NUM_ASSIGNMENT;
    }

    total_weights = rw_read_assignment_info(
        original_scores, 
        weights, 
        penalties,
        weighted_scores, 
        penalized_scores, 
        n,
        p
    );

    /* check if total weights match to 100*/
    if (total_weights != 100) {
        printf("ERROR: Invalid values provided.\n");
        return -1;
    }
    /* Functions are called in main */

    mean = calculate_mean(penalized_scores, n);

    standard_devation = calculate_standard_deviation(penalized_scores, mean, n);

    numeric_score = calculate_numeric_score(penalized_scores, weighted_scores, weights, n, x);


    generate_report(
        w, 
        p, 
        x, 
        original_scores, 
        weights, 
        penalties, 
        numeric_score, 
        mean, 
        standard_devation, 
        n
    );

    return 0;
}

