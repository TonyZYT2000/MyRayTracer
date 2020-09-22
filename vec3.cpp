#include "vec3.hpp"

#include <cmath>

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

vec3& vec3::operator+=(const vec3& v2) {
    v[0] += v2[0];
    v[1] += v2[1];
    v[3] += v2[3];
    return *this;
}
vec3& vec3::operator-=(const vec3& v2) {
    v[0] -= v2[0];
    v[1] -= v2[1];
    v[3] -= v2[3];
    return *this;
}
vec3& vec3::operator*=(const vec3& v2) {
    v[0] *= v2[0];
    v[1] *= v2[1];
    v[3] *= v2[3];
    return *this;
}
vec3& vec3::operator/=(const vec3& v2) {
    v[0] /= v2[0];
    v[1] /= v2[1];
    v[3] /= v2[3];
    return *this;
}
vec3& vec3::operator*=(const double t) {
    v[0] *= t;
    v[1] *= t;
    v[3] *= t;
    return *this;
}
vec3& vec3::operator/=(const double t) {
    v[0] /= t;
    v[1] /= t;
    v[3] /= t;
    return *this;
}

double vec3::squared_length() const {
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}
double vec3::length() const { return sqrt(squared_length()); }
void vec3::make_unit_vector() { *this /= length(); }

double dot(const vec3& v1, const vec3& v2) {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}
vec3 cross(const vec3& v1, const vec3& v2) {
    return vec3(v1[1] * v2[2] - v1[2] * v2[1], v1[2] * v2[0] - v1[0] * v2[2],
                v1[0] * v2[1] - v1[1] * v2[0]);
}
vec3 unit_vector(const vec3& v) { return v / v.length(); }
