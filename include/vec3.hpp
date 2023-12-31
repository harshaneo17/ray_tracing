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
    double e[3]; //e is an arrya of 3 elements of double

    Vec3() : e{0,0,0} {} //constructor 1 to create Vec3 with all components to zero
    Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {} // another constructor is provided that takes three doubles as parameters

    double x() const {
         return e[0]; 
    }

    double y() const {
         return e[1]; 
    }

    double z() const {
         return e[2];
    }

    Vec3 operator-() const {
        return Vec3(-e[0], -e[1], -e[2]); 
    }

    double operator[](int i) const { 
        return e[i];
    }

    double& operator[](int i) {
        return e[i];
    }

    Vec3& operator+=(const Vec3 &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    Vec3& operator*=(double t){
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    Vec3& operator/=(double t) {
        return *this *= 1/t;
    }

    double length() const{
        return std::sqrt(length_squared());
    }

    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    bool near_zero() const {
        //Return true if vector is close to zero in all dimentions
        auto s = 1e-8;
        return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
    }

    double magnitude() const {
        /*Makes more sense to call it magnitude*/
        return std::sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    }

    static Vec3 random_vec(){
        return Vec3(random_double(),random_double(),random_double());
    }

    static Vec3 random_vec(double min, double max){
        /*The is the one of the most basic feature of C++: function overloading. 
        In C++, it's entirely possible as long as the function function signature is different,
         ie two functions having the same name but different set of parameters.*/
        return Vec3(random_double(min,max), random_double(min,max), random_double(min,max));
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

inline Vec3 operator*(double t, const Vec3 &v) {
    return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline Vec3 operator*(const Vec3 &v, double t) {
    return t * v;
}

inline Vec3 operator/(Vec3 v, double t){
    return (1/t) * v;
}

inline double dot(const Vec3 &u, const Vec3 &v){
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2]; 
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v){
    return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vec3 unit_vector(Vec3 v) {
    /*The term normalized vector is sometimes used as a synonym for unit vector*/
    return v / v.length();
}

inline Vec3 random_in_unit_disk() {
    while (true) {
        auto p = Vec3(random_double(-1,1), random_double(-1,1),0);
        if (p.length_squared() < 1)
            return p;
    }
}

inline Vec3 random_in_unit_sphere(){
    while(true){
        auto p = Vec3::random_vec(-1,1);
        if (p.length_squared() < 1)
            return p;
    }
}

inline Vec3 random_unit_vector(){
    return unit_vector(random_in_unit_sphere());
}

inline Vec3 random_on_hemisphere(const Vec3& normal){
    Vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere,normal) > 0.0)
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

inline Vec3 reflect(const Vec3& v, const Vec3& n){
    return v - 2*dot(v,n)*n;
}

inline Vec3 refract(const Vec3& uv,const Vec3& n,double etai_over_etat){
    auto cos_theta = fmin(dot(-uv,n),1.0);
    //fmin takes two arguements and returns the smallest of them
    Vec3 r_out_perp =  etai_over_etat * (uv + cos_theta * n);
    Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    // refer to my notes for explanation
    return r_out_perp + r_out_parallel;
}

#endif