/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "Transformed.h"

namespace raytracer {

BoundingBox generateBoundingBox(const ColliderPtr& pCollider, const Matrix3x3& rotation, const Vector3& offset) {
    if (!pCollider) {
        throw std::invalid_argument{"pCollider must be not null"};
    }

    const auto box = pCollider->boundingBox();
    const std::array<Point3, 2> points{box.min(), box.max()};

    constexpr auto inf = std::numeric_limits<double>::infinity();
    Point3 min{inf, inf, inf};
    Point3 max{-inf, -inf, -inf};
    for (const auto& px : points) {
        for (const auto& py : points) {
            for (const auto& pz : points) {
                const auto p = rotation * Point3{px.x(), py.y(), pz.z()};
                for (std::size_t i = 0; i < 3; ++i) {
                    min[i] = std::fmin(min[i], p[i]);
                    max[i] = std::fmax(max[i], p[i]);
                }
            }
        }
    }

    return {min + offset, max + offset};
}

Transformed::Transformed(ColliderPtr pCollider,
                         double xr,
                         double yr,
                         double zr,
                         const Vector3& offset)

        : pCollider_(std::move(pCollider)),
          rotation_(Matrix3x3::zRotation(zr) * Matrix3x3::yRotation(yr) * Matrix3x3::xRotation(xr)),
          reverseRotation_(Matrix3x3::xRotation(-xr) * Matrix3x3::yRotation(-yr) * Matrix3x3::zRotation(-zr)),
          offset_(offset),
          box_(generateBoundingBox(pCollider_, rotation_, offset_)) {

    if (!pCollider_) {
        throw std::invalid_argument{"pCollider must be not null"};
    }
}

std::optional<HitData> Transformed::hit(const Point3& origin, const Vector3& dir, double minT, double maxT) const {
    const auto reversedOrigin = reverseRotation_ * (origin - offset_);
    const auto reversedDir = reverseRotation_ * dir;
    auto optHit = pCollider_->hit(reversedOrigin, reversedDir, minT, maxT);
    if (!optHit) {
        return std::nullopt;
    }

    const auto& hit = *optHit;
    return std::make_optional<HitData>(rotation_ * hit.p + offset_,
                                       rotation_ * hit.n,
                                       hit.isOutside,
                                       hit.materialId,
                                       hit.u,
                                       hit.v,
                                       hit.t);
}

} // raytracer
