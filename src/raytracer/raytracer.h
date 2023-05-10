/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#pragma once

#include <memory>
#include <vector>

#include "Point3.h"
#include "Vector3.h"

#include "Color.h"
#include "ICollider.h"
#include "IMaterial.h"

namespace raytracer {

using math::Point3;
using math::Vector3;

Color raytrace(const Point3& origin,
               const Vector3& dir,
               const Color& backgroundColor,
               const ICollider& sceneCollider,
               const std::vector<std::shared_ptr<IMaterial>>& materialPtrs,
               int depth);

}
