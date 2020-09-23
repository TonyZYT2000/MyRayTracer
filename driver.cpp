#include <fstream>
#include <iostream>

#include "color.hpp"
#include "hittable_list.hpp"
#include "rtweekend.hpp"
#include "sphere.hpp"

color3 ray_color(const ray& r, const hittable& world) {
    hit_record record;
    if (world.hit(r, 0, infinity, record)) {
        return 0.5 * (record.normal + color3(1, 1, 1));
    } else {
        vec3 unit_dir = unit_vector(r.direction());
        double t = 0.5 * (unit_dir.y() + 1.0);
        return (1.0 - t) * color3(1.0, 1.0, 1.0) + t * color3(0.5, 0.7, 1.0);
    }
}

int main(void) {
    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 600;
    const int image_height = (int)(image_width / aspect_ratio);

    // Open File
    std::ofstream output;
    output.open("output.ppm");

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    // Camera
    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

    point3 origin(0, 0, 0);
    vec3 horiz(viewport_width, 0, 0);
    vec3 vert(0, viewport_height, 0);
    auto lower_left_corner =
        origin - horiz / 2 - vert / 2 - vec3(0, 0, focal_length);

    // Renderer
    output << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines reamaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            ray r(origin, lower_left_corner + horiz * u + vert * v);
            color3 pixel = ray_color(r, world);
            write_color(output, pixel);
        }
    }
    std::cerr << "\nDone.\n";

    output.close();
    return 0;
}
