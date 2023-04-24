/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include <string>
#include <vector>

#include "Color.h"

namespace ppm {

using raytracer::Color;

void write(const std::string& filePath, unsigned width, unsigned height, const std::vector<Color>& colors);

}
