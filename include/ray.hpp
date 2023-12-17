#ifndef RAY_HPP
#define RAY_HPP

#include "vec3.hpp"

/*Let’s think of a ray as a function P(t)=A+tb
Here P is a 3D position along a line in 3D. 
A is the ray origin and b is the ray direction. The ray parameter t
is a real number (float in the code). Plug in a different t
and P(t) moves the point along the ray. Add in negative t
values and you can go anywhere on the 3D line. For positive t,
you get only the parts in front of A,and this is what is often called a half-line or a ray.
We can represent the idea of a ray as a class, and represent the function P(t)
as a function that we'll call ray::at(t)*/

class Ray {

  public:
    
    Ray() {}

    Ray(const Point3& origin, const Vec3& direction) : orig(origin), dir(direction) {}

    Point3 origin() const {
        return orig;
    }

    Vec3 direction() const {
        return dir;
    }

    Point3 at(float t) const{
        return orig + t*dir;
    }

  private:
    Point3 orig;
    Vec3 dir;    
};



#endif