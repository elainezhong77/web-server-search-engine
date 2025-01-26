// Copyright 2024 Elaine Zhong
// Elaine Zhong, ezhong4@uw.edu

#ifndef _CARTESIAN_H_
#define _CARTESIAN_H_

#include <string>
#include "Coordinate.h"

using namespace std;

// A Cartesian object represents a 2D cartesian coordinate
class Cartesian : public Coordinate {
 public:
  Cartesian(double, double);
  // ToString method
  virtual string ToString() const;

  // Distance method
  double Distance(const Cartesian &cart) const;

 private:
  double x_;
  double y_;
};

#endif  // _CARTESIAN_H_
