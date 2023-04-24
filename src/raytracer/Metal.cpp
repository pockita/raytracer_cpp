/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "Metal.h"

#include <stdexcept>

#include "raytracer_utils.h"

namespace raytracer {

Metal::Metal(const Color& albedo, double fuzz) : albedo_(albedo), fuzz_(fuzz) {
    if (fuzz < 0.0) {
        throw std::invalid_argument{"fuzz must be >= 0"};
    }
    if (fuzz > 1.0) {
        throw std::invalid_argument{"fuzz must be <= 1"};
    }
}

std::optional<TraceData> Metal::trace(const Vector3& unitInV, const Vector3& unitN, bool isOutside) const {
    if (!unitInV.isUnit(getTol())) {
        throw std::invalid_argument{"unitInV must be unit"};
    }
    const auto reflectedV = reflected(unitInV, unitN); // nearly unit, but the length error can be > tolerance
    const auto v = reflectedV + fuzz_ * randomVectorInUnitSphere();
    if (dot(v, unitN) <= 0.0) {
        return std::nullopt;
    }
    return std::make_optional<TraceData>(albedo_, v.isZero(getTol()) ? reflectedV : v);
}

} // raytracer
