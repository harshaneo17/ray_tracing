#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "mainheader.hpp"
#include "color.hpp"
#include "traced.hpp"
#include "material.hpp"

#include <iostream>

class Camera{
    public:
        double aspect_ratio = 1.0;  // Ratio of image width over height
        int    image_width  = 100;  // Rendered image width in pixel count
        int    samples_per_pixel = 10; //Count of random samples for each pixel
        int    max_depth = 10;


        void render(const Traced& world){
            initialize();
            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for (int j = 0; j < image_height; ++j){
                std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
                for (int i = 0; i < image_width; ++i){
                    Color pixel_color(0,0,0);
                    for (int sample = 0;sample < samples_per_pixel; ++sample){
                        Ray r = get_ray(i,j);
                        pixel_color += ray_color(r,max_depth, world);
                    }
                    write_color(std::cout, pixel_color, samples_per_pixel); //this method is described in color.hpp
                // static_cast<target type> (expression)
                /*std::flush is a stream manipulator to display the content of the stream. 
                Normally, a stream can wait until a good moment (the end of the program, for example), std::flush enforces a direct output. std::cout is a stream that one might want to flush, 
                std::clog and std::cerr always flush. 
                When writing '\n' to std::cout, std::cout is not flushed, std::endl writes '\n' and flushes the stream. Note that flushing a stream takes time, so only flush when needed.*/
            }
        }
        std::clog << "\rDone.                 \n";

        }
    private:
        int    image_height;   // Rendered image height
        Point3 camera_center;         // Camera center
        Point3 pixel_origin;    // Location of pixel 0, 0
        Vec3   pixel_delta_u;  // Offset to pixel to the right
        Vec3   pixel_delta_v;  // Offset to pixel below

        void initialize(){
            //Calculate image height from aspect ratio and width
            image_height = static_cast<int>(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;
            /* the english translation of above terinary operator means
            image height is 1 if image height is less than one else image height stays the same
            */
            camera_center = Point3(0,0,0);

            //camera
            auto focal_length = 1.0;
            auto viewport_height = 2.0;
            auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);

            //calculate the vectors that navigate on the viewport
            auto viewport_u = Vec3(viewport_width, 0, 0);
            auto viewport_v = Vec3(0,-viewport_height,0); //why negative?

            //calculate the difference in pixel to pixel (Delta v)
            pixel_delta_u = viewport_u / image_width;
            pixel_delta_v = viewport_v / image_height;

            //calculate the location of the upper left pixel
            auto viewport_upper_left = camera_center - Vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;
            pixel_origin = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        }

        Ray get_ray(int i, int j) const {
            //Get a randomly sampled camera ray for the pixel at location i,j

            auto pixel_center = pixel_origin + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto pixel_sample = pixel_center + pixel_sample_square();

            auto ray_origin = camera_center;
            auto ray_direction = pixel_sample - ray_origin;

            return Ray(ray_origin, ray_direction);
        }

        Vec3 pixel_sample_square() const {
            //Returns a random point in the square surrounding a pixel at origin
            auto px = -0.5 + random_double();
            auto py = -0.5 + random_double();
            return (px * pixel_delta_u) + (py * pixel_delta_v);
        }

        Color ray_color(const Ray& r,int depth,const Traced& world) const {
        /*
        color of ray. each pixel coordinate corresponding to a Color object which is multiplied with 255
        to ensure the color values are normalized. Not sure what normalized means here but ill come back to this.
        This method has certain conditions like hit_sphere and  color gradient for whole image. 
        Hit sphere also draws a sphere and highlights the parts where ray pixels intersect with it. 
        read above function
        */
            TraceRecord rec;

            //if ray bounce limit is exceeded return 0,0,0
            if (depth <= 0)
                return Color(0,0,0);

            if (world.trace(r,Interval(0.001,infinity),rec)){
                //Vec3 direction = random_on_hemisphere(rec.normal);
                //comment this to disable lambertian diffusion distribution
                Ray scattered;
                Color attenuation;
                if (rec.mat->scatter(r, rec, attenuation, scattered))
                    return attenuation * ray_color(scattered, depth - 1 ,world);
                return Color(0,0,0);
            }
        
            Vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y()+1.0);
            return (1.0-a)*Color(1.0,1.0,1.0)+a*Color(0.5,0.7,1.0);

        }
};

#endif