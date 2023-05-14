/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "Matrix3x3.h"

#include <cmath>

#include "math_utils.h"

namespace math {

Matrix3x3::Matrix3x3() : elems_(zero.elems_) {}

Matrix3x3::Matrix3x3(const Elements& elems) : elems_(elems) {}

const Matrix3x3 Matrix3x3::zero{{{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0}
}}};

const Matrix3x3 Matrix3x3::identity{{{
    {1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0}
}}};

Matrix3x3 Matrix3x3::xRotation(double xr) {
    xr = degToRad(xr);
    const auto xCos = std::cos(xr);
    const auto xSin = std::sin(xr);
    return Matrix3x3{{{
        {1.0,  0.0,   0.0  },
        {0.0,  xCos,  -xSin},
        {0.0,  xSin,  xCos }
    }}};
}

Matrix3x3 Matrix3x3::yRotation(double yr) {
    yr = degToRad(yr);
    const auto yCos = std::cos(yr);
    const auto ySin = std::sin(yr);
    return Matrix3x3{{{
        {yCos,   0.0,  ySin},
        {0.0,    1.0,  0.0 },
        {-ySin,  0.0,  yCos}
    }}};
}

Matrix3x3 Matrix3x3::zRotation(double zr) {
    zr = degToRad(zr);
    const auto zCos = std::cos(zr);
    const auto zSin = std::sin(zr);
    return Matrix3x3{{{
        {zCos,  -zSin,  0.0},
        {zSin,  zCos,   0.0},
        {0.0,   0.0,    1.0}
    }}};
}

Matrix3x3 Matrix3x3::scale(double xs, double ys, double zs) {
    return Matrix3x3{{{
        {xs,  0.0, 0.0},
        {0.0, ys,  0.0},
        {0.0, 0.0, zs }
    }}};
}

Matrix3x3 operator*(const Matrix3x3& lm, const Matrix3x3& rm) {
    auto res = Matrix3x3::zero;
    for (std::size_t i = 0; i < Matrix3x3::nDim; ++i) {
        for (std::size_t j = 0; j < Matrix3x3::nDim; ++j) {
            for (std::size_t k = 0; k < Matrix3x3::nDim; ++k) {
                res.at(i, j) += (lm.at(i, k) * rm.at(k, j));
            }
        }
    }
    return res;
}

template<typename T>
T mul(const Matrix3x3& m, const T& t) {
    T res{0.0, 0.0, 0.0};
    for (std::size_t i = 0; i < Matrix3x3::nDim; ++i) {
        for (std::size_t j = 0; j < Matrix3x3::nDim; ++j) {
            res[i] += (m.at(i, j) * t[j]);
        }
    }
    return res;
}

Vector3 operator*(const Matrix3x3& m, const Vector3& v) { return mul(m, v); }

Point3 operator*(const Matrix3x3& m, const Point3& p) { return mul(m, p); }

} // math
