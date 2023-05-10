/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include "Perlin.h"

#include <algorithm>
#include <array>
#include <random>

#include "raytracer_utils.h"

namespace raytracer {

double interpolate(const std::array<Vector3, 8>& vectors, const double u, const double v, const double w) {
    const auto uu = u * u * (3.0 - 2.0 * u);
    const auto vv = v * v * (3.0 - 2.0 * v);
    const auto ww = w * w * (3.0 - 2.0 * w);

    auto acc = 0.0;
    for (int idx = 0; idx < 8; ++idx) {
        const int i = idx / 4;
        const int j = idx % 4 / 2;
        const int k = idx % 2;
        Vector3 weight{u - i, v - j, w - k};
        acc += (i * uu + (1 - i) * (1.0 - u)) *
               (j * vv + (1 - j) * (1.0 - v)) *
               (k * ww + (1 - k) * (1.0 - w)) *
               dot(vectors[idx], weight);
    }
    return acc;
}

Perlin::Perlin() : randomUnitVectors_{}, permutation_x_(generatePermutation()), permutation_y_(generatePermutation()), permutation_z_(generatePermutation()) {
    for (auto& v : randomUnitVectors_) {
        v = randomUnitVector();
    }

}

double Perlin::noise(const Point3& p) const {
    const auto u = p.x() - std::floor(p.x());
    const auto v = p.y() - std::floor(p.y());
    const auto w = p.z() - std::floor(p.z());

    const auto i = static_cast<int>(std::floor(p.x())) & 255;
    const auto j = static_cast<int>(std::floor(p.y())) & 255;
    const auto k = static_cast<int>(std::floor(p.z())) & 255;

    std::array<Vector3, 8> vectors;
    for (int idx = 0; idx < 8; ++idx) {
        const int di = idx / 4;
        const int dj = idx % 4 / 2;
        const int dk = idx % 2;
        vectors[idx] = randomUnitVectors_[permutation_x_[(i + di) & 255] ^
                                          permutation_y_[(j + dj) & 255] ^
                                          permutation_z_[(k + dk) & 255]];
    }

    return interpolate(vectors, u, v, w);
}

double Perlin::turbulence(const Point3& p, int depth) const {
    auto acc = 0.0;
    auto q = p;
    auto weight = 1.0;
    for (int i = 0; i < depth; ++i) {
        acc += weight * noise(q);
        weight *= 0.5;
        q = {q[0] * 2.0, q[1] * 2.0, q[2] * 2.0};
    }
    return std::fabs(acc);
}

std::array<int, Perlin::n_> Perlin::generatePermutation() {
    static std::random_device r;
    static std::mt19937 e{r()};
    std::array<int, 256> a{};
    for (int i = 0; i < a.size(); ++i) {
        a[i] = i;
    }
    std::shuffle(std::begin(a), std::end(a), e);
    return a;
}

} // raytracer
