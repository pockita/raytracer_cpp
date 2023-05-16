/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "ConstMedium.h"

#include <cmath>
#include <stdexcept>

#include "raytracer_utils.h"

namespace raytracer {

ConstMedium::ConstMedium(ColliderPtr pBoundary, double density, int materialId)
        : pBoundary_(std::move(pBoundary)), negInvDensity_(-1.0 / density), materialId_(materialId) {

    if (!pBoundary_) {
        throw std::invalid_argument{"pBoundary must be not nullptr"};
    }
    if (density <= 0.0) {
        throw std::invalid_argument{"density must be > 0"};
    }
}

std::optional<HitData> ConstMedium::hit(const Point3& origin, const Vector3& dir, double minT, double maxT) const {
    constexpr auto inf = std::numeric_limits<double>::infinity();

    const auto optHit1 = pBoundary_->hit(origin, dir, -inf, inf);
    if (!optHit1) {
        return std::nullopt;
    }
    auto t1 = optHit1->t;

    const auto optHit2 = pBoundary_->hit(origin, dir, t1 + 1.0e-6, inf);
    if (!optHit2) {
        return std::nullopt;
    }
    auto t2 = optHit2->t;

    if (t1 < minT) {
        t1 = minT;
    }
    if (t2 > maxT) {
        t2 = maxT;
    }
    if (t1 >= t2) {
        return std::nullopt;
    }

    const auto dirLen = dir.len();
    const auto distInside = (t2 - t1) * dirLen;
    const auto hitDist = negInvDensity_ * std::log(randomDoubleInUnitInterval());
    if (hitDist > distInside) {
        return std::nullopt;
    }
    const auto t = t1 + hitDist / dirLen;

    // n, isOutside, u, v are arbitrary
    return std::make_optional<HitData>(moved(origin, dir, t), Vector3::xUnit, true, materialId_, 0.0, 0.0, t);
}

} // raytracer
