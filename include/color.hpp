#ifndef COLOR_HPP
#define COLOR_HPP

#include <vec3.hpp>

#include <iostream>

using Color = Vec3;

void write_color(std::ostream &out, Color pixel_color) {
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

#endif