/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include "IMaterial.h"
#include "ITexture.h"

namespace raytracer {

struct Lambertian final : IMaterial {
    explicit Lambertian(TexturePtr pTexture);
    std::optional<TraceData> trace(const Vector3& unitInV, const Vector3& unitN, bool isOutside) const override;
    Color getColor(double u, double v, const Point3& p) const override { return pTexture_->getColor(u, v, p); }
    Color getEmittedColor(double u, double v, const Point3& p) const override { return Color::black; }

private:
    TexturePtr pTexture_;
};

} // raytracer
