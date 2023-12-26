#ifndef MAINHEADER_HPP
#define MAINHEADER_HPP

#include "ray.hpp"
#include "vec3.hpp"

#include <cmath>
#include <limits>
#include <memory>
//Usings

//I dont like usings keyword. Id rather work hard

//Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//Utility functions

inline double degrees_to_radians(double degrees){
    return degrees * pi / 180;
}

#endif