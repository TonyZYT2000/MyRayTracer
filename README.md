# My Ray Tracer

## Description

This is based on [Peter Shirley](https://github.com/petershirley)'s fantastic tutorial *[Ray Tracing in One Weekend Series](https://raytracing.github.io/)*. I have some modifications based on my own taste.

## Build

Type `mkdir build && cd build` to create the build directory where project will be generated.

- Use `cmake -DCMAKE_BUILD_TYPE=Debug ..` for debug build.

- Use `cmake -DCMAKE_BUILD_TYPE=Release ..` for release build.

Add flag `-G "Unix Makefiles"` to force generating Makefile project.

To debug the project in VSCode, make sure to use debug build and add the above flag. That is:

```bash
cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" ..
```

Also, you can use [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) in VSCode to automatically generate the project.

## Artworks!

Here are some artworks created by the ray tracer. They show multiple textures and the effects of reflection and refraction.

![3 Balls](https://cdn.jsdelivr.net/gh/TonyZYT2000/MyRayTracer@master/pic/3balls.jpg)

![Random Balls 1](https://cdn.jsdelivr.net/gh/TonyZYT2000/MyRayTracer@master/pic/ManyBalls1.jpg)

![Random Balls 2](https://cdn.jsdelivr.net/gh/TonyZYT2000/MyRayTracer@master/pic/ManyBalls2.jpg)
