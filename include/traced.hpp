#ifndef TRACED_H
#define TRACED_H

#include "ray.hpp"

class TraceRecord{
    public:
       Point3 p;
       Vec3 normal;
       double t;
       bool front_face;

       void set_face_normal(const Ray& r,const Vec3& outward_normal){
             /*outward normal is unit length because I said so. and this function finds the direction
       of the normal vector. If the ray hits the sphere from outside then the normal vector is perpendicular to the 
       front of the surface. If its from inside the sphere (in case of glass sphere) then the normal is draw from inside
       the surface of the sphere*/
        front_face = dot(r.direction(),outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
       }
};


class Traced {
    public:
      virtual ~Traced() = default;
       
      virtual bool trace(const Ray& r, double ray_tmin, double ray_tmax, TraceRecord& rec) const = 0;  
};

#endif