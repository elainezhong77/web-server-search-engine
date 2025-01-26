// Copyright 2024 Elaine Zhong
// Elaine Zhong, ezhong4@uw.edu

#include <iostream>
#include "Vector.h"
using namespace vector333;
using namespace std;

int main(int argc, char** argv) {
  // Test default constructor
  Vector v;
  if (!(v.get_x() == 0.0 && v.get_y() == 0.0 && v.get_z() == 0.0)) {
    cout << "Default constructor failed." << endl;
    return EXIT_FAILURE;
  }

  // Test x, y, z parameter constructor 
  Vector v1(1, 2, 3);
  if (!(v1.get_x() == 1.0 && v1.get_y() == 2.0 && v1.get_z() == 3.0)) {
  cout << "Constructor failed." << endl;
  return EXIT_FAILURE;
  }

  // Test copy constructor
  Vector copy = v1;
  if (!(copy.get_x() == 1.0 && copy.get_y() == 2.0 && copy.get_z() == 3.0)) {
    cout << "Constructor failed." << endl;
    return EXIT_FAILURE;
  }

  // Test +=
  Vector v2(1, 1, 1);
  Vector temp;
  temp += v2;
  if (!(temp.get_x() == 1.0 && temp.get_y() == 1.0 && temp.get_z() == 1.0)) {
    cout << "+= failed." << endl;
    return EXIT_FAILURE;
  }

  // Test -=
  Vector temp2;
  temp2 -= v2;
  if (!(temp2.get_x() == -1.0 && temp2.get_y() == -1.0 && temp2.get_z() == -1.0)) {
    cout << "-= failed." << endl;
    return EXIT_FAILURE;
  }

  // Test + 
  Vector sum;
  sum = v1 + v2;
  if (!(sum.get_x() == 2.0 && sum.get_y() == 3.0 && sum.get_z() == 4.0)) {
    cout << "+ failed." << endl;
    return EXIT_FAILURE;
  }
  cout << v1 << " + " << v2 << " = " << sum << endl;

  // Test -
  Vector diff;
  diff = v1 - v2;
  if (!(diff.get_x() == 0.0 && diff.get_y() == 1.0 && diff.get_z() == 2.0)) {
    cout << "- failed." << endl;
    return EXIT_FAILURE;
  }
  cout << v1 << " - " << v2 << " = " << diff << endl;
  
  // Test * dot product
  double product;
  product = v1 * v2;
  if (product != 6) {
    cout << "dot product failed." << endl;
    return EXIT_FAILURE;
  }
  cout << v1 << " * " << v2 << " = " << product << endl;
  

  // Test * vector and double
  Vector product2;
  product2 = v1 * 2;
  if (!(product2.get_x() == 2.0 && product2.get_y() == 4.0 && product2.get_z() == 6.0)) {
    cout << "vector and double product failed." << endl;
    return EXIT_FAILURE;
  }
  cout << v1 << " * " << 2 << " = " << product2 << endl;

  // Test * double and vector
  Vector product3;
  product3 = 2 * v1;
  if (!(product3.get_x() == 2.0 && product3.get_y() == 4.0 && product3.get_z() == 6.0)) {
    cout << "double and vector product failed." << endl;
    return EXIT_FAILURE;
  }
  cout << 2 << " * " << v1 << " = " << product3 << endl;

  cout << "All tests passed." << endl;
  return EXIT_SUCCESS;
}
