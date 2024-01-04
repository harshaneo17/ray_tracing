#include "mainheader.hpp"

#include "camera.hpp"
#include "color.hpp"
#include "traced_list.hpp"
#include "material.hpp"
#include "sphere.hpp"



int main() {
   
    //World
    Traced_List world;

    auto R = cos(pi/4);

    auto material_left   = std::make_shared<Lambertian>(Color(0,1,0));
    auto material_right  = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);


    world.append(std::make_shared<Sphere>(Point3(-R,0,-1),R, material_left));
    world.append(std::make_shared<Sphere>(Point3(R,0,-1),R, material_right));

    Camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.render(world);
   
}