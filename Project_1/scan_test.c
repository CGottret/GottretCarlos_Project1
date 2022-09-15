#include <stdio.h>
#define MAX_NUM_ASSIGNMENT 50

int rw_read_assignment_info(int assignment_number[], int original_scores[], int weights[], int days_late[], int penalties[], double weighted_scores[], int size) {
    int total_weights = 0;
    int i;
    for (i = 0; i < size; i++) {

        scanf ("%d, %d, %d, %d", &assignment_number[i], &original_scores[i], &weights[i], &days_late[i]);

        total_weights += weights[i];
        penalties[i] = original_scores[i] - (10 * days_late[i]);
        weighted_scores[i] = original_scores[i] * weights[i];
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

    double numerice_score = 0.0;
    double mean = 0.0;
    double standard_devation = 0.0;
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

    /* penalized_scores for applying penalties to original score 
    int penalized_scores[MAX_NUM_ASSIGNMENT]; */

    /* weight for weight of assignment */
    int weights[MAX_NUM_ASSIGNMENT];

    /*index */
    int assignment_number[MAX_NUM_ASSIGNMENT];

    /* days late */
    int days_late[MAX_NUM_ASSIGNMENT];

    /* this is to check whether weights add up to 100 */
    int total_weights;

    /* penalties for numbers of days assignment was turn in late */
    int penalties[MAX_NUM_ASSIGNMENT];

    /* this is reading the first line */
    scanf (" %d %d %c", &p, &x, &w);

    /* this is reading the second line */
    scanf(" %d", &n);

    total_weights = rw_read_assignment_info(
        assignment_number,
        original_scores, 
        weights,
        days_late, 
        penalties,
        weighted_scores, 
        n);

/*
    for (i = 0; i < n; i++){
        printf("%d, %d, %d, %d \n", assignment_number[i], original_scores[i], weights[i], days_late[i]);
    }
    */
    generate_report( w, p, x, original_scores, weights, penalties, numerice_score, mean, standard_devation, n);
}

