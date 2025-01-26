// Copyright 2024 Elaine Zhong
// Elaine Zhong, ezhong4@uw.edu

#include <string>
#include "Polar.h"
#include <cmath>
# define PI 3.14159265358979

using namespace std;

Polar::Polar(double rad, double ang): rad_(rad), ang_(ang) {}

string Polar::ToString() const {
  return "(" + to_string(rad_) + ", " + to_string(ang_) + ")";
}

double Polar::Distance(const Polar &coord) const {
  double distance = pow(rad_, 2.0) + pow(coord.rad_, 2.0) - 2.0 * rad_ * coord.rad_ 
                    * cos((ang_ - coord.ang_) * PI / 180);
  return sqrt(distance);
}
