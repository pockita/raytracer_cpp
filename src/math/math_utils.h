/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include <cmath>

namespace math {

inline double degToRad(double deg) { return deg * (M_PI / 180.0); }

inline double radToDeg(double rad) { return rad * (180.0 / M_PI); }

}
