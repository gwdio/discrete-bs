#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "MergeSort.h" // Include MergeSort algorithm found in MergeSort.c

int* makeRandom(int size);
int* makeIncreasing(int size);
int* makeDecreasing(int size);
void noiseify(int *data, int size);

#define DATATYPE 'I'
#define MAXELEMENTS 10000000 // Set to 10 million to Hopefully Generate nlogn trend
#define TRIALS 200
#define EXTRA_RUNS 5
FILE *trialData;

int main(int argc, char* argv[])
{
    srand((unsigned int) time(NULL)); // Seed random number generator
    trialData = fopen("sortdata.csv", "w"); // Open CSV file for output
    if (trialData == NULL) {
        perror("Unable to open sortdata.csv");
        return 1;
    }

    fprintf(trialData, "Size,Time_ms\n"); // Write CSV header

    int* list;
    double times[TRIALS + EXTRA_RUNS]; // Array to store run times for trimming
    int sizes[TRIALS + EXTRA_RUNS]; // Array to store sizes of each list

    for (int i = 0; i < TRIALS + EXTRA_RUNS; i++) {
        int size = (rand() % MAXELEMENTS) + 1; // Generate a random size up to MAXELEMENTS
        sizes[i] = size; // Store the actual size for CSV output
        
        // Generate the list based on the datatype
        switch (DATATYPE) {
            case 'R':
                list = makeRandom(size);
                break;
            case 'I':
                list = makeIncreasing(size);
                break;
            case 'D':
                list = makeDecreasing(size);
                break;
            default:
                fprintf(stderr, "Invalid DATATYPE\n");
                exit(1);
        }

        struct timeval start, end;
        gettimeofday(&start, NULL);

        // Sort the list
        dsMergeSort(list, size);

        gettimeofday(&end, NULL);

        // Calculate elapsed time in milliseconds
        double milliseconds = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
        times[i] = milliseconds; // Store this run time

        free(list); // Free memory for the list
    }

    // Write the trimmed results to CSV (skip the first 10 times)
    for (int i = EXTRA_RUNS; i < TRIALS + EXTRA_RUNS; i++) {
        fprintf(trialData, "%d,%.3f\n", sizes[i], times[i]);
    }

    fclose(trialData); // Close the CSV file
    return 0;
}

int* makeRandom(int size) {
    int *data = (int*) malloc(size * sizeof(int));
    if (data != NULL) {
        noiseify(data, size);
    }
    return data;
}

void noiseify(int *data, int size) {
    for (int i = 0; i < size; i++) {
        data[i] = rand();
    }
}

int* makeIncreasing(int size) {
    int *data = (int*) malloc(size * sizeof(int));
    if (data != NULL) {
        for (int i = 0; i < size; i++) {
            data[i] = i;
        }
    }
    return data;
}

int* makeDecreasing(int size) {
    int *data = (int*) malloc(size * sizeof(int));
    if (data != NULL) {
        for (int i = 0; i < size; i++) {
            data[i] = size - i;
        }
    }
    return data;
}
