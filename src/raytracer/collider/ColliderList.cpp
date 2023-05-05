/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "ColliderList.h"

#include <stdexcept>

namespace raytracer {

BoundingBox buildEnclosingBox(const std::vector<ColliderPtr>& colliderPtrs) {
    if (colliderPtrs.empty()) {
        throw std::invalid_argument{"colliderPtrs must be not empty"};
    }
    for (const auto& pCollider : colliderPtrs) {
        if (!pCollider) {
            throw std::invalid_argument{"colliderPtrs must contain no nullptr"};
        }
    }
    auto box = colliderPtrs[0]->boundingBox();
    for (std::size_t i = 1; i < colliderPtrs.size(); ++i) {
        box.enclose(colliderPtrs[i]->boundingBox());
    }
    return box;
}

ColliderList::ColliderList(const std::vector<ColliderPtr>& colliderPtrs)
        : colliderPtrs_(colliderPtrs), box_(buildEnclosingBox(colliderPtrs)) {

    // colliderPtrs is validated in buildEnclosingBox
}

std::optional<HitData> ColliderList::hit(const Point3& origin, const Vector3& dir, double minT, double maxT) const {
    std::optional<HitData> res;
    for (const auto& pCollider : colliderPtrs_) {
        if (auto optHit = pCollider->hit(origin, dir, minT, maxT)) {
            res = optHit;
            maxT = res->t;
        }
    }
    return res;
}

} // raytracer
