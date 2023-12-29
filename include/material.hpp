#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "mainheader.hpp"

using Color = Vec3;

class TraceRecord; //this is to ensure compiler knows class something is defined and we shall write it later

class Material {
    public:
        virtual ~Material() = default;

        virtual bool scatter(const Ray& r_in,const TraceRecord& rec, Color& attuenuation, Ray& scattered) const = 0;
    
};

class Lambertian : public Material {
    public:
        Lambertian(const Color& a) : albedo(a) {}

        bool scatter(const Ray& r_in, const TraceRecord& rec, Color& attenuation, Ray& scattered)
        const override {
            auto scatter_direction = rec.normal + random_unit_vector();

            /*If the random unit vector we generate is exactly opposite the normal vector, 
            the two will sum to zero, which will result in a zero scatter direction vector. 
            This leads to bad scenarios later on (infinities and NaNs), 
            so we need to intercept the condition before we pass it on*/

            if (scatter_direction.near_zero())
                scatter_direction = rec.normal;

            scattered = Ray(rec.p, scatter_direction);
            return true;

        }
    private:
        Color albedo;
};

class Metal: public Material {
    public:
        Metal(const Color& a): albedo(a) {}

        bool scatter(const Ray& r_in, const TraceRecord& rec, Color& attenuation, Ray& scattered)
        const override {
            Vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = Ray(rec.p, reflected);
            attenuation = albedo;
            return true;
        }

    private:
        Color albedo;

};

#endif