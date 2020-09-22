#include <fstream>
#include <iostream>

#include "ray.hpp"
#include "vec3.hpp"


bool hit_sphere(const vec3& center, double radius, const ray& r) {
    double a = dot(r.direction(), r.direction());
    double b = 2 * dot(r.direction(), r.origin() - center);
    double c = dot(r.origin() - center, r.origin() - center) - radius * radius;
    double delta = b * b - 4 * a * c;
    return delta > 0;
}

vec3 color(const ray& r) {
    if (hit_sphere(vec3(0, 0, -1), 0.5, r)) {
        return vec3(1, 0, 0);
    }
    vec3 unit_dir = unit_vector(r.direction());
    double t = 0.5 * (unit_dir.y() + 1.0);
    return vec3(1.0, 1.0, 1.0) * (1.0 - t) + vec3(0.2, 0.7, 1.0) * t;
}

int main(void) {
    int nx = 200;
    int ny = 100;

    std::ofstream output;
    output.open("output.ppm");
    output << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 origin(0.0, 0.0, 0.0);
    vec3 horiz(4.0, 0.0, 0.0);
    vec3 vert(0.0, 2.0, 0.0);
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            double u = double(i) / double(nx);
            double v = double(j) / double(ny);
            ray r(origin, lower_left_corner + horiz * u + vert * v);
            vec3 pixel(color(r));
            int ir = int(255.99 * pixel.r());
            int ig = int(255.99 * pixel.g());
            int ib = int(255.99 * pixel.b());
            output << ir << " " << ig << " " << ib << "\n";
        }
    }

    output.close();
    return 0;
}
