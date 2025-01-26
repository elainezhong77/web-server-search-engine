// Copyright 2024 Elaine Zhong
// Elaine Zhong, ezhong4@uw.edu

#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

// Reads input value and detects conversion/unexpected EOF conditions
template <class T> T ReadValue(istream& in);

// Reads and sorts 6 doubles
int main() {
  cout << "Enter 6 doubles:" << endl;
  double curr;
  vector<double> vec;
  for (int i = 0; i < 6; i++) {
    curr = ReadValue<double>(cin);
    vec.push_back(curr);
  }
  sort(vec.begin(), vec.end());
  cout << "Your sorted doubles are:" << endl;
  for (int i = 0; i < 6; i++) {
    cout <<vec[i] << endl;
  }
  return EXIT_SUCCESS;
}

template <class T> T ReadValue(istream& in) {
  // declare value of type T
  T value;
  // extract from istream and store in value
  if (in >> value) {
    in.clear();
    return value;
  }

  if (in.eof()) {
    cerr << "End of file reached." << endl;
    exit(EXIT_FAILURE);
  } else {
    cerr << "Invalid input. Must enter 6 doubles." << endl;
    exit(EXIT_FAILURE);
  }
}
