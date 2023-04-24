/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "Sphere.h"

#include <cmath>
#include <stdexcept>

#include "raytracer_utils.h"

namespace raytracer {

Sphere::Sphere(const Point3& center, double radius) : center_(center), radius_(radius) {
    if (radius <= getTol()) {
        throw std::invalid_argument{"radius must be > 0"};
    }
}

std::optional<HitData> Sphere::hit(const Point3& origin, const Vector3& dir, double minT, double maxT) const {
    const auto a = dir.sqrLen();
    if (a <= getSqrTol()) {
        throw std::invalid_argument{"dir must be not 0"};
    }
    const auto centerToOrigin = origin - center_;
    const auto halfB = dot(dir, centerToOrigin);
    const auto c = centerToOrigin.sqrLen() - radius_ * radius_;
    const auto d = halfB * halfB - a * c;
    if (d < 0.0) {
        return std::nullopt;
    }
    const auto sqrtD = std::sqrt(d);

    auto t = (-halfB - sqrtD) / a;
    if (t < minT || t > maxT) {
        t = (-halfB + sqrtD) / a;
        if (t < minT || t > maxT) {
            return std::nullopt;
        }
    }

    const auto p = moved(origin, dir, t);
    return std::make_optional<HitData>(dir, p, (p - center_) / radius_, t);
}

} // raytracer
