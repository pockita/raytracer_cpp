/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "Color.h"

namespace raytracer {

Color::Color(double r, double g, double b) : channels_{r, g, b} {}

const Color Color::black{0.0, 0.0, 0.0};
const Color Color::white{1.0, 1.0, 1.0};

} // raytracer
