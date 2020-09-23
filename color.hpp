#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>

#include "vec3.hpp"

void write_color(std::ostream& out, color3 pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // scaling color by 1/# of samples, then gamma correct with gamma = 2
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    out << (int)(256 * clamp(r, 0.0, 0.999)) << ' '
        << (int)(256 * clamp(g, 0.0, 0.999)) << ' '
        << (int)(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif
