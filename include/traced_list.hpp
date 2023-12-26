#ifndef TRACEDLIST_HPP
#define TRACEDLIST_HPP

#include "traced.hpp"

#include <memory>
#include <vector>

//shared_ptr is included in the memory header
//std::vector is included in the vector header

class Traced_List : public Traced {
    public:
      std::vector<std::shared_ptr<Traced>> objects;

      Traced_List(){}
      Traced_List(std::shared_ptr<Traced> object){append(object);}

      void clear() {objects.clear();}

      void append(std::shared_ptr<Traced> object){
        objects.push_back(object);
      }

      bool trace(const Ray& r, double ray_tmin, double ray_tmax, TraceRecord& rec) const override {
        TraceRecord temp_rec;
        bool trace_anything = false;
        auto closest_point_yet = ray_tmax;

        for (const auto& object : objects){
            if(object->trace(r, ray_tmin,closest_point_yet,temp_rec)) {
                trace_anything = true;
                closest_point_yet = temp_rec.t;
                rec = temp_rec;
            }
        }
        return trace_anything;
      }

};

#endif