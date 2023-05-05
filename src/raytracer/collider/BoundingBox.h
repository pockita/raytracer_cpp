/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include "Point3.h"
#include "Vector3.h"

namespace raytracer {

using math::Point3;
using math::Vector3;

/**
 * Axis aligned bounding box (AABB)
 */
struct BoundingBox final {
    BoundingBox(const Point3& min, const Point3& max);

    Point3 min() const { return min_; }
    Point3 max() const { return max_; }
    bool hit(const Point3& origin, const Vector3& dir, double minT, double maxT) const;

    void enclose(const BoundingBox& box);

private:
    Point3 min_;
    Point3 max_;
};

BoundingBox enclosing(const BoundingBox& lBox, const BoundingBox& rBox);

} // raytracer
