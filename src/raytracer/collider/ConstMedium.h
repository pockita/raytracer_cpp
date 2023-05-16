/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include "ICollider.h"

namespace raytracer {

struct ConstMedium final : ICollider {
    ConstMedium(ColliderPtr pBoundary, double density, int materialId);
    std::optional<HitData> hit(const Point3& origin, const Vector3& dir, double minT, double maxT) const override;
    BoundingBox boundingBox() const override { return pBoundary_->boundingBox(); }

private:
    ColliderPtr pBoundary_;
    double negInvDensity_;
    int materialId_;
};

} // raytracer
