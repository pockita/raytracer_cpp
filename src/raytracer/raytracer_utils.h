/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include "Vector3.h"

namespace raytracer {

using math::Vector3;

constexpr double getTol() { return 1.0e-8; }

constexpr double getSqrTol() { return getTol() * getTol(); }

double randomDoubleInUnitInterval();

double randomDouble(double min, double max);

int randomInt(int min, int max);

Vector3 randomVector(double min, double max);

Vector3 randomUnitVector();

Vector3 randomVectorInUnitSphere();

Vector3 randomVectorInUnitXYDisk();

Vector3 reflected(const Vector3& inV, const Vector3& unitN);

Vector3 refracted(const Vector3& unitInV, const Vector3& unitN, double refractiveRatio);

} // raytracer
