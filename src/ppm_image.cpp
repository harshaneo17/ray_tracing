#include <iostream>

int main(){
    int image_width = 256;
    int image_height = 256;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j){
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i){
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_height-1);
            int b = 0;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);
            // static_cast<target type> (expression)
            /*std::flush is a stream manipulator to display the content of the stream. 
            Normally, a stream can wait until a good moment (the end of the program, for example), std::flush enforces a direct output. std::cout is a stream that one might want to flush, 
            std::clog and std::cerr always flush. 
            When writing '\n' to std::cout, std::cout is not flushed, std::endl writes '\n' and flushes the stream. Note that flushing a stream takes time, so only flush when needed.*/
            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::clog << "\rDone.                 \n";
}