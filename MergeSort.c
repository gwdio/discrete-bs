#include <stdio.h>
#include <stdlib.h>
#include "MergeSort.h"

void split(int arr[], int len, int **a, int *lenA, int **b, int *lenB);
int* zip(int a[], int lenA, int b[], int lenB);

void dsMergeSort(int arr[], int len) {
    if (len <= 1) {
        return;
    }

    int *a, *b;
    int lenA, lenB;

    // Split array into two halves
    split(arr, len, &a, &lenA, &b, &lenB);

    // Sort both halves
    dsMergeSort(a, lenA);
    dsMergeSort(b, lenB);

    // Merge sorted halves back into arr
    int *sorted = zip(a, lenA, b, lenB);
    for (int i = 0; i < len; i++) {
        arr[i] = sorted[i];
    }

    // Free memory
    free(a);
    free(b);
    free(sorted);
}

void split(int arr[], int len, int **a, int *lenA, int **b, int *lenB) {
    *lenA = len / 2;
    *lenB = len - *lenA;

    // allocate memory for the output arrays
    *a = malloc(*lenA * sizeof(int));
    *b = malloc(*lenB * sizeof(int));

    for (int i = 0; i < *lenA; i++) {
        (*a)[i] = arr[i];
    }
    for (int i = 0; i < *lenB; i++) {
        (*b)[i] = arr[*lenA + i];
    }
}

int* zip(int a[], int lenA, int b[], int lenB) {
    int *sorted = malloc((lenA + lenB) * sizeof(int));
    int indexA = 0, indexB = 0, index = 0;

    // Compare both heads and add smaller element
    while (indexA < lenA && indexB < lenB) {
        if (a[indexA] <= b[indexB]) {
            sorted[index++] = a[indexA++];
        } else {
            sorted[index++] = b[indexB++];
        }
    }

    // Copy remaining
    while (indexA < lenA) {
        sorted[index++] = a[indexA++];
    }
    while (indexB < lenB) {
        sorted[index++] = b[indexB++];
    }

    return sorted;
}