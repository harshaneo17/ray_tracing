#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "traced.hpp"
#include "vec3.hpp"

class Sphere : public Traced {
    public:
       Sphere(Point3 _center, double _radius) : center(_center), radius(_radius){}

       bool trace(const Ray& r, double ray_tmin, double ray_tmax, TraceRecord& rec) const override {
            Vec3 oc = r.origin() - center;
            auto a = r.direction().length_squared();
            auto half_b = dot(oc, r.direction());
            auto c = oc.length_squared() - radius*radius;

            auto discriminant = half_b*half_b - a*c;
            if (discriminant < 0) return false;
            auto sqrtd = std::sqrt(discriminant);

            /*previously we did only true or false condition. then we wanted to know the exact values 
            now we are considering closest values to roots as well*/
            auto root = (-half_b - sqrtd) / a;
            if (root <= ray_tmin || ray_tmax <= root){
                return false;
            }
            rec.t = root;
            rec.p = r.at(rec.t);
            rec.normal = (rec.p - center) / radius;

            return true;

       }
       private:
         Point3 center;
         double radius;
        
};

#endif