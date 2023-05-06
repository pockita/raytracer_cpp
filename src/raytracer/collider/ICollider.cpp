/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "ICollider.h"

#include <stdexcept>

#include "raytracer_utils.h"

namespace raytracer {

HitData::HitData(const Vector3& dir,
                 const Point3& p,
                 const Vector3& unitOutsideN,
                 int materialId,
                 double u,
                 double v,
                 double t)
        : p(p),
          n(unitOutsideN),
          isOutside(dot(dir, unitOutsideN) <= 0.0),
          materialId(materialId),
          u(u),
          v(v),
          t(t) {

    if (!unitOutsideN.isUnit(getTol())) {
        throw std::invalid_argument{"unitOutsideN must be unit"};
    }
    if (!isOutside) {
        n *= -1.0;
    }

    if (u < 0.0) {
        throw std::invalid_argument{"u must be >= 0"};
    }
    if (u > 1.0) {
        throw std::invalid_argument{"u must be <= 1"};
    }
    if (v < 0.0) {
        throw std::invalid_argument{"v must be >= 0"};
    }
    if (v > 1.0) {
        throw std::invalid_argument{"v must be <= 1"};
    }
}

} // raytracer
