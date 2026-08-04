#pragma once
#include <cmath>

struct vec3 {
    double x, y, z;

    vec3() : x(0), y(0), z(0) {}
    vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    vec3 operator+(const vec3& v) const { return {x+v.x, y+v.y, z+v.z}; }
    vec3 operator-(const vec3& v) const { return {x-v.x, y-v.y, z-v.z}; }
    vec3 operator*(double t)      const { return {x*t,   y*t,   z*t};   }
    vec3 operator*(const vec3& v) const { return {x*v.x, y*v.y, z*v.z}; }
    vec3 operator/(double t)      const { return *this * (1/t);          }

    double length() const { return std::sqrt(x*x + y*y + z*z); }

    vec3 normalize() const { return *this / length(); }
};

// Utility functions
inline double dot(const vec3& a, const vec3& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

inline vec3 cross(const vec3& a, const vec3& b) {
    return {
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    };
}

// Alias
using point3 = vec3;
using color  = vec3;