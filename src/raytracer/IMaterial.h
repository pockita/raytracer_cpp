/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include <optional>

#include "Vector3.h"

#include "Color.h"

namespace raytracer {

using math::Vector3;

struct TraceData final {
    TraceData(const Color& attenuation, const Vector3& outV);

    Color attenuation;
    Vector3 outV;
};

struct IMaterial {
    virtual ~IMaterial() = default;
    virtual std::optional<TraceData> trace(const Vector3& unitInV, const Vector3& unitN, bool isOutside) const = 0;
};

} // raytracer
