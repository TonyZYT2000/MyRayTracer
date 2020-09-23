#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>

#include "vec3.hpp"

void write_color(std::ostream& out, color3 pixel_color) {
    out << (int)(255.999 * pixel_color.x()) << ' '
        << (int)(255.999 * pixel_color.y()) << ' '
        << (int)(255.999 * pixel_color.z()) << '\n';
}

#endif
