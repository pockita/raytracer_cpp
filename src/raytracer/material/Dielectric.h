/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include "IMaterial.h"

namespace raytracer {

struct Dielectric final : IMaterial {
    explicit Dielectric(double refractiveIndex);
    std::optional<TraceData> trace(const Vector3& unitInV, const Vector3& unitN, bool isOutside) const override;

private:
    double refractiveIndex_;
};

} // raytracer
