#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>

#include "vec3.hpp"

void write_color(std::ostream& out, color3 pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    auto scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    out << (int)(256 * clamp(r, 0.0, 0.999)) << ' '
        << (int)(256 * clamp(g, 0.0, 0.999)) << ' '
        << (int)(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif
