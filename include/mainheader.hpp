#ifndef MAINHEADER_HPP
#define MAINHEADER_HPP


#include <cmath>
#include <random>
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

inline double random_double(){
    static std::uniform_real_distribution<double> distribution(0.0,1.0); 
    //Produces random floating-point values x , uniformly distributed on the interval [a,b), 
    // that is, distributed according to the probability density function:
    // P(x|a,b) = 1/b-a
    static std::mt19937 generator;
    //A Mersenne Twister pseudo-random generator of 32-bit numbers with a state size of 19937 bits.
    return distribution(generator);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

//This is the same stupidity as pushing a door that clearly says pull.
//understand why this include is written here instead of the top of this file.
//modern problems require modern solutions.
#include "interval.hpp"
#include "ray.hpp"
#include "vec3.hpp"


#endif