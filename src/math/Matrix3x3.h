/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include <array>
#include <cstddef>

#include "Point3.h"
#include "Vector3.h"

namespace math {

struct Matrix3x3 final {
    static constexpr std::size_t nDim = 3;

    using Elements = std::array<std::array<double, nDim>, nDim>;

    Matrix3x3();
    explicit Matrix3x3(const Elements& elems);

    static const Matrix3x3 zero;
    static const Matrix3x3 identity;

    static Matrix3x3 xRotation(double xr);
    static Matrix3x3 yRotation(double yr);
    static Matrix3x3 zRotation(double zr);
    static Matrix3x3 scale(double xs, double ys, double zs);

    double at(std::size_t i, std::size_t j) const { return elems_[i][j]; }

    double& at(std::size_t i, std::size_t j) { return elems_[i][j]; }

private:
    Elements elems_;
};

Matrix3x3 operator*(const Matrix3x3& lm, const Matrix3x3& rm);

Vector3 operator*(const Matrix3x3& m, const Vector3& v);

Point3 operator*(const Matrix3x3& m, const Point3& p);

} // math
