/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include <cstddef>
#include <vector>

#include "ITexture.h"

namespace raytracer {

struct ImageTexture : ITexture {
    ImageTexture(unsigned width, unsigned height, std::vector<Color>&& colors);
    Color getColor(double u, double v) const override;

private:
    unsigned width_;
    unsigned height_;
    std::vector<Color> colors_;
};

} // raytracer
