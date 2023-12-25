cmake_minimum_required(VERSION "3.19.2")

#run cmake -S <path to source> -B <path to build>
#cmake --build ./build --config Release (windows)

project("ray_tracing")
set(CMAKE_CXX_STANDARD 17)
add_executable(main "src/ppm_image.cpp")
target_include_directories(main PUBLIC "include/") #syntax (<target_exe> PUBLIC| |PRIVATE | INTERFACE <path_to_lib>)

