/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include <array>
#include <cstddef>

namespace raytracer {

struct Color final {
    Color(double r, double g, double b);

    static const Color black;
    static const Color white;

    double operator[](std::size_t i) const { return channels_[i]; }
    double r() const { return channels_[0]; }
    double g() const { return channels_[1]; }
    double b() const { return channels_[2]; }

private:
    std::array<double, 3> channels_; // rgb
};

inline Color operator*(const Color& c1, const Color& c2) {
    return {c1[0] * c2[0], c1[1] * c2[1], c1[2] * c2[2]};
}

inline Color blend(const Color& c1, const Color& c2, double t1) {
    auto t2 = 1.0 - t1;
    return {c1[0] * t1 + c2[0] * t2, c1[1] * t1 + c2[1] * t2, c1[2] * t1 + c2[2] * t2};
}

} // raytracer
