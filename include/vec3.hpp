#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <iostream>

/* header guards are definded to ensure multiple includes are not being called during compilation
This is a preprocessor technique of preventing a header file from being included multiple times, 
which can be problematic for various reasons. 
During compilation of your project, each .cpp file (usually) is compiled. 
In simple terms, this means the compiler will take your .cpp file, open any files #included by it, 
concatenate them all into one massive text file, and then perform syntax analysis 
and finally it will convert it to some intermediate code, optimize/perform other tasks, 
and finally generate the assembly output for the target architecture. Because of this, 
if a file is #included multiple times under one .cpp file, the compiler will append its file contents twice, 
so if there are definitions within that file, you will get a compiler error telling you that you redefined a variable.
read more here https://shorturl.at/diHV2
*/

class Vec3 {
  public :
    float e[3]; //e is an arrya of 3 elements of float

    Vec3() : e{0,0,0} {} //constructor 1 to create Vec3 with all components to zero
    Vec3(float e0, float e1, float e2) : e{e0, e1, e2} {} // another constructor is provided that takes three floats as parameters

    float x() const {
         return e[0]; 
    }

    float y() const {
         return e[1]; 
    }

    float z() const {
         return e[2];
    }

    Vec3 operator-() const {
        return Vec3(-e[0], -e[1], -e[2]); 
    }

    float operator[](int i) const { 
        return e[i];
    }

    float& operator[](int i) {
        return e[i];
    }

    Vec3& operator+=(const Vec3 &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    Vec3& operator*=(float t){
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    Vec3& operator/=(float t) {
        return *this *= 1/t;
    }

    float length() const{
        return std::sqrt(length_squared());
    }

    float length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    } 
};

/* 
Create alias for Vec3, since this class serves two purposes, 
it becomes easy to differentiate which one is what in source code
*/

using Point3 = Vec3;

//Utility Global functions

/*Vector operations of dot and cross products along with operator overloading
Operator overloading means dunder methods like editing what an operator would do
in this case its the Vec3 object being added, subtracted or multiplied using these functions*/

inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2]; 
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator*(float t, const Vec3 &v) {
    return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline Vec3 operator/(Vec3 v, float t){
    return (1/t) * v;
}

inline float dot(const Vec3 &u, const Vec3 &v){
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2]; 
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v){
    return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vec3 unit_vector(Vec3 v) {
    return v / v.length();
}

#endif