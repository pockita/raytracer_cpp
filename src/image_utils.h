/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include <string>
#include <vector>

#include "Color.h"

using raytracer::Color;

struct ImageData {
    ImageData(unsigned width, unsigned height, std::vector<Color>&& pixels);

    unsigned width = 0;
    unsigned height = 0;
    std::vector<Color> pixels;
};

ImageData loadImage(const std::string& filePath);
