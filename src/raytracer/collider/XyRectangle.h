/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include "ICollider.h"

namespace raytracer {

struct XyRectangle final : ICollider {
    XyRectangle(double minX, double maxX, double minY, double maxY, double z, int materialId);
    std::optional<HitData> hit(const Point3& origin, const Vector3& dir, double minT, double maxT) const override;
    BoundingBox boundingBox() const override;

private:
    double minX_;
    double maxX_;
    double minY_;
    double maxY_;
    double z_;
    int materialId_;
};

} // raytracer
