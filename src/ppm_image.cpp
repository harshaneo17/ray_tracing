#include "color.hpp"
#include "ray.hpp"
#include "vec3.hpp"

#include <iostream>
float hit_sphere(const Point3& center, double radius, const Ray& r){
    /*This function calculates a,b,c to determine the discriminant and find out if the 
    quadratic equation of sphere and ray has any roots. If it does then we know for certain that 
    there is a ray projected onto that sphere. otherwise it just passes by. The factor by which 
    a ray is project onto sphere is "t" this is the coordinate of intersection of the ray and the sphere
    This function returns true if "t" exists on the sphere. A geometric proof is available on the OG website
    but its rather expansive and out of documentation scope. this shall be therefore covered in a video*/
     Vec3 oc = r.origin() - center;
     auto a = dot(r.direction(),r.direction());
     auto b = 2 * dot(oc,r.direction());
     auto c = dot(oc, oc) - radius*radius;
     auto discriminant = b*b - 4*a*c;
     
     if (discriminant < 0){
        return -1.0;
     } 
     else{
        return (-b - std::sqrt(discriminant)) / (2*a);
     }
}


Color ray_color(const Ray& r){
    /*
    color of ray. each pixel coordinate corresponding to a Color object which is multiplied with 255
    to ensure the color values are normalized. Not sure what normalized means here but ill come back to this.
    This method has certain conditions like hit_sphere and  color gradient for whole image. 
    Hit sphere also draws a sphere and highlights the parts where ray pixels intersect with it. 
    read above function
    */
    float t = hit_sphere(Point3(0,0,-1),0.5,r);
    if (t > 0.0){
       Vec3 perp = unit_vector(r.at(t) - Vec3(0,0,-1));
       return 0.5 * Color(perp.x()+1,perp.y(),perp.z()); //normal(x,y,z) correspond to r,g,b
    }
   
    Vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y()+1.0);
    return (1.0-a)*Color(1.0,1.0,1.0)+a*Color(0.5,0.7,1.0);
}

int main() {
    
    //Image
    auto aspect_ratio = 16.0/9.0;
    int image_width = 400;

    //Calculate image height from aspect ratio and width
    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
    /* the english translation of above terinary operator means
    image height is 1 if image height is less than one else image height stays the same
    */
   
    //camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
    auto camera_center = Point3(0,0,0);

    //calculate the vectors that navigate on the viewport
    auto viewport_u = Vec3(viewport_width, 0, 0);
    auto viewport_v = Vec3(0,-viewport_height,0); //why negative?

    //calculate the difference in pixel to pixel (Delta v)
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    //calculate the location of the upper left pixel
    auto viewport_upper_left = camera_center - Vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel_origin = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j){
       std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
       for (int i = 0; i < image_width; ++i){
            auto pixel_center = pixel_origin + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            Ray r(camera_center, ray_direction);
            Color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color); //this method is described in color.hpp
            // static_cast<target type> (expression)
            /*std::flush is a stream manipulator to display the content of the stream. 
            Normally, a stream can wait until a good moment (the end of the program, for example), std::flush enforces a direct output. std::cout is a stream that one might want to flush, 
            std::clog and std::cerr always flush. 
            When writing '\n' to std::cout, std::cout is not flushed, std::endl writes '\n' and flushes the stream. Note that flushing a stream takes time, so only flush when needed.*/
        }
    }
    std::clog << "\rDone.                 \n";
}