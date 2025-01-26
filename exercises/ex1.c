// Copyright 2024 Elaine Zhong
// Elaine Zhong, ezhong4@uw.edu

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

void CopyAndSort(int64_t source[], int64_t dest[], int size);
void printArray(int64_t dest[], int size);

int main() {
    int64_t unsortedArray[12] = {3, 2, -5, 7, 17, 42, 6, 333, 7, 8, -8, 6};
    int64_t sortedArray[12];

    CopyAndSort(unsortedArray, sortedArray, 12);
    printArray(sortedArray, 12);
    return EXIT_SUCCESS;
}

// Copies and sorts values from a given array one by one using insertion sort 
void CopyAndSort(int64_t source[], int64_t dest[], int size) {
    for (int i = 0; i < size; i++) {
        int j = i;
        while (j > 0 && dest[j - 1] > source[i]) {
            dest[j] = dest[j - 1];
            j--;
        }
        dest[j] = source[i];
    }
}

// Print out each value in a given array
void printArray(int64_t dest[], int size) {
    for (int i = 0; i < size; i++) {
        printf(" %" PRId64, dest[i]);
    }
    printf("\n");
}
