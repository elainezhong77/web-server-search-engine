// Copyright 2024 Elaine Zhong
// Elaine Zhong, ezhong4@uw.edu

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

int main(int argc, char **argv) {
  // Allocate an integer on the heap, initialize to value 5.
  unique_ptr<int> x(new int(5));
  cout << "*x is: " << *x << endl;

  // Allocate a vector of integers on the heap, add some values to
  // that vector, sort the vector, print the values.
  unique_ptr<vector<int>> v (new vector<int>);
  v->push_back(13);
  v->push_back(42);
  v->push_back(17);
  sort(v->begin(), v->end());
  std::cout << "sorted v: ";
  for (int &el : *v) {
    cout << el << " ";
  }
  cout << endl;

  // Allocate a vector of (integer pointers) on the stack, add some
  // values to the vector from the heap, print the values.
  vector<unique_ptr<int>> v2;
  v2.push_back(unique_ptr<int> (new int(13)));
  v2.push_back(unique_ptr<int> (new int(42)));
  v2.push_back(unique_ptr<int> (new int(17)));
  cout << "unsorted v2: ";
  for (unique_ptr<int> &el : v2) {
    cout << *el << " ";
  }
  cout << endl;

  return EXIT_SUCCESS;
}