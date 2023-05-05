/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "Dielectric.h"

#include <cmath>
#include <stdexcept>

#include "raytracer_utils.h"

namespace raytracer {

double calcReflectance(double cosTheta, double refractiveRatio) {
    if (cosTheta < -1.0 || cosTheta > 1.0) {
        throw std::invalid_argument{"cosTheta must be [-1, 1]"};
    }
    if (refractiveRatio <= getTol()) {
        throw std::invalid_argument{"refractiveRatio must be > 0"};
    }
    // Schlick's approximation
    auto r0 = (1.0 - refractiveRatio) / (1.0 + refractiveRatio);
    r0 = r0 * r0;
    return r0 + (1.0 - r0) * std::pow(1.0 - cosTheta, 5);
}

Dielectric::Dielectric(double refractiveIndex) : refractiveIndex_(refractiveIndex) {
    if (refractiveIndex <= getTol()) {
        throw std::invalid_argument{"refractiveIndex must be > 0"};
    }
}

std::optional<TraceData> Dielectric::trace(const Vector3& unitInV, const Vector3& unitN, bool isOutside) const {
    if (!unitInV.isUnit(getTol())) {
        throw std::invalid_argument{"unitInV must be unit"};
    }
    if (!unitN.isUnit(getTol())) {
        throw std::invalid_argument{"unitN must be unit"};
    }

    const auto refractiveRatio = isOutside ? 1.0 / refractiveIndex_ : refractiveIndex_;
    const auto cosTheta = std::fmin(-dot(unitInV, unitN), 1.0);
    if (cosTheta < 0.0) {
        throw std::invalid_argument{"angle between unitInV (incident vector) and unitN (local normal) must be in [90, 180]"};
    }
    const auto sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

    const auto canRefract = refractiveRatio * sinTheta <= 1.0 && calcReflectance(cosTheta, refractiveRatio) < randomDoubleInUnitInterval();
    const auto v = canRefract ? refracted(unitInV, unitN, refractiveRatio) : reflected(unitInV, unitN);
    return std::make_optional<TraceData>(Color::white, v);
}

} // raytracer
