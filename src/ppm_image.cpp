#include "mainheader.hpp"

#include "camera.hpp"
#include "color.hpp"
#include "traced_list.hpp"
#include "material.hpp"
#include "sphere.hpp"



int main() {
   
    //World
    Traced_List world;

    auto ground_material = std::make_shared<Lambertian>(Color(0.5,0.5,0.5));
    world.append(std::make_shared<Sphere>(Point3(0,-1000,0),1000,ground_material));

    for (int a = -11; a < 11; a++) {
        for(int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            Point3 center(a + 0.9 * random_double(),0.2, b + 0.9*random_double());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    //diffuse
                    auto albedo = Color::random_vec() * Color::random_vec();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.append(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    //metal
                    auto albedo = Color::random_vec(0.5,1);
                    auto fuzz = random_double(0,0.5);
                    sphere_material = std::make_shared<Metal>(albedo,fuzz);
                    world.append(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    //glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.append(std::make_shared<Sphere>(center,0.2,sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.append(std::make_shared<Sphere>(Point3(0,1,0),1.0,material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4,0.2,0.1));
    world.append(std::make_shared<Sphere>(Point3(-4,1,0),1.0,material2));

    auto material3 = std::make_shared<Metal>(Color(0.7,0.6,0.5),0.0);
    world.append(std::make_shared<Sphere>(Point3(4,1,0),1.0,material3));



    Camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 700;
    cam.samples_per_pixel = 200;
    cam.max_depth = 50;

    cam.vfov = 20;
    cam.lookfrom = Point3(13,2,3);
    cam.lookat = Point3(0,0,0);
    cam.cam_vertical_up = Vec3(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_dist = 10.0;

    cam.render(world);
   
}