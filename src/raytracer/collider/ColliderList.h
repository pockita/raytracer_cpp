/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include <vector>

#include "ICollider.h"

namespace raytracer {

struct ColliderList final : ICollider {
    explicit ColliderList(const std::vector<ColliderPtr>& colliderPtrs);

    std::optional<HitData> hit(const Point3& origin, const Vector3& dir, double minT, double maxT) const override;
    BoundingBox boundingBox() const override { return box_; }

private:
    std::vector<ColliderPtr> colliderPtrs_;
    BoundingBox box_;
};

} // raytracer
