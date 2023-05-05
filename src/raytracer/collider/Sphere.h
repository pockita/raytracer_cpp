/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include "ICollider.h"

namespace raytracer {

struct Sphere final : ICollider {
    Sphere(const Point3& center, double radius, int materialId);

    std::optional<HitData> hit(const Point3& origin, const Vector3& dir, double minT, double maxT) const override;
    BoundingBox boundingBox() const override;

private:
    Point3 center_;
    double radius_;
    int materialId_;
};

} // raytracer
