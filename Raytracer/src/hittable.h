#pragma once
#include "vec3.h"
#include "ray.h"
#include <memory>

class Material;

struct HitRecord {
    point3 point;
    vec3   normal;
    double t;
    bool   front_face;
    std::shared_ptr<Material> material;

    void set_face_normal(const Ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction, outward_normal) < 0;
        normal = front_face ? outward_normal : outward_normal * -1;
    }
};

class Hittable {
public:
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};