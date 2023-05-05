/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "ColliderTree.h"

#include <memory>
#include <stdexcept>

#include "raytracer_utils.h"

namespace raytracer {

bool lessByAxis(const ColliderPtr& lp, const ColliderPtr& rp, int axis) {
    if (!lp || !rp) {
        throw std::invalid_argument{"lp and rp must be not nullptr"};
    }
    if (axis < 0 || axis > 2) {
        throw std::invalid_argument{"axis must be in [0, 2]"};
    }
    return lp->boundingBox().min()[axis] < rp->boundingBox().min()[axis];
}

ColliderTree::ColliderTree(std::vector<ColliderPtr>& colliderPtrs, std::size_t start, std::size_t end)
        : box_(Point3::origin, Point3::origin) {

    using std::swap;

    if (colliderPtrs.empty()) {
        throw std::invalid_argument{"colliderPtrs must be not empty"};
    }
    if (end <= start) {
        throw std::invalid_argument{"end must be > start"};
    }
    if (end > colliderPtrs.size()) {
        throw std::invalid_argument{"end must be <= the size of colliderPtrs"};
    }

    const auto less = [axis = randomInt(0, 2)](const ColliderPtr& lp, const ColliderPtr& rp) {
        return lessByAxis(lp, rp, axis);
    };

    const auto n = end - start;

    if (n == 1) {
        pLeft_ = colliderPtrs[start];
        box_ = pLeft_->boundingBox();
        return;
    }

    if (n == 2) {
        pLeft_ = colliderPtrs[start];
        pRight_ = colliderPtrs[start + 1];
        if (less(pRight_, pLeft_)) {
            swap(pLeft_, pRight_);
        }
    } else {
        std::sort(colliderPtrs.begin() + static_cast<int>(start), colliderPtrs.begin() + static_cast<int>(end), less);
        const auto middle = start + n/2;
        pLeft_ = std::make_shared<ColliderTree>(colliderPtrs, start, middle);
        pRight_ = std::make_shared<ColliderTree>(colliderPtrs, middle, end);
    }

    box_ = enclosing(pLeft_->boundingBox(), pRight_->boundingBox());
}

std::optional<HitData> ColliderTree::hit(const Point3& origin, const Vector3& dir, double minT, double maxT) const {
    if (!box_.hit(origin, dir, minT, maxT)) {
        return std::nullopt;
    }

    auto optLeftHit = pLeft_->hit(origin, dir, minT, maxT);
    if (!pRight_) {
        return optLeftHit;
    }
    if (optLeftHit) {
        maxT = optLeftHit->t;
    }
    auto optRightHit = pRight_->hit(origin, dir, minT, maxT);
    return optRightHit ? optRightHit : optLeftHit;
}

} // raytracer
