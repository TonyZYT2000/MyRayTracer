#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "rtweekend.hpp"

struct hit_record;

class material {
  public:
    virtual bool scatter(const ray& r_in, const hit_record& record,
                         color3& attenuation, ray& scattered) const = 0;
};

class lambertian : public material {
  private:
    color3 albedo;

  public:
    lambertian() : albedo(color3()) {}
    lambertian(const color3& c) : albedo(c) {}

    virtual bool scatter(const ray& r_in, const hit_record& record,
                         color3& attenuation, ray& scattered) const override {
        vec3 scatter_direction = record.normal + random_unit_vector();
        scattered = ray(record.point, scatter_direction);
        attenuation = albedo;
        return true;
    }
};

class metal : public material {
  private:
    color3 albedo;
    double fuzz;

  public:
    metal() : albedo(color3()), fuzz(0) {}
    metal(const color3& c, double f) : albedo(c), fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(const ray& r_in, const hit_record& record,
                         color3& attenuation, ray& scattered) const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()), record.normal);
        scattered = ray(record.point, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), record.normal) > 0);
    }
};

#endif
