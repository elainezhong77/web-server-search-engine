// Copyright 2024 Elaine Zhong
// Elaine Zhong, ezhong4@uw.edu

#include <iostream>
#include "Cartesian.h"
#include "Polar.h"
#define PI 3.14159265358979

using namespace std;   

int main() {
  Cartesian c1(1.0,2.0);
  Cartesian c2(1.0,7.0);
  double cart_distance = c1.Distance(c2);
  cout << "Cartesian coordinate 1: " << c1.ToString() << endl;
  cout << "Cartesian coordinate 2: " << c2.ToString() << endl;
  cout << "Distance between Cartesian coordinates: " << cart_distance << endl;

  Polar p1(3.0, 4.0);
  Polar p2(0.0, 4.0);
  double polar_distance = p1.Distance(p2);
  cout << "Polar coordinate 1: " << p1.ToString() << endl;
  cout << "Polar coordinate 2: " << p2.ToString() << endl;
  cout << "Distance between Polar coordinates: " << polar_distance << endl;

  return EXIT_SUCCESS;
}