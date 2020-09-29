#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include <memory>
#include <vector>

#include "hittable.hpp"

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable {
  private:
    std::vector<shared_ptr<hittable>> objects;

  public:
    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(shared_ptr<hittable> object) { objects.push_back(object); }

    virtual bool hit(const ray& r, double t_min, double t_max,
                     hit_record& record) const override;
};

bool hittable_list::hit(const ray& r, double t_min, double t_max,
                        hit_record& record) const {
    hit_record temp_rec;
    bool hit_flag = false;
    double closest = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest, temp_rec)) {
            hit_flag = true;
            closest = temp_rec.t;
            record = temp_rec;
        }
    }

    return hit_flag;
}

#endif
