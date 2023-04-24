/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include <array>
#include <cmath>
#include <cstddef>

namespace math {

struct Vector3 final {
    Vector3();
    Vector3(double x, double y, double z);

    static const Vector3 zero;
    static const Vector3 xUnit;
    static const Vector3 yUnit;
    static const Vector3 zUnit;
    static const Vector3 one;

    double operator[](std::size_t i) const { return coords_[i]; }
    double x() const { return coords_[0]; }
    double y() const { return coords_[1]; }
    double z() const { return coords_[2]; }
    double sqrLen() const { return coords_[0] * coords_[0] + coords_[1] * coords_[1] + coords_[2] * coords_[2]; }
    double len() const { return std::sqrt(sqrLen()); }
    bool isZero(double tol = 0.0) const { return sqrLen() <= tol * tol; }
    bool isUnit(double tol = 0.0) const { return 0.5 * std::fabs(sqrLen() - 1.0 - tol * tol) <= tol; }

    Vector3& operator+=(const Vector3& v);
    Vector3& operator-=(const Vector3& v);
    Vector3& operator*=(double a);
    Vector3& operator/=(double a);
    void normalize();

private:
    std::array<double, 3> coords_; // xyz
};

inline Vector3 operator-(const Vector3& v) {
    return {-v[0], -v[1], -v[2]};
}

inline Vector3 operator+(const Vector3& lv, const Vector3& rv) {
    return {lv[0] + rv[0], lv[1] + rv[1], lv[2] + rv[2]};
}

inline Vector3 operator-(const Vector3& lv, const Vector3& rv) {
    return {lv[0] - rv[0], lv[1] - rv[1], lv[2] - rv[2]};
}

inline Vector3 operator*(const Vector3& v, double a) {
    return {v[0] * a, v[1] * a, v[2] * a};
}

inline Vector3 operator*(double a, const Vector3& v) {
    return v * a;
}

Vector3 operator/(const Vector3& v, double a);

Vector3 normalized(const Vector3& v);

inline double dot(const Vector3& lv, const Vector3& rv) {
    return lv[0] * rv[0] + lv[1] * rv[1] + lv[2] * rv[2];
}

inline Vector3 cross(const Vector3& lv, const Vector3& rv) {
    return {
        lv[1] * rv[2] - lv[2] * rv[1],
        lv[2] * rv[0] - lv[0] * rv[2],
        lv[0] * rv[1] - lv[1] * rv[0]
    };
}

} // math
