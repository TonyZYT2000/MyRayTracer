#ifndef RTWEEKEND_HPP
#define RTWEEKEND_HPP

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// Using
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
double degrees_to_radius(double degrees) {
    return degrees * pi / 180.0;
}

// Random Generater
double random_double() {
    // return a random real number in [0, 1)
    return rand() / (RAND_MAX + 1.0);
}

double random_double(double min, double max) {
    // return a random real number in [min, max)
    return min + (max - min) * random_double();
}

// Common Headers

#include "ray.hpp"
#include "vec3.hpp"

#endif
