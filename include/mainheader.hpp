#ifndef MAINHEADER_HPP
#define MAINHEADER_HPP


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

//This is the same stupidity as pushing a door that clearly says pull.
//understand why this include is written here instead of the top of this file.
//modern problems require modern solutions.
#include "interval.hpp"
#include "ray.hpp"
#include "vec3.hpp"


#endif