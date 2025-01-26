// Copyright 2024 Elaine Zhong
// Elaine Zhong, ezhong4@uw.edu

#ifndef _COORDINATE_H_
#define _COORDINATE_H_

#include <string>

using namespace std;

// A Coordinate object represents an abstract 2D coordinate
class Coordinate {
 public:
  // ToString method
  virtual string ToString() const = 0;
};

#endif  // _COORDINATE_H_
