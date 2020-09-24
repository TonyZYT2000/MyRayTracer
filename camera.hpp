#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "rtweekend.hpp"

class camera {
  private:
    vec3 vertical;
    vec3 horizontal;
    point3 origin;
    point3 lower_left_corner;

  public:
    camera() {
        double aspect_ratio = 16.0 / 9.0;
        double viewport_height = 2.0;
        double viewport_width = aspect_ratio * viewport_height;
        double focal_length = 1.0;

        origin = point3(0, 0, 0);
        vertical = vec3(0, viewport_height, 0);
        horizontal = vec3(viewport_width, 0, 0);
        lower_left_corner =
            origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
    }

    camera(point3 lookfrom, point3 lookat, vec3 vup, double vfov,
           double aspect_ratio) {
        double theta = degrees_to_radius(vfov);
        double h = tan(theta / 2);
        double viewport_height = 2 * h;
        double viewport_width = aspect_ratio * viewport_height;

        auto w = unit_vector(lookfrom - lookat);
        auto u = unit_vector(cross(vup, w));
        auto v = cross(w, u);

        origin = lookfrom;
        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;
    }

    ray get_ray(double s, double t) const {
        return ray(origin,
                   lower_left_corner + s * horizontal + t * vertical - origin);
    }
};

#endif
