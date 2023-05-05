/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "raytracer_utils.h"

#include <cmath>
#include <random>
#include <stdexcept>

namespace raytracer {

double randomDoubleInUnitInterval() {
    static std::random_device r;
    static std::mt19937 e{r()};
    static std::uniform_real_distribution<double> dist{0.0, 1.0};
    return dist(e);
}

double randomDouble(double min, double max) {
    return min + (max - min) * randomDoubleInUnitInterval();
}

int randomInt(int min, int max) {
    return static_cast<int>(randomDouble(min, max + 1.0 - 1.0e-8));
}

Vector3 randomVector(double min, double max) {
    return {randomDouble(min, max), randomDouble(min, max), randomDouble(min, max)};
}

Vector3 randomUnitVector() {
    auto v = randomVector(-1.0, 1.0);
    if (v.isZero(getTol())) {
        v = Vector3::one;
    }
    v.normalize();
    return v;
}

Vector3 randomVectorInUnitSphere() {
    while (true) {
        auto v = randomVector(-1.0, 1.0);
        if (v.sqrLen() <= 1.0) {
            return v;
        }
    }
}

Vector3 randomVectorInUnitXYDisk() {
    while (true) {
        Vector3 v{randomDouble(-1.0, 1.0), randomDouble(-1.0, 1.0), 0.0};
        if (v.sqrLen() <= 1.0) {
            return v;
        }
    }
}

Vector3 reflected(const Vector3& inV, const Vector3& unitN) {
    if (!unitN.isUnit(getTol())) {
        throw std::invalid_argument{"unitN must be unit"};
    }
    return inV - 2.0 * dot(inV, unitN) * unitN;
}

Vector3 refracted(const Vector3& unitInV, const Vector3& unitN, double refractiveRatio) {
    if (!unitInV.isUnit(getTol())) {
        throw std::invalid_argument{"unitInV must be unit"};
    }
    if (!unitN.isUnit(getTol())) {
        throw std::invalid_argument{"unitN must be unit"};
    }
    const auto cosTheta = std::fmin(-dot(unitInV, unitN), 1.0);
    const auto perpV = refractiveRatio * (unitInV + cosTheta * unitN);
    return perpV - std::sqrt(std::fabs(1.0 - perpV.sqrLen())) * unitN;
}

} // raytracer
