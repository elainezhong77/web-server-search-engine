// Elaine Zhong, ezhong4@uw.edu

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int checkValidInput(char[]);
double estimatePiTerm(int);

int main (int argc, char* argv[]) {
    // Exit if there are more than two arguments
    if (argc != 2) {
        printf("Must input 2 arguments.\n");
        exit(EXIT_FAILURE);
    }
    int n = checkValidInput(argv[1]);
    double result = 3.0;
    for (int i = 1; i <= n; i++) {
        result += estimatePiTerm(i);
    }
    printf("Our estimate of Pi is %0.20f\n", result);
    return EXIT_SUCCESS;
}

int checkValidInput(char input[]) {
    // Exit if the input too large
    long longInput = strtol(input, NULL, 0);
    if (longInput > INT_MAX) {
        printf("The input value is too large.\n");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (input[i] != 0) {
        // Exit in case the input is larger than a long
        if (i > 9) {
            printf("The input value is too large.\n");
            exit(EXIT_FAILURE);
        }
        // Exit if input contains non-digits
        if (input[i] > '9' || input[i] < '0') {
            printf("Must input a positive integer.\n");
            exit(EXIT_FAILURE);
        }
        i++;    
    }
    return atoi(input);
}

double estimatePiTerm(int term) {
    double nOne = 2.0 * term;  
    double nTwo = (2.0 * term) + 1;
    double nThree = (2.0 * term) + 2;
    double currTerm = 4.0 / ((nOne * nTwo * nThree));
    if (term % 2 == 0) {
        currTerm *= -1;
    }
    return currTerm;
}