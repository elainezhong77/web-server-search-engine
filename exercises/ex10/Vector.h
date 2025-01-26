// Copyright 2024 Elaine Zhong
// Elaine Zhong, ezhong4@uw.edu

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>

namespace vector333 {

// Vector object with x, y, and z coordinates to represent 3 dimensions
class Vector {
  public:
    // Invokes a Vector constructor
    Vector(const double x, const double y, const double z);
    // Default constructor
    Vector();
    // Copy constructor
    Vector(const Vector& copyme);
    // Destructor
    ~Vector();

    // Assignment operator for vectors
    Vector &operator=(const Vector &v);
    // Updates assignment for addition
    Vector &operator+=(const Vector &v);
    // Updates assignment for subtraction
    Vector &operator-=(const Vector &v);

    // Overloaded multiplication operator for dot product
    friend double operator*(const Vector &u, const Vector &v);
    // Overloaded multiplication operator for a double and vector
    friend Vector operator*(const Vector &v, const double k);
    // Overloaded multiplication operator for a double and vector
    friend Vector operator*(const double k, const Vector &v);

    // Overloaded stream output operator
    friend std::ostream &operator<<(std::ostream &out, const Vector &v);

  private:
    double *arr;  // Member variables
};

// Overloaded addition operator for vectors
Vector operator+(const Vector &u, const Vector &v);
// Overloaded subtraction operator for vectors
Vector operator-(const Vector &u, const Vector &v);

}  // namespace vector333

#endif  // _VECTOR_H_
