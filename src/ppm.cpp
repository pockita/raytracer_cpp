/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "ppm.h"

#include <cmath>
#include <fstream>
#include <stdexcept>

namespace ppm {

constexpr int getMaxIntValue() { return 255; }

int convToIntValue(double v) {
    v = std::max(v, 0.0);
    v = std::min(v, 1.0 - 1.0e-6);
    return static_cast<int>(getMaxIntValue() * v);
}

void write(const std::string& filePath, unsigned width, unsigned height, const std::vector<Color>& colors) {
    if (!filePath.ends_with(".ppm")) {
        throw std::invalid_argument{"extension of filePath must be ppm"};
    }
    if (width == 0) {
        throw std::invalid_argument{"width must be > 0"};
    }
    if (height == 0) {
        throw std::invalid_argument{"height must be > 0"};
    }
    if (colors.size() != width * height) {
        throw std::invalid_argument{"size of colors must be width * height"};
    }

    std::ofstream f;
    f.open(filePath);

    f << "P3" << std::endl; // plain ppm magic number
    f << width << ' ' << height << std::endl;
    f << getMaxIntValue() << std::endl;
    for (const auto& c : colors) {
        f << convToIntValue(c.r()) << ' '
          << convToIntValue(c.g()) << ' '
          << convToIntValue(c.b()) << std::endl;
    }

    f.flush();
    f.close();
}

}
