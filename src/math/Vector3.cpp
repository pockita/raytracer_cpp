/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "Vector3.h"

#include <stdexcept>

namespace math {

Vector3::Vector3() : coords_{0.0, 0.0, 0.0} {}

Vector3::Vector3(double x, double y, double z) : coords_{x, y, z} {}

const Vector3 Vector3::zero{0.0, 0.0, 0.0};
const Vector3 Vector3::xUnit{1.0, 0.0, 0.0};
const Vector3 Vector3::yUnit{0.0, 1.0, 0.0};
const Vector3 Vector3::zUnit{0.0, 0.0, 1.0};
const Vector3 Vector3::one{1.0, 1.0, 1.0};

Vector3& Vector3::operator+=(const Vector3& v) {
    for (std::size_t i = 0; i < coords_.size(); ++i) {
        coords_[i] += v.coords_[i];
    }
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& v) {
    for (std::size_t i = 0; i < coords_.size(); ++i) {
        coords_[i] -= v.coords_[i];
    }
    return *this;
}

Vector3& Vector3::operator*=(double a) {
    for (auto& c : coords_) {
        c *= a;
    }
    return *this;
}

Vector3& Vector3::operator/=(double a) {
    if (a == 0.0) {
        throw std::invalid_argument{"a must be not 0"};
    }
    for (auto& c : coords_) {
        c /= a;
    }
    return *this;
}

void Vector3::normalize() {
    auto l = len();
    if (l == 0.0) {
        throw std::logic_error{"vector must be not 0"};
    }
    for (auto& c: coords_) {
        c /= l;
    }
}

Vector3 operator/(const Vector3& v, double a) {
    if (a == 0.0) {
        throw std::invalid_argument{"a must be not 0"};
    }
    return {v[0] / a, v[1] / a, v[2] / a};
}

Vector3 normalized(const Vector3& v) {
    auto l = v.len();
    if (l == 0.0) {
        throw std::invalid_argument{"v must be not 0"};
    }
    return {v[0] / l, v[1] / l, v[2] / l};
}

} // math
