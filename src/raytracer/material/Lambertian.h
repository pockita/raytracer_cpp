/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include "Color.h"
#include "IMaterial.h"

namespace raytracer {

struct Lambertian final : IMaterial {
    explicit Lambertian(const Color& albedo);
    std::optional<TraceData> trace(const Vector3& unitInV, const Vector3& unitN, bool isOutside) const override;

private:
    Color albedo_;
};

} // raytracer