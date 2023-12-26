#include "mainheader.hpp"
#include "sphere.hpp"
#include "traced_list.hpp"
#include "camera.hpp"


int main() {
   
    //World
    Traced_List world;
    world.append(std::make_shared<Sphere>(Point3(0,0,-1),0.5));
    world.append(std::make_shared<Sphere>(Point3(0,-100.5,-1),100));

    Camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 400;

    cam.render(world);
   
}