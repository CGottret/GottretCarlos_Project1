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

double calculate_mean(int penalized_scores[], int size) {
    double sum;
    for (int i = 0; i < size; i++) {
        sum += penalized_scores[i];
    }
    return sum / size;
}

double calculate_standard_deviation(int penalized_scores[], double mean, int size) {
    double standard_deviation;
    for (int i = 0; i < size; i++) {
        standard_deviation += pow(penalized_scores[i] - mean, 2);
    }

    return sqrt(standard_deviation / size);
}

/* read assignment info and return total weight */
int rw_read_assignment_info(FILE *fptr, int original_scores[], int weights[], int penalties[], int weighted_scores[], int penalized_scores[], int size) {
    char line[52];
    int total_weights, i, j;
    for (i = 0; i < size; i++) {
        char *line_arr[4];
        char delim[] = ", ";
        char *ptr;
        int index;
        int score;
        int weight;
        int days_late;
        int penalized_score;

        fgets (line, 20, fptr);
        ptr = strtok(line, delim);

        while (ptr != NULL) {
            line_arr[j] = ptr;
            ptr = strtok(NULL, delim);
            j++;
        }
        /* this is to reset the index of line_arr */
        j = 0;

        index = atoi(line_arr[0]) - 1;
        score = atoi(line_arr[1]);
        weight = atoi(line_arr[2]);
        total_weights += weight;
        days_late = atoi(line_arr[3]);
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
    if (w == 'Y' || w == 'y') {
        printf("Numeric Score: %5.4f\n", numerice_score);
        printf("Points Penalty Per Day Late: %d\n", p);
        printf("Number of Assignments Dropped: %d\n", x);
        printf("Values Provided:\n");
        printf("Assignment, Score, Weight, Days Late\n");
        for (int j = 0; j < size; j++) {
            printf("%d, %d, %d, %d\n", j+1, original_scores[j], weights[j], penalties[j]);
        }
        printf("Mean: %5.4f, Standard Deviation: %5.4f \n", mean, standard_devation);
    }
}

int main() {
    FILE *fptr;
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
    int weighted_scores[MAX_NUM_ASSIGNMENT];

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

    char line[1];
    fptr = fopen("file.txt","r");

    /* this is reading the first line */
    fgets(line, 10, fptr);
    sscanf (line, "%d %d %c", &p, &x, &w);

    /* this is reading the second line */
    fgets (line, 10, fptr);
    sscanf(line, "%d", &n);

    if (n > MAX_NUM_ASSIGNMENT) {
        n = MAX_NUM_ASSIGNMENT;
    }

    total_weights = rw_read_assignment_info(
        fptr, 
        original_scores, 
        weights, 
        penalties,
        weighted_scores, 
        penalized_scores, 
        n
    );

    // check if total weights match to 100
    if (total_weights != 100) {
        printf("ERROR: Invalid values provided.\n");
        return -1;
    }

    // get means
    mean = calculate_mean(penalized_scores, n);

    // get standard deviation
    standard_devation = calculate_standard_deviation(penalized_scores, mean, n);

    // generate report
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

