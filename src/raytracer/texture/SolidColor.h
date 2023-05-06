/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include "ITexture.h"

namespace raytracer {

struct SolidColor final : ITexture {
    explicit SolidColor(const Color& color);
    Color getColor(double u, double v) const override { return color_; }

private:
    Color color_;
};

} // raytracer
