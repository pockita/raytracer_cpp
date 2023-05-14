/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include "Matrix3x3.h"

#include "ICollider.h"

namespace raytracer {

using math::Matrix3x3;

/**
 * x-rotation, y-rotation, z-rotation, translation
 */
struct Transformed final : ICollider {
    Transformed(ColliderPtr pCollider,
                double xr,
                double yr,
                double zr,
                const Vector3& offset);

    std::optional<HitData> hit(const Point3& origin, const Vector3& dir, double minT, double maxT) const override;
    BoundingBox boundingBox() const override { return box_; }

private:
    ColliderPtr pCollider_;
    Matrix3x3 rotation_;
    Matrix3x3 reverseRotation_;
    Vector3 offset_;
    BoundingBox box_;
};

} // raytracer
