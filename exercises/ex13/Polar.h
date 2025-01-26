// Copyright 2024 Elaine Zhong
// Elaine Zhong, ezhong4@uw.edu

#ifndef _POLAR_H_
#define _POLAR_H_

#include <string>
#include "Coordinate.h"

using namespace std;

// A Polar object represents a 2D polar coordinate
class Polar : public Coordinate {
 public:
  Polar(double, double);

  // ToString method 
  virtual string ToString() const;

  // Distance method
  double Distance(const Polar &coord) const;

 private:
  // Radius and angle
  double rad_;
  double ang_;
};

#endif  // _POLAR_H_
