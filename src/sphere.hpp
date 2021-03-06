#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cmath>

#include "hittable.hpp"

class sphere : public hittable {
  private:
    point3 center;
    double radius;
    shared_ptr<material> mat_ptr;

  public:
    sphere() : center(vec3()), radius() {}
    sphere(vec3 center, double radius, shared_ptr<material> m)
        : center(center), radius(radius), mat_ptr(m) {}

    virtual bool hit(const ray& r, double t_min, double t_max,
                     hit_record& record) const override;
};

bool sphere::hit(const ray& r, double t_min, double t_max,
                 hit_record& record) const {
    vec3 oc = r.origin() - center;
    double a = r.direction().squared_length();
    double half_b = dot(oc, r.direction());
    double c = oc.squared_length() - radius * radius;
    double delta = half_b * half_b - a * c;

    if (delta > 0) {
        double sol = (-half_b - sqrt(delta)) / a;
        if (sol > t_min && sol < t_max) {
            record.t = sol;
            record.point = r.at(sol);
            vec3 outward_normal = (record.point - center) / radius;
            record.set_face_normal(r, outward_normal);
            record.mat_ptr = mat_ptr;
            return true;
        }

        sol = (-half_b + sqrt(delta)) / a;
        if (sol > t_min && sol < t_max) {
            record.t = sol;
            record.point = r.at(sol);
            vec3 outward_normal = (record.point - center) / radius;
            record.set_face_normal(r, outward_normal);
            record.mat_ptr = mat_ptr;
            return true;
        }
    }

    return false;
}

#endif
