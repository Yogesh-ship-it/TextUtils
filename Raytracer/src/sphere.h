#pragma once
#include "hittable.h"
#include "material.h"
#include <cmath>

class Sphere : public Hittable {
public:
    point3 center;
    double radius;
    std::shared_ptr<Material> material;

    Sphere(point3 center, double radius, std::shared_ptr<Material> material)
        : center(center), radius(radius), material(material) {}

    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override {
        vec3 oc = r.origin - center;
        double a = dot(r.direction, r.direction);
        double b = dot(oc, r.direction);
        double c = dot(oc, oc) - radius * radius;
        double discriminant = b*b - a*c;

        if (discriminant < 0) return false;

        double sqrtd = std::sqrt(discriminant);
        double root = (-b - sqrtd) / a;

        if (root < t_min || root > t_max) {
            root = (-b + sqrtd) / a;
            if (root < t_min || root > t_max)
                return false;
        }

        rec.t      = root;
        rec.point  = r.at(rec.t);
        vec3 outward_normal = (rec.point - center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.material = material;

        return true;
    }
};