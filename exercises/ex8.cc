// Copyright 2024 Elaine Zhong
// Elaine Zhong, ezhong4@uw.edu

#include <iostream>
#include <cstdlib>
using namespace std;

// Prints the factors of a given integer
void PrintFactors(int num);

// Prints the factors of a positive integer
int main(int argc, char** argv) {
  int num;
  cout << "Which positive integer would you like me to factorize? ";
  // Checks if input is not a number or is not positive
  if (!(cin >> num) || num <= 0) {
    cout << "Must enter a positive integer." << endl;
    return EXIT_FAILURE;
  }
  PrintFactors(num);
  return EXIT_SUCCESS;
}

void PrintFactors(int num) {
  for (int i = 1; i <= num; i++) {
    if (num % i == 0) {
      cout << i << " ";
    }
  }
  cout << endl;
}
