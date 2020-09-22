#include <iostream>
#include <fstream>

#include "vec3.hpp"

int main(void) {
    int nx = 200;
    int ny = 100;

    std::ofstream output;
    output.open("output.ppm");
    output << "P3\n" << nx << " " << ny << "\n255\n";

    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 pixel(float(i) / float(nx), float(j) / float(ny), 0.2);
            int ir = int(255.99 * pixel.r());
            int ig = int(255.99 * pixel.g());
            int ib = int(255.99 * pixel.b());
            output << ir << " " << ig << " " << ib << "\n";
        }
    }

    output.close();
    return 0;
}
