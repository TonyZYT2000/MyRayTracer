#include <fstream>
#include <iostream>

#include "camera.hpp"
#include "color.hpp"
#include "hittable_list.hpp"
#include "material.hpp"
#include "rtweekend.hpp"
#include "sphere.hpp"

color3 ray_color(const ray& r, const hittable& world, int depth) {
    hit_record record;

    // reaching maximum depth
    if (depth <= 0) {
        return color3(0, 0, 0);
    }

    if (world.hit(r, 0.001, infinity, record)) {
        ray scattered;
        color3 attenuation;
        if (record.mat_ptr->scatter(r, record, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, depth - 1);
        } else {
            return color3(0, 0, 0);
        }
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
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // Open File
    std::ofstream output;
    output.open("output.ppm");

    // World
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color3(0.8, 0.8, 0));
    auto material_center = make_shared<lambertian>(color3(0.1, 0.2, 0.5));
    auto material_left = make_shared<dielectric>(1.5);
    auto material_right = make_shared<metal>(color3(0.8, 0.6, 0.2), 0.0);

    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100, material_ground));
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1, 0, -1), 0.5, material_left));
    //world.add(make_shared<sphere>(point3(-1, 0, -1), -0.45, material_left));
    world.add(make_shared<sphere>(point3(1, 0, -1), 0.5, material_right));

    // Camera
    camera cam(point3(-2, 2, 1), point3(0, 0, -1), vec3(0, 1, 0), 20, aspect_ratio);

    // Renderer
    output << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines reamaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color3 pixel_color(0, 0, 0);
            // Anti-Aliasing by sampling multiple times for single pixel
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(output, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";

    output.close();
    return 0;
}
