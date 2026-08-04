#pragma once
#include "hittable.h"
#include <vector>
#include <memory>

class HittableList : public Hittable {
public:
    std::vector<std::shared_ptr<Hittable>> objects;

    HittableList() {}

    void add(std::shared_ptr<Hittable> object) {
        objects.push_back(object);
    }

    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override {
        HitRecord temp_rec;
        bool hit_anything = false;
        double closest = t_max;

        for (const auto& object : objects) {
            if (object->hit(r, t_min, closest, temp_rec)) {
                hit_anything = true;
                closest = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};