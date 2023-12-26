#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "traced.hpp"
#include "vec3.hpp"

class Sphere : public Traced {
    public:
       Sphere(Point3 _center, double _radius) : center(_center), radius(_radius){}

       bool trace(const Ray& r, Interval ray_t, TraceRecord& rec) const override {
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
            if (!ray_t.surrounds(root)){
                root = (-half_b + sqrtd) / a;
                if (!ray_t.surrounds(root))
                   return false;
            }
            rec.t = root;
            rec.p = r.ray_equation(rec.t);
            Vec3 outward_normal = (rec.p - center)/ radius;
            rec.set_face_normal(r,outward_normal);

            return true;

       }
       private:
         Point3 center;
         double radius;
        
};

#endif