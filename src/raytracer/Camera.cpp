/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "Camera.h"

#include <cmath>
#include <stdexcept>

#include "math_utils.h"

#include "raytracer_utils.h"

namespace raytracer {

Camera::Camera(const Point3& lookFrom,
               const Point3& lookAt,
               const Vector3& viewUp,
               double verticalFieldOfView,
               double aspectRatio,
               double focusDist,
               double aperture)

        : origin_(lookFrom) {

    using math::degToRad;

    const Vector3 z = lookFrom - lookAt;
    const Vector3 x = cross(viewUp, z);

    if (z.isZero(getTol())) {
        throw std::invalid_argument{"lookFrom and lookAt must differ"};
    }
    if (viewUp.isZero(getTol())) {
        throw std::invalid_argument{"viewUp must be not 0"};
    }
    if (x.isZero(getTol())) {
        throw std::invalid_argument{"look direction and viewUp must be not parallel"};
    }

    zUnit_ = normalized(z);
    xUnit_ = normalized(x);
    yUnit_ = cross(zUnit_, xUnit_);

    if (verticalFieldOfView <= 0.0) {
        throw std::invalid_argument{"verticalFieldOfView must be > 0"};
    }
    if (verticalFieldOfView > 180.0) {
        throw std::invalid_argument{"verticalFieldOfView must be <= 180"};
    }
    if (aspectRatio <= 0.0) {
        throw std::invalid_argument{"aspectRatio must be > 0"};
    }
    if (focusDist <= getTol()) {
        throw std::invalid_argument{"focusDist must be > 0"};
    }
    if (aperture < 0.0) {
        throw std::invalid_argument{"aperture must be >= 0"};
    }

    viewportHeight_ = 2.0 * std::tan(0.5 * degToRad(verticalFieldOfView));
    viewportWidth_ = aspectRatio * viewportHeight_;
    focusDist_ = focusDist;
    lensRadius_ = 0.5 * aperture;
}

std::pair<Point3, Vector3> Camera::calcRay(double u, double v) const {
    auto dir = (u - 0.5) * viewportWidth_ * xUnit_ + (v - 0.5) * viewportHeight_ * yUnit_ - zUnit_;
    dir *= focusDist_;
    auto offset = lensRadius_ * randomVectorInUnitXYDisk();
    return {origin_ + offset, dir - offset};
}

} // raytracer
