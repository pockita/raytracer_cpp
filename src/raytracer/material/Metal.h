/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include "Color.h"
#include "IMaterial.h"

namespace raytracer {

struct Metal final : IMaterial {
    Metal(const Color& albedo, double fuzz);
    std::optional<TraceData> trace(const Vector3& unitInV, const Vector3& unitN, bool isOutside) const override;
    Color getColor(double u, double v) const override { return albedo_; }

private:
    Color albedo_;
    double fuzz_;
};

} // raytracer
