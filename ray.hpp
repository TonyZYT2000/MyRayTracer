#ifndef RAY_HPP
#define RAY_HPP

#include "vec3.hpp"

class ray {
  private:
    vec3 ori;
    vec3 dir;

  public:
    ray() : ori(vec3()), dir(vec3()) {}
    ray(const vec3& ori, const vec3& dir) : ori(ori), dir(dir) {}
    vec3 origin() const { return ori; }
    vec3 direction() const { return dir; }
    vec3 at(double t) const { return ori + dir * t; }
};

#endif
