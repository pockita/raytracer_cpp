/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "raytracer.h"

#include <limits>
#include <stdexcept>

#include "raytracer_utils.h"

namespace raytracer {

Color raytrace(const Point3& origin,
               const Vector3& dir,
               const std::vector<std::shared_ptr<ICollider>>& colliderPtrs,
               const std::vector<std::shared_ptr<IMaterial>>& materialPtrs,
               int depth) {

    static const auto minT = 1.0e-8; // to prevent shadow acne
    static const auto maxT = std::numeric_limits<double>::infinity();

    if (depth <= 0) {
        return Color::black;
    }

    if (dir.isZero(getTol())) {
        throw std::invalid_argument{"dir must be not 0"};
    }
    const auto unitDir = normalized(dir);

    std::optional<HitData> optResultHit;
    for (const auto& pCollider : colliderPtrs) {
        if (!pCollider) {
            throw std::invalid_argument{"pCollider must be not null"};
        }

        const auto optHit = pCollider->hit(origin, unitDir, minT, maxT);
        if (optHit && (!optResultHit || optHit->t < optResultHit->t)) {
            optResultHit = optHit;
        }
    }

    if (!optResultHit) {
        return blend(Color{0.5, 0.7, 1.0}, Color::white, 0.5 * (unitDir.y() + 1.0));
    }
    const auto& hit = *optResultHit;

    if (hit.materialId < 0 || hit.materialId >= materialPtrs.size()) {
        throw std::invalid_argument{"no material with materialId"};
    }

    const auto& pMaterial = materialPtrs[hit.materialId];
    if (!pMaterial) {
        throw std::invalid_argument{"pMaterial must be not null"};
    }

    const auto optTrace = pMaterial->trace(unitDir, hit.n, hit.isOutside);
    return optTrace ? optTrace->attenuation * raytrace(hit.p, optTrace->outV, colliderPtrs, materialPtrs, depth - 1) : Color::black;
}

}