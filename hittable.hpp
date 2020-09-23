#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "ray.hpp"
#include "vec3.hpp"

struct hit_record {
    double t;
    vec3 normal;
    point3 point;
    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
  public:
    virtual bool hit(const ray& r, double t_min, double t_max,
                     hit_record& record) const = 0;
};

#endif
