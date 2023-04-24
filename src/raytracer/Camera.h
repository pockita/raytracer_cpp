/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include "Point3.h"
#include "Vector3.h"

namespace raytracer {

using math::Point3;
using math::Vector3;

struct Camera final {
    Camera(const Point3& lookFrom,
           const Point3& lookAt,
           const Vector3& viewUp,
           double verticalFieldOfView,
           double aspectRatio,
           double focusDist,
           double aperture);

    std::pair<Point3, Vector3> calcRay(double u, double v) const;

private:
    Point3 origin_;
    Vector3 xUnit_;
    Vector3 yUnit_;
    Vector3 zUnit_;
    double viewportWidth_ = 0.0; // for focusDist = 1
    double viewportHeight_ = 0.0; // for focusDist = 1
    double focusDist_ = 0.0;
    double lensRadius_ = 0.0;
};

} // raytracer
