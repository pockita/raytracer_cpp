/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include <array>

#include "Point3.h"
#include "Vector3.h"

namespace raytracer {

using math::Point3;
using math::Vector3;

struct Perlin {
    Perlin();
    double noise(const Point3& p) const;
    double turbulence(const Point3& p, int depth = 7) const;

private:
    static constexpr int n_ = 256;

    static std::array<int, n_> generatePermutation();

    std::array<Vector3, n_> randomUnitVectors_;
    std::array<int, n_> permutation_x_;
    std::array<int, n_> permutation_y_;
    std::array<int, n_> permutation_z_;
};

} // raytracer
