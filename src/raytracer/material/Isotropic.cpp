/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "Isotropic.h"

#include <stdexcept>

#include "raytracer_utils.h"

namespace raytracer {

Isotropic::Isotropic(TexturePtr pTexture) : pTexture_(std::move(pTexture)) {
    if (!pTexture_) {
        throw std::invalid_argument{"pTexture must be not nullptr"};
    }
}

std::optional<TraceData> Isotropic::trace(const Vector3& unitInV, const Vector3& unitN, bool isOutside) const {
    return std::make_optional<TraceData>(randomUnitVector());
}

} // raytracer
