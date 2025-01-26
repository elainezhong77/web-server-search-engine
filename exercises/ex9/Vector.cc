// Copyright 2024 Elaine Zhong
// Elaine Zhong, ezhong4@uw.edu

#include "Vector.h"

namespace vector333 {

Vector::~Vector() {}

Vector &Vector::operator=(const Vector &v) {
  if (this != &v) {
    this->x_ = v.x_;
    this->y_ = v.y_;
    this->z_ = v.z_;
  }
  return *this;
}

Vector &Vector::operator+=(const Vector &v) {
  if (this != &v) {
    this->x_ += v.x_;
    this->y_ += v.y_;
    this->z_ += v.z_;
  }
  return *this;
}

Vector &Vector::operator-=(const Vector &v) {
  if (this != &v) {
    this->x_ -= v.x_;
    this->y_ -= v.y_;
    this->z_ -= v.z_;
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
  temp += u.x_ * v.x_;
  temp += u.y_ * v.y_;
  temp += u.z_ * v.z_;
  return temp;
}

Vector operator*(const Vector &v, const double k) {
  Vector temp;
  temp.x_ += v.x_ * k;
  temp.y_ += v.y_ * k;
  temp.z_ += v.z_ * k;
  return temp;
}

Vector operator*(const double k, const Vector &v) {
  Vector temp;
  temp.x_ += v.x_ * k;
  temp.y_ += v.y_ * k;
  temp.z_ += v.z_ * k;
  return temp;
}

std::ostream &operator<<(std::ostream &out, const Vector &v) {
  return out << "(" << v.x_ << "," << v.y_ << "," << v.z_ << ")";
}

}
