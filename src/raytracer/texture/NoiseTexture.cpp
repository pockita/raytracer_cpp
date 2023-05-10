/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "NoiseTexture.h"

namespace raytracer {

NoiseTexture::NoiseTexture(double scale) : scale_(scale) {}

Color NoiseTexture::getColor(double u, double v, const Point3& p) const {
    double a = 0.5 * (1.0 + std::sin(scale_ * p.z() + 10.0 * perlin_.turbulence(p)));
    return {a, a, a};
}

} // raytracer