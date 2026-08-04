#include <iostream>
#include <fstream>
#include <memory>
#include "vec3.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"

const int MAX_DEPTH = 50;

color ray_color(const Ray& r, const Hittable& world, int depth) {
    if (depth <= 0) return color(0,0,0);
    HitRecord rec;
    if (world.hit(r, 0.001, 1e9, rec)) {
        Ray scattered;
        color attenuation;
        if (rec.material->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return color(0,0,0);
    }
    vec3 unit = r.direction.normalize();
    double t = 0.5 * (unit.y + 1.0);
    return color(1,1,1) * (1.0-t) + color(0.5, 0.7, 1.0) * t;
}

HittableList random_scene() {
    HittableList world;

    // Ground
    auto ground = std::make_shared<Lambertian>(color(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(point3(0, -1000, 0), 1000, ground));

    // Random small spheres
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double choose_mat = random_double();
            point3 center(
                a + 0.9 * random_double(),
                0.2,
                b + 0.9 * random_double()
            );

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                if (choose_mat < 0.8) {
                    // Diffuse
                    color albedo(
                        random_double()*random_double(),
                        random_double()*random_double(),
                        random_double()*random_double()
                    );
                    world.add(std::make_shared<Sphere>(center, 0.2,
                        std::make_shared<Lambertian>(albedo)));
                } else if (choose_mat < 0.95) {
                    // Metal
                    color albedo(
                        0.5*(1+random_double()),
                        0.5*(1+random_double()),
                        0.5*(1+random_double())
                    );
                    double fuzz = 0.5 * random_double();
                    world.add(std::make_shared<Sphere>(center, 0.2,
                        std::make_shared<Metal>(albedo, fuzz)));
                } else {
                    // Glass
                    world.add(std::make_shared<Sphere>(center, 0.2,
                        std::make_shared<Dielectric>(1.5)));
                }
            }
        }
    }

    // Three big spheres
    world.add(std::make_shared<Sphere>(point3(0,  1, 0), 1.0,
        std::make_shared<Dielectric>(1.5)));
    world.add(std::make_shared<Sphere>(point3(-4, 1, 0), 1.0,
        std::make_shared<Lambertian>(color(0.4, 0.2, 0.1))));
    world.add(std::make_shared<Sphere>(point3(4,  1, 0), 1.0,
        std::make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0)));

    return world;
}

int main() {
    // Image
    int image_width  = 400;
    int image_height = 225;
    int samples      = 50;

    // Scene
    HittableList world = random_scene();

    // Camera
    point3 lookfrom(13, 2, 3);
    point3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    double vfov = 20.0;
    double aspect = double(image_width) / image_height;

    double theta = vfov * 3.14159265 / 180.0;
    double h = std::tan(theta/2);
    double vp_h = 2.0 * h;
    double vp_w = aspect * vp_h;

    vec3 w = (lookfrom - lookat).normalize();
    vec3 u = cross(vup, w).normalize();
    vec3 v = cross(w, u);

    point3 origin     = lookfrom;
    vec3 horizontal   = u * vp_w;
    vec3 vertical     = v * vp_h;
    point3 lower_left = origin - horizontal/2 - vertical/2 - w;

    // Render
    std::ofstream file("../output/image.ppm");
    file << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; j--) {
        std::cout << "Scanlines remaining: " << j << "  \r" << std::flush;
        for (int i = 0; i < image_width; i++) {
            color pixel(0,0,0);
            for (int s = 0; s < samples; s++) {
                double uu = (i + random_double()) / (image_width  - 1);
                double vv = (j + random_double()) / (image_height - 1);
                Ray r(origin, lower_left + horizontal*uu + vertical*vv - origin);
                pixel = pixel + ray_color(r, world, MAX_DEPTH);
            }
            double scale = 1.0 / samples;
            int ir = int(255.99 * std::sqrt(pixel.x * scale));
            int ig = int(255.99 * std::sqrt(pixel.y * scale));
            int ib = int(255.99 * std::sqrt(pixel.z * scale));
            file << ir << " " << ig << " " << ib << "\n";
        }
    }

    file.close();
    std::cout << "\nDone!\n";
}