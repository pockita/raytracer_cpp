/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include <memory>

#include "Point3.h"

#include "Color.h"

namespace raytracer {

using math::Point3;

struct ITexture {
    virtual ~ITexture() = default;
    virtual Color getColor(double u, double v, const Point3& p) const = 0;
};

using TexturePtr = std::shared_ptr<ITexture>;

} // raytracer
