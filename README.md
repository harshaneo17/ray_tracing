# Ray Tracing

Ray tracing library implementation in c++, following ray tracing in a weekend tutorials. Most stuff depends on domain knowledge. A good christmas week gone for this. 

I wish to make this a library so I can use this for future projects. after reading the theory of Ray tracing, I found Spheres to be the easiest shape to render.

<u> Plan to use multiple shapes </u>

<u> HELPFUL LINKS </u>

https://stackoverflow.com/questions/1943276/what-does-do-in-a-c-declaration

https://thoughtbot.com/blog/the-magic-behind-configure-make-make-install

https://stackoverflow.com/questions/11021452/how-do-redirect-stdout-out-of-xcode-compiled-command-line-executable?rq=4


# Cmake commands to build depending on OS
cmake -S <path to source> -B <path to build>

cmake --build ./build --config Release (windows)

make -C build/ (linux,mac) 

```
   cmake -S . -B build
   make -C build/
```

# Camera view point self.explanation

<img src="images/ray_tracing.png" width="800">

# Progress after creating a camera class

<img src="images/image.jpg" width="800">