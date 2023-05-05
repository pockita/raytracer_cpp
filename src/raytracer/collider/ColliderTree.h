/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include <cstddef>
#include <vector>

#include "ICollider.h"

namespace raytracer {

/**
 * Bounding volume hierarchy (BVH)
 */
struct ColliderTree final : ICollider {
    ColliderTree(std::vector<ColliderPtr>& colliderPtrs, std::size_t start, std::size_t end);

    std::optional<HitData> hit(const Point3& origin, const Vector3& dir, double minT, double maxT) const override;
    BoundingBox boundingBox() const override { return box_; }

private:
    ColliderPtr pLeft_;
    ColliderPtr pRight_;
    BoundingBox box_;
};

} // raytracer
