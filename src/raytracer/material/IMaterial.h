/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include <memory>
#include <optional>

#include "Vector3.h"

#include "Color.h"

namespace raytracer {

using math::Vector3;

struct TraceData final {
    explicit TraceData(const Vector3& outV);

    Vector3 outV;
};

struct IMaterial {
    virtual ~IMaterial() = default;
    virtual std::optional<TraceData> trace(const Vector3& unitInV, const Vector3& unitN, bool isOutside) const = 0;
    virtual Color getColor(double u, double v) const = 0;
};

using MaterialPtr = std::shared_ptr<IMaterial>;

} // raytracer
