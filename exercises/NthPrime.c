// Copyright 2024 Elaine Zhong
// Elaine Zhong, ezhong4@uw.edu

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>

#include "NthPrime.h"
#define FIRST_PRIME 2

// Checks if factor is a factor of number.
bool IsFactor(int64_t number, int64_t factor);
// Checks if a number is prime.
bool IsPrime(int64_t number);

int64_t NthPrime(int16_t number) {
  if (number < 1) {
    printf("Must enter a positive integer.\n");
    exit(EXIT_FAILURE);
  }
  int curr_num = FIRST_PRIME;
  int primeCount = 0;
  while (curr_num < UINT_MAX) {
    if (IsPrime(curr_num)) {
      primeCount++;
      if (primeCount == number) {
        return curr_num;
      }
    }
    curr_num++;
  }
  printf("This number is too large. Try a smaller positive integer.\n");
  exit(EXIT_FAILURE);
}

bool IsFactor(int64_t number, int64_t factor) {
  if (number % factor == 0) {
    return true;
  }
  return false;
}

bool IsPrime(int64_t number) {
  for (int n = FIRST_PRIME; n < number; n++) {
    if (IsFactor(number, n)) {
      return false;
    }
  }
  return true;
}
