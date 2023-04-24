/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "ICollider.h"

#include <stdexcept>

#include "raytracer_utils.h"

namespace raytracer {

HitData::HitData(const Vector3& dir, const Point3& p, const Vector3& unitOutsideN, double t)
        : p(p), n(unitOutsideN), isOutside(dot(dir, unitOutsideN) <= 0.0), t(t) {

    if (!unitOutsideN.isUnit(getTol())) {
        throw std::invalid_argument{"unitOutsideN must be unit"};
    }
    if (!isOutside) {
        n *= -1.0;
    }
}

} // raytracer
