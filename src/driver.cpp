#include <fstream>
#include <future>
#include <iostream>
#include <vector>

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

hittable_list random_scene() {
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color3(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; ++a) {
        for (int b = -11; b < 11; ++b) {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2,
                          b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color3::random() * color3::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(
                        make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color3::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(
                        make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(
                        make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color3(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color3(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    return world;
}

void renderer(hittable_list& world, camera& cam, const int image_height,
              const int image_width, int& start_height, const int end_height,
              const int samples_per_pixel, const int max_depth,
              std::vector<color3>& pixels) {
    int start = start_height;
    start_height = end_height;
    for (int j = start; j >= end_height; --j) {
        // std::cerr << "\rScanlines reamaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color3 pixel_color(0, 0, 0);
            // Anti-Aliasing by sampling multiple times for single pixel
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            pixels[i + (image_height - j - 1) * image_width] = pixel_color;
        }
    }
}

int main(void) {
    // Image
    const double aspect_ratio = 3.0 / 2.0;
    const int image_width = 1600;
    const int image_height = (int)(image_width / aspect_ratio);
    const int samples_per_pixel = 500;
    const int max_depth = 50;
    const int threads = 32;

    // Open File
    std::ofstream output;
    output.open("output.ppm");

    // World
    srand(time(0));
    auto world = random_scene();

    // Camera
    point3 lookfrom(13, 2, 3);
    point3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    double focus_dist = 10;
    double aperture = 0.1;
    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, focus_dist);

    // Renderer
    auto pixels = std::vector<color3>(image_height * image_width);
    auto ft_list = std::vector<std::future<void>>(threads);
    int start_height = image_height - 1;
    int step = image_height / threads;

    for (auto& ft : ft_list) {
        int end_height =
            ((start_height - step) > 0 ? (start_height - step) : 0);
        ft = std::async(std::launch::async, [&] {
            renderer(world, cam, image_height, image_width, start_height,
                     end_height, samples_per_pixel, max_depth, pixels);
        });
        while (start_height != end_height) {
            std::cerr << '\0';
        }
        start_height -= 1;
    }
    std::cerr << "Finishing creating jobs" << std::endl;

    for (auto& ft : ft_list) {
        ft.wait();
    }
    std::cerr << "Finishing running jobs" << std::endl;

    /*
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
    */

    output << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (auto pixel_color : pixels) {
        write_color(output, pixel_color, samples_per_pixel);
    }
    std::cerr << "\nDone.\n";

    output.close();
    return 0;
}
