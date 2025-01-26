// Copyright 2024 Elaine Zhong
// Elaine Zhong, ezhong4@uw.edu

#include <iostream>
#include <sstream>
#include <string>
#include "Vector.h"

namespace vector333 {

Vector::Vector(const double x, const double y, const double z) {
    arr = new double[3];
    arr[0] = x;
    arr[1] = y;
    arr[2] = z;
  }

  Vector::Vector() {
    arr = new double[3];
    arr[0] = 0.0;
    arr[1] = 0.0;
    arr[2] = 0.0;
  }

  Vector::Vector(const Vector& copyme) {
    arr = new double[3];
    arr[0] = copyme.arr[0];
    arr[1] = copyme.arr[1];
    arr[2] = copyme.arr[2];
  }

  Vector::~Vector() {
    delete[] arr;
  }

Vector &Vector::operator=(const Vector &v) {
  if (this != &v) {
    arr[0] = v.arr[0];
    arr[1] = v.arr[1];
    arr[2] = v.arr[2];
  }
  return *this;
}

Vector &Vector::operator+=(const Vector &v) {
  if (this != &v) {
    arr[0] += v.arr[0];
    arr[1] += v.arr[1];
    arr[2] += v.arr[2];
  }
  return *this;
}

Vector &Vector::operator-=(const Vector &v) {
  if (this != &v) {
    arr[0] -= v.arr[0];
    arr[1] -= v.arr[1];
    arr[2] -= v.arr[2];
  }
  return *this;
}

Vector operator+(const Vector &u, const Vector &v) {
  Vector temp = u;
  temp += v;
  return temp;
}

Vector operator-(const Vector &u, const Vector &v) {
  Vector temp = u;
  temp -= v;
  return temp;
}

double operator*(const Vector &u, const Vector &v) {
  double temp = 0.0;
  temp += u.arr[0] * v.arr[0];
  temp += u.arr[1] * v.arr[1];
  temp += u.arr[2] * v.arr[2];
  return temp;
}

Vector operator*(const Vector &v, const double k) {
  Vector temp;
  temp.arr[0] += v.arr[0] * k;
  temp.arr[1] += v.arr[1] * k;
  temp.arr[2] += v.arr[2] * k;
  return temp;
}

Vector operator*(const double k, const Vector &v) {
  Vector temp;
  temp.arr[0] += v.arr[0] * k;
  temp.arr[1] += v.arr[1] * k;
  temp.arr[2] += v.arr[2] * k;
  return temp;
}

std::ostream &operator<<(std::ostream &out, const Vector &v) {
  out << "(" << v.arr[0] << "," << v.arr[1] << "," << v.arr[2] << ")";
  return out;
}

}  // namespace vector333
