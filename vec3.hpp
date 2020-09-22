#ifndef VEC3_HPP
#define VEC3_HPP

class vec3 {
  private:
    double v[3];

  public:
    vec3() {
        v[0] = 0;
        v[1] = 0;
        v[2] = 0;
    }
    vec3(double vec0, double vec1, double vec2) {
        v[0] = vec0;
        v[1] = vec1;
        v[2] = vec2;
    }

    double x() const { return v[0]; }
    double y() const { return v[1]; }
    double z() const { return v[2]; }
    double r() const { return v[0]; }
    double g() const { return v[1]; }
    double b() const { return v[2]; }

    double& operator[](int i) { return v[i]; }
    const double& operator[](int i) const { return v[i]; }
    vec3 operator+() const {return vec3(v[0], v[1], v[2]);}
    vec3 operator-() const { return vec3(-v[0], -v[1], -v[2]);}

    vec3 operator+(const vec3& v2) const;
    vec3 operator-(const vec3& v2) const;
    vec3 operator*(const vec3& v2) const;
    vec3 operator/(const vec3& v2) const;
    vec3 operator*(const double t) const;
    vec3 operator/(const double t) const;

    vec3& operator+=(const vec3& v2);
    vec3& operator-=(const vec3& v2);
    vec3& operator*=(const vec3& v2);
    vec3& operator/=(const vec3& v2);
    vec3& operator*=(const double t);
    vec3& operator/=(const double t);

    double length() const;
    double squared_length() const;
    void make_unit_vector();
};

double dot(const vec3& v1, const vec3& v2);
vec3 cross(const vec3& v1, const vec3& v2);
vec3 unit_vector(const vec3& v);
#endif
