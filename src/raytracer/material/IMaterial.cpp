/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "IMaterial.h"

namespace raytracer {

TraceData::TraceData(const Color& attenuation, const Vector3& outV) : attenuation(attenuation), outV(outV) {}

} // raytracer
