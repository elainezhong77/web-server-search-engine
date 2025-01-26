// Copyright 2024 Elaine Zhong
// Elaine Zhong, ezhong4@uw.edu

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "NthPrime.h"

int main(int argc,  char* argv[]) {
  printf("The 1st prime number is %" PRIu64 ".\n", NthPrime(1));
  printf("The 5th prime number is %" PRIu64 ".\n", NthPrime(5));
  printf("The 20th prime number is %" PRIu64 ".\n", NthPrime(20));
  return EXIT_SUCCESS;
}
