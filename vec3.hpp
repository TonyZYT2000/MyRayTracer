#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <iostream>

class vec3 {
  private:
    double v[3];

  public:
    // Constructors
    vec3() : v{0, 0, 0} {}
    vec3(double vec0, double vec1, double vec2) : v{vec0, vec1, vec2} {}

    // Getters
    double x() const { return v[0]; }
    double y() const { return v[1]; }
    double z() const { return v[2]; }

    // Unary Operators
    double& operator[](int i) { return v[i]; }
    double operator[](int i) const { return v[i]; }
    vec3 operator+() const { return vec3(v[0], v[1], v[2]); }
    vec3 operator-() const { return vec3(-v[0], -v[1], -v[2]); }

    // Arithmetic Operators
    vec3 operator+(const vec3& v2) const;
    vec3 operator-(const vec3& v2) const;
    vec3 operator*(const vec3& v2) const;
    vec3 operator/(const vec3& v2) const;
    vec3 operator*(const double t) const;
    vec3 operator/(const double t) const;

    // Arithmetic Assignment Operators
    vec3& operator+=(const vec3& v2);
    vec3& operator-=(const vec3& v2);
    vec3& operator*=(const vec3& v2);
    vec3& operator/=(const vec3& v2);
    vec3& operator*=(const double t);
    vec3& operator/=(const double t);

    // Member Utility Functions
    double length() const;
    double squared_length() const;
    void make_unit_vector();
};

// Arithmetic Operators
vec3 vec3::operator+(const vec3& v2) const {
    return vec3(v[0] + v2[0], v[1] + v2[1], v[2] + v2[2]);
}
vec3 vec3::operator-(const vec3& v2) const {
    return vec3(v[0] - v2[0], v[1] - v2[1], v[2] - v2[2]);
}
vec3 vec3::operator*(const vec3& v2) const {
    return vec3(v[0] * v2[0], v[1] * v2[1], v[2] * v2[2]);
}
vec3 vec3::operator/(const vec3& v2) const {
    return vec3(v[0] / v2[0], v[1] / v2[1], v[2] / v2[2]);
}
vec3 vec3::operator*(const double t) const {
    return vec3(v[0] * t, v[1] * t, v[2] * t);
}
vec3 vec3::operator/(const double t) const {
    return vec3(v[0] / t, v[1] / t, v[2] / t);
}

// Arithmetic Assignment Operators
vec3& vec3::operator+=(const vec3& v2) {
    v[0] += v2[0];
    v[1] += v2[1];
    v[2] += v2[2];
    return *this;
}
vec3& vec3::operator-=(const vec3& v2) {
    v[0] -= v2[0];
    v[1] -= v2[1];
    v[2] -= v2[2];
    return *this;
}
vec3& vec3::operator*=(const vec3& v2) {
    v[0] *= v2[0];
    v[1] *= v2[1];
    v[2] *= v2[2];
    return *this;
}
vec3& vec3::operator/=(const vec3& v2) {
    v[0] /= v2[0];
    v[1] /= v2[1];
    v[2] /= v2[2];
    return *this;
}
vec3& vec3::operator*=(const double t) {
    v[0] *= t;
    v[1] *= t;
    v[2] *= t;
    return *this;
}
vec3& vec3::operator/=(const double t) {
    v[0] /= t;
    v[1] /= t;
    v[2] /= t;
    return *this;
}

// Member Utility Functions
double vec3::squared_length() const {
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}
double vec3::length() const { return sqrt(squared_length()); }
void vec3::make_unit_vector() { *this /= length(); }

// Type Aliases
using point3 = vec3;
using color3 = vec3;

// More Operators
std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}
vec3 operator*(double t, const vec3& v) { return v * t; }

// More Utility Functions
double dot(const vec3& v1, const vec3& v2) {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}
vec3 cross(const vec3& v1, const vec3& v2) {
    return vec3(v1[1] * v2[2] - v1[2] * v2[1], v1[2] * v2[0] - v1[0] * v2[2],
                v1[0] * v2[1] - v1[1] * v2[0]);
}
vec3 unit_vector(const vec3& v) { return v / v.length(); }

#endif
