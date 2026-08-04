#pragma once
#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include <cmath>
#include <cstdlib>

// Random number helpers
inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

inline vec3 random_in_unit_sphere() {
    while (true) {
        vec3 p(
            random_double()*2 - 1,
            random_double()*2 - 1,
            random_double()*2 - 1
        );
        if (dot(p,p) < 1) return p;
    }
}

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - n * 2 * dot(v, n);
}



class Material {
public:
    virtual bool scatter(
        const Ray& r_in,
        const HitRecord& rec,
        color& attenuation,
        Ray& scattered
    ) const = 0;
};

// Matte / diffuse
class Lambertian : public Material {
public:
    color albedo;
    Lambertian(const color& a) : albedo(a) {}

    bool scatter(const Ray&, const HitRecord& rec,
                 color& attenuation, Ray& scattered) const override {
        vec3 direction = rec.normal + random_in_unit_sphere().normalize();
        scattered   = Ray(rec.point, direction);
        attenuation = albedo;
        return true;
    }
};

// Metal / reflective
class Metal : public Material {
public:
    color  albedo;
    double fuzz;
    Metal(const color& a, double f) : albedo(a), fuzz(f) {}

    bool scatter(const Ray& r_in, const HitRecord& rec,
                 color& attenuation, Ray& scattered) const override {
        vec3 reflected = reflect(r_in.direction.normalize(), rec.normal);
        scattered   = Ray(rec.point, reflected + random_in_unit_sphere() * fuzz);
        attenuation = albedo;
        return dot(scattered.direction, rec.normal) > 0;
    }
};

// Glass / dielectric
class Dielectric : public Material {
public:
    double refraction_index;
    Dielectric(double ri) : refraction_index(ri) {}

    bool scatter(const Ray& r_in, const HitRecord& rec,
                 color& attenuation, Ray& scattered) const override {
        attenuation = color(1, 1, 1);
        double ratio = rec.front_face ? (1.0/refraction_index) : refraction_index;

        vec3 unit = r_in.direction.normalize();
        double cos_theta = std::fmin(dot(unit * -1, rec.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

        bool cannot_refract = ratio * sin_theta > 1.0;
        vec3 direction;

        if (cannot_refract || reflectance(cos_theta, ratio) > random_double())
            direction = reflect(unit, rec.normal);
        else
            direction = refract(unit, rec.normal, ratio);

        scattered = Ray(rec.point, direction);
        return true;
    }

private:
    static double reflectance(double cosine, double ref_idx) {
        double r0 = (1-ref_idx) / (1+ref_idx);
        r0 = r0*r0;
        return r0 + (1-r0)*std::pow((1-cosine), 5);
    }

    static vec3 refract(const vec3& uv, const vec3& n, double ratio) {
        double cos_theta = std::fmin(dot(uv * -1, n), 1.0);
        vec3 r_perp = (uv + n * cos_theta) * ratio;
        vec3 r_para = n * -std::sqrt(std::fabs(1.0 - dot(r_perp, r_perp)));
        return r_perp + r_para;
    }
};