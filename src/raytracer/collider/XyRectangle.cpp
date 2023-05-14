/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "XyRectangle.h"

#include <stdexcept>

namespace raytracer {

XyRectangle::XyRectangle(double minX, double maxX, double minY, double maxY, double z, int materialId)
        : minX_(minX),
          maxX_(maxX),
          minY_(minY),
          maxY_(maxY),
          z_(z),
          materialId_(materialId) {

    if (minX > maxX) {
        throw std::invalid_argument{"minX must be < maxX"};
    }
    if (minY > maxY) {
        throw std::invalid_argument{"minY must be < maxY"};
    }
}

std::optional<HitData> XyRectangle::hit(const Point3& origin, const Vector3& dir, double minT, double maxT) const {
    const auto t = (z_ - origin.z()) / dir.z();
    if (t < minT || t > maxT || std::isinf(t) || std::isnan(t))
        return std::nullopt;

    const auto p = moved(origin, dir, t);
    if (p.x() < minX_ || p.x() > maxX_ || p.y() < minY_ || p.y() > maxY_)
        return std::nullopt;

    const auto u = (p.x() - minX_) / (maxX_ - minX_);
    const auto v = (p.y() - minY_) / (maxY_ - minY_);
    return std::make_optional<HitData>(dir, p, Vector3::zUnit, materialId_, u, v, t);
}

BoundingBox XyRectangle::boundingBox() const {
    static constexpr double thickness = 1.0e-6;
    return {{minX_, minY_, z_ - thickness}, {maxX_, maxY_, z_ + thickness}};
}

} // raytracer
