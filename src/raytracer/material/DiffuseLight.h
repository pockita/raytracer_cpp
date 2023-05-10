/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include "IMaterial.h"
#include "ITexture.h"

namespace raytracer {

struct DiffuseLight final : IMaterial {
    explicit DiffuseLight(TexturePtr pTexture);
    std::optional<TraceData> trace(const Vector3& unitInV, const Vector3& unitN, bool isOutside) const override { return std::nullopt; }
    Color getColor(double u, double v, const Point3& p) const override;
    Color getEmittedColor(double u, double v, const Point3& p) const override { return pTexture_->getColor(u, v, p); }

private:
    TexturePtr pTexture_;
};

} // raytracer
