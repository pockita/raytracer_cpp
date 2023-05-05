/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "BoundingBox.h"

#include <cmath>
#include <stdexcept>

namespace raytracer {

BoundingBox::BoundingBox(const Point3& min, const Point3& max) : min_(min), max_(max) {
    for (std::size_t i = 0; i < 3; ++i) {
        if (min[i] > max[i]) {
            throw std::invalid_argument{"min coordinates must be <= max coordinates"};
        }
    }
}

bool BoundingBox::hit(const Point3& origin, const Vector3& dir, double minT, double maxT) const {
    using std::swap;

    for (std::size_t i = 0; i < 3; ++i) {
        /*
         * (p - o) / +-0
         * if (p - o) != 0:  +-inf
         * if (p - o) = 0:   NaN
         * ray projection intersects box projection <-> (t0 is NaN) or (t1 is NaN) or (t1 != t2)
         */
        auto invD = 1.0 / dir[i];
        auto t0 = (min_[i] - origin[i]) * invD;
        auto t1 = (max_[i] - origin[i]) * invD;
        if (invD < 0.0) {
            swap(t0, t1);
        }

        // comparisons with NaN return false
        minT = t0 > minT ? t0 : minT;
        maxT = t1 < maxT ? t1 : maxT;
        if (minT > maxT || std::isinf(minT) && minT == maxT) {
            return false;
        }
    }
    return true;
}

void BoundingBox::enclose(const BoundingBox& box) {
    for (std::size_t i = 0; i < 3; ++i) {
        min_[i] = std::min(min_[i], box.min_[i]);
        max_[i] = std::max(max_[i], box.max_[i]);
    }
}

BoundingBox enclosing(const BoundingBox& lBox, const BoundingBox& rBox) {
    auto lMin = lBox.min();
    auto rMin = rBox.min();
    auto lMax = lBox.max();
    auto rMax = rBox.max();
    return {
        {std::min(lMin[0], rMin[0]), std::min(lMin[1], rMin[1]), std::min(lMin[2], rMin[2])},
        {std::max(lMax[0], rMax[0]), std::max(lMax[1], rMax[1]), std::max(lMax[2], rMax[2])}
    };
}

} // raytracer
