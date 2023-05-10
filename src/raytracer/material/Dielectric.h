/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include "IMaterial.h"

namespace raytracer {

struct Dielectric final : IMaterial {
    explicit Dielectric(double refractiveIndex);
    std::optional<TraceData> trace(const Vector3& unitInV, const Vector3& unitN, bool isOutside) const override;
    Color getColor(double u, double v, const Point3& p) const override { return Color::white; }
    Color getEmittedColor(double u, double v, const Point3& p) const override { return Color::black; }

private:
    double refractiveIndex_;
};

} // raytracer
