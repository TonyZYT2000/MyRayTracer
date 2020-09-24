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
        scattered =
            ray(record.point, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), record.normal) > 0);
    }
};

class dielectric : public material {
  private:
    double ref_index;

    static double schlick(double cosine, double ri) {
        auto r0 = (1 - ri) / (1 + ri);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }

  public:
    dielectric() : ref_index(1) {}
    dielectric(double ri) : ref_index(ri) {}

    virtual bool scatter(const ray& r_in, const hit_record& record,
                         color3& attenuation, ray& scattered) const override {
        attenuation = color3(1, 1, 1);
        double etai_over_etat = record.front_face ? (1 / ref_index) : ref_index;
        vec3 v_in = r_in.direction();

        double cos_theta = dot(-v_in, record.normal) / v_in.length();
        double sin_theta = sqrt(1 - cos_theta * cos_theta);

        if (etai_over_etat * sin_theta > 1) {
            vec3 reflected = reflect(v_in, record.normal);
            scattered = ray(record.point, reflected);
            return true;
        }

        double reflect_prob = schlick(cos_theta, etai_over_etat);
        if (random_double() < reflect_prob) {
            vec3 reflected = reflect(v_in, record.normal);
            scattered = ray(record.point, reflected);
            return true;
        } else {
            vec3 refracted = refract(v_in, record.normal, etai_over_etat);
            scattered = ray(record.point, refracted);
            return true;
        }
    }
};

#endif
