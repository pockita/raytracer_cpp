/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "ImageTexture.h"

#include <cmath>
#include <stdexcept>

namespace raytracer {

ImageTexture::ImageTexture(unsigned width, unsigned height, std::vector<Color>&& colors)
        : width_(width), height_(height), colors_(std::move(colors)) {

    if (width == 0) {
        throw std::invalid_argument{"width must be > 0"};
    }
    if (height == 0) {
        throw std::invalid_argument{"height must be > 0"};
    }
    if (colors_.size() != width * height) {
        throw std::invalid_argument{"size of colors must be width * height"};
    }
}

Color ImageTexture::getColor(double u, double v) const {
    u = std::clamp(u, 0.0, 1.0);
    v = std::clamp(v, 0.0, 1.0);
    const auto i = std::min(static_cast<unsigned>(u * width_), width_ - 1);
    const auto j = std::min(static_cast<unsigned>(v * height_), height_ - 1);
    return colors_[width_ * j + i];
}

} // raytracer
