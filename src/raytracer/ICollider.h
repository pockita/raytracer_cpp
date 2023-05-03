/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include <optional>

#include "Point3.h"
#include "Vector3.h"

namespace raytracer {

using math::Point3;
using math::Vector3;

struct HitData final {
    HitData(const Vector3& dir, const Point3& p, const Vector3& unitOutsideN, int materialId, double t);

    Point3 p;
    Vector3 n;
    bool isOutside;
    int materialId;
    double t;
};

struct ICollider {
    virtual ~ICollider() = default;
    virtual std::optional<HitData> hit(const Point3& origin, const Vector3& dir, double minT, double maxT) const = 0;
};

} // raytracer
