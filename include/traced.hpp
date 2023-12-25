#ifndef TRACED_H
#define TRACED_H

#include "ray.hpp"

class TraceRecord{
    public:
       Point3 p;
       Vec3 normal;
       double t;
};

class Traced {
    public:
      virtual ~Traced() = default;
       
      virtual bool trace(const Ray& r, double ray_tmin, double ray_tmax, TraceRecord& rec) const = 0;  
};

#endif