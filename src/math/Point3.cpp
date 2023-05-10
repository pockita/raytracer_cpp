/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "Point3.h"

#include <iostream>

namespace math {

Point3::Point3() : coords_{0.0, 0.0, 0.0} {}

Point3::Point3(double x, double y, double z) : coords_{x, y, z} {}

const Point3 Point3::origin{0.0, 0.0, 0.0};

Point3& Point3::operator+=(const Vector3& v) {
    for (std::size_t i = 0; i < coords_.size(); ++i) {
        coords_[i] += v[i];
    }
    return *this;
}

Point3& Point3::operator-=(const Vector3& v) {
    for (std::size_t i = 0; i < coords_.size(); ++i) {
        coords_[i] -= v[i];
    }
    return *this;
}

void Point3::move(const Vector3& v, double t) {
    for (std::size_t i = 0; i < coords_.size(); ++i) {
        coords_[i] += (v[i] * t);
    }
}

std::ostream& operator<<(std::ostream& os, const Point3& p) {
    return os << '(' << p[0] << ", " << p[1] << ", " << p[2] << ')';
}

} // math
