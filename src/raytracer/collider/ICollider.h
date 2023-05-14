/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include <memory>
#include <optional>

#include "Point3.h"
#include "Vector3.h"

#include "BoundingBox.h"

namespace raytracer {

using math::Point3;
using math::Vector3;

struct HitData final {
    HitData(const Point3& p,
            const Vector3& unitN,
            bool isOutside,
            int materialId,
            double u,
            double v,
            double t);

    HitData(const Vector3& dir,
            const Point3& p,
            const Vector3& unitOutsideN,
            int materialId,
            double u,
            double v,
            double t);

    Point3 p;
    Vector3 n;
    bool isOutside;
    int materialId;
    double u;
    double v;
    double t;
};

struct ICollider {
    virtual ~ICollider() = default;
    virtual std::optional<HitData> hit(const Point3& origin, const Vector3& dir, double minT, double maxT) const = 0;
    virtual BoundingBox boundingBox() const = 0;
};

using ColliderPtr = std::shared_ptr<ICollider>;

} // raytracer
