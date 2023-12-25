# Ray Tracing

Ray tracing library implementation in c++. 

Plan to use multiple shapes

HELPFUL LINKS 

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

![plot](./ray_tracing.png)