#pragma once
#include "vec3.h"

struct Ray {
    point3 origin;
    vec3   direction;

    Ray() {}
    Ray(const point3& origin, const vec3& direction)
        : origin(origin), direction(direction) {}

    // Get point along ray at distance t
    point3 at(double t) const {
        return origin + direction * t;
    }
};