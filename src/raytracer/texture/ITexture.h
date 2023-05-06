/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include <memory>

#include "Color.h"

namespace raytracer {

struct ITexture {
    virtual ~ITexture() = default;
    virtual Color getColor(double u, double v) const = 0;
};

using TexturePtr = std::shared_ptr<ITexture>;

} // raytracer
