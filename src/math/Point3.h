/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include <array>
#include <cstddef>
#include <iosfwd>

#include "Vector3.h"

namespace math {

struct Point3 final {
    Point3();
    Point3(double x, double y, double z);

    static const Point3 origin;

    double operator[](std::size_t i) const { return coords_[i]; }
    double x() const { return coords_[0]; }
    double y() const { return coords_[1]; }
    double z() const { return coords_[2]; }

    double& operator[](std::size_t i) { return coords_[i]; }
    Point3& operator+=(const Vector3& v);
    Point3& operator-=(const Vector3& v);
    void move(const Vector3& v, double t);

private:
    std::array<double, 3> coords_; // xyz
};

inline Point3 operator+(const Point3& p, const Vector3& v) {
    return {p[0] + v[0], p[1] + v[1], p[2] + v[2]};
}

inline Point3 operator-(const Point3& p, const Vector3& v) {
    return {p[0] - v[0], p[1] - v[1], p[2] - v[2]};
}

inline Vector3 operator-(const Point3& lp, const Point3& rp) {
    return {lp[0] - rp[0], lp[1] - rp[1], lp[2] - rp[2]};
}

inline Point3 moved(const Point3& p, const Vector3& v, double t) {
    return {p[0] + v[0] * t, p[1] + v[1] * t, p[2] + v[2] * t};
}

inline double sqrDist(const Point3& p, const Point3& q) {
    return (p - q).sqrLen();
}

inline double dist(const Point3& p, const Point3& q) {
    return (p - q).len();
}

std::ostream& operator<<(std::ostream& os, const Point3& p);

} // math
