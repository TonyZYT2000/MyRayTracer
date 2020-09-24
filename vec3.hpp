#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <iostream>

#include "rtweekend.hpp"

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

    // Random Generators
    static vec3 random();
    static vec3 random(double min, double max);
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
vec3 reflect(const vec3& v, const vec3& n) { return v - 2 * dot(v, n) * n; }
vec3 refract(const vec3& v, const vec3& n, double etai_over_etat) {
    vec3 r_out_perp = etai_over_etat * (v - dot(v, n) * n);
    vec3 r_out_parallel = -sqrt(v.squared_length() - r_out_perp.squared_length()) * n;
    return r_out_perp + r_out_parallel;
}

// Random Generators
vec3 vec3::random() {
    return vec3(random_double(), random_double(), random_double());
}
vec3 vec3::random(double min, double max) {
    return vec3(random_double(min, max), random_double(min, max),
                random_double(min, max));
}
vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1, 1);
        if (p.squared_length() >= 1) {
            continue;
        }
        return p;
    }
}
vec3 random_unit_vector() {
    // express in sphere coordinate to have true Lambertian distribution
    auto a = random_double(0, 2 * pi);
    auto z = random_double(-1, 1);
    auto r = sqrt(1 - z * z);
    return vec3(r * cos(a), r * sin(a), z);
}
vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) {
        return in_unit_sphere;
    } else {
        return -in_unit_sphere;
    }
}
vec3 random_in_unit_disk() {
    auto a = random_double(0, 2 * pi);
    auto r = random_double(-1, 1);

    return vec3(r * cos(a), r * sin(a), 0);
}

#endif
