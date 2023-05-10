/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include "ITexture.h"
#include "Perlin.h"

namespace raytracer {

struct NoiseTexture : ITexture {
    explicit NoiseTexture(double scale = 1.0);
    Color getColor(double u, double v, const Point3& p) const override;

private:
    Perlin perlin_;
    double scale_;
};

} // raytracer
