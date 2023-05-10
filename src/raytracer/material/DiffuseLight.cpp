/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "DiffuseLight.h"

#include <stdexcept>

namespace raytracer {

DiffuseLight::DiffuseLight(raytracer::TexturePtr pTexture) : pTexture_(std::move(pTexture)) {
    if (!pTexture_) {
        throw std::invalid_argument{"pTexture must be not nullptr"};
    }
}

Color DiffuseLight::getColor(double u, double v, const Point3& p) const {
    throw std::logic_error{"DiffuseLight::getColor must be not called"};
}

} // raytracer
