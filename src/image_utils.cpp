/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "image_utils.h"

#include <stdexcept>

#include "stb.h"

ImageData::ImageData(unsigned width, unsigned height, std::vector<Color>&& pixels)
        : width(width), height(height), pixels(std::move(pixels)) {

    if (width == 0) {
        throw std::invalid_argument{"width must be > 0"};
    }
    if (height == 0) {
        throw std::invalid_argument{"height must be > 0"};
    }
    if (this->pixels.size() != width * height) {
        throw std::invalid_argument{"size of pixels must be width * height"};
    }
}

ImageData loadImage(const std::string& filePath) {
    static const int bytesPerPixel = 3;
    static const double channelScale = 1.0 / 255.0;

    int width = 0;
    int height = 0;
    int componentsPerPixel = bytesPerPixel;
    auto data = stbi_load(filePath.c_str(), &width, &height, &componentsPerPixel, componentsPerPixel);
    if (!data) {
        throw std::runtime_error{"failed to load image"};
    }
    if (width <= 0) {
        throw std::runtime_error{"width of the loaded image is <= 0"};
    }
    if (height <= 0) {
        throw std::runtime_error{"width of the loaded image is <= 0"};
    }

    std::vector<Color> pixels;
    pixels.reserve(width * height);

    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            auto pixel = data + j * bytesPerPixel * width + i * bytesPerPixel;
            pixels.emplace_back(pixel[0] * channelScale, pixel[1] * channelScale, pixel[2] * channelScale);
        }
    }

    return {static_cast<unsigned>(width), static_cast<unsigned>(height), std::move(pixels)};
}
