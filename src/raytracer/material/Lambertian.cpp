/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "Lambertian.h"

#include <stdexcept>

#include "raytracer_utils.h"

namespace raytracer {

Lambertian::Lambertian(TexturePtr pTexture) : pTexture_(std::move(pTexture)) {
    if (!pTexture_) {
        throw std::invalid_argument{"pTexture must be not nullptr"};
    }
}

std::optional<TraceData> Lambertian::trace(const Vector3& unitInV, const Vector3& unitN, bool isOutside) const {
    if (!unitN.isUnit(getTol())) {
        throw std::invalid_argument{"unitN must be unit"};
    }
    const auto v = unitN + randomUnitVector();
    return std::make_optional<TraceData>(v.isZero(getTol()) ? unitN : v);
}

} // raytracer
