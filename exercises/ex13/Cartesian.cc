// Copyright 2024 Elaine Zhong
// Elaine Zhong, ezhong4@uw.edu

#include <string>
#include "Cartesian.h"
#include <cmath>

using namespace std;

Cartesian::Cartesian(double x, double y) : x_(x), y_(y) {}

string Cartesian::ToString() const {
  return ("(" + to_string(x_) +", "+ to_string(y_)+")");
}

double Cartesian::Distance(const Cartesian &cart) const {
  double x_val = cart.x_ - x_;
  double y_val = cart.y_ - y_;
  return(sqrt((x_val * x_val) + (y_val * y_val)));
}
