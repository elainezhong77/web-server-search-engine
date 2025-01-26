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
    Vector(const double x, const double y, const double z) : x_(x), y_(y), z_(z) {}
    // Default constructor
    Vector() : x_(0.0), y_(0.0), z_(0.0) {}
    // Copy constructor
    Vector(const Vector& copyme) : x_(copyme.x_), y_(copyme.y_), z_(copyme.z_) {}
    // Destructor
    ~Vector();

    // Gets x value
    double get_x() const { return x_; }
    // Gets y value
    double get_y() const { return y_; }
    // Gets z value
    double get_z() const { return z_; }

    // Assignment operator for vectors
    Vector &operator=(const Vector &v);
    // Updates assignment for addition
    Vector &operator+=(const Vector &v);
    // Updates assignment for subtraction
    Vector &operator-=(const Vector &v);

    // Overloaded addition operator for vectors
    friend Vector operator+(const Vector &u, const Vector &v);
    // Overloaded subtraction operator for vectors
    friend Vector operator-(const Vector &u, const Vector &v);

    // Overloaded multiplication operator for dot product
    friend double operator*(const Vector &u, const Vector &v);
    // Overloaded multiplication operators for a double and vector
    friend Vector operator*(const Vector &v, const double k);
    friend Vector operator*(const double k, const Vector &v);

    // Overloaded stream output operator 
    friend std::ostream &operator<<(std::ostream &out, const Vector &v);
    
  private:
    double x_, y_, z_; // Member variables

};

}  // namespace

#endif  // _VECTOR_H_
