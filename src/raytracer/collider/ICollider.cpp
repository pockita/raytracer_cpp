/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "ICollider.h"

#include <stdexcept>

#include "raytracer_utils.h"

namespace raytracer {

void validateUv(double u, double v) {
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

HitData::HitData(const Point3& p,
                 const Vector3& unitN,
                 bool isOutside,
                 int materialId,
                 double u,
                 double v,
                 double t)
        : p(p),
          n(unitN),
          isOutside(isOutside),
          materialId(materialId),
          u(u),
          v(v),
          t(t) {

    if (!unitN.isUnit(getTol())) {
        throw std::invalid_argument{"unitN must be unit"};
    }

    validateUv(u, v);
}

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

    validateUv(u, v);
}

} // raytracer
