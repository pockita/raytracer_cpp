/*
 * Created by Alex (pockitaxd@gmail.com)
 */

#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

#include "Point3.h"
#include "Vector3.h"

#include "Camera.h"
#include "Dielectric.h"
#include "Lambertian.h"
#include "Metal.h"
#include "raytracer.h"
#include "raytracer_utils.h"
#include "Sphere.h"

#include "ppm.h"

int main() {
    using std::chrono::duration_cast;
    using std::chrono::steady_clock;
    using namespace math;
    using namespace raytracer;

    const double aspectRatio = 3.0 / 2.0;
    const int imageWidth = 800;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int nSamplesPerPixel = 100;
    const int maxDepth = 50;

    auto materialGround = std::make_shared<Lambertian>(Color{0.8, 0.8, 0.0});
    auto materialCenter = std::make_shared<Lambertian>(Color{0.2, 0.2, 0.5});
    auto materialLeft = std::make_shared<Dielectric>(1.5);
    auto materialRight = std::make_shared<Metal>(Color{0.8, 0.6, 0.2}, 0);

    auto colliderGround = std::make_shared<Sphere>(Point3{0.0, -100.5, -1.0}, 100.0);
    auto colliderCenter = std::make_shared<Sphere>(Point3{0.0, 0.0, -1.0}, 0.5);
    auto colliderLeft = std::make_shared<Sphere>(Point3{-1.0, 0.0, -1.0}, 0.5);
    auto colliderRight = std::make_shared<Sphere>(Point3{1.0, 0.0, -1.0}, 0.5);

    std::vector<ObjectData> objects {
        {colliderGround, materialGround},
        {colliderCenter, materialCenter},
        {colliderLeft, materialLeft},
        {colliderRight, materialRight}
    };

    const Point3 lookFrom{3.0,3.0,2.0};
    const Point3 lookAt{0.0,0.0,-1.0};
    const Vector3 viewUp{0.0, 1.0, 0.0};
    const double verticalFieldOfView = 20.0;
    const double focusDist = (lookFrom - lookAt).len() + 0.5;
    const double aperture = 0.5;
    Camera camera{lookFrom, lookAt, viewUp, verticalFieldOfView, aspectRatio, focusDist, aperture};

    const double gamma = 1.5;

    const auto start = steady_clock::now();

    std::vector<Color> colors;
    colors.reserve(imageWidth * imageHeight);
    for(int j = imageHeight - 1; j >= 0; --j) {
        for (int i = 0; i < imageWidth; ++i) {
            double r = 0.0;
            double g = 0.0;
            double b = 0.0;
            for (int k = 0; k < nSamplesPerPixel; ++k) {
                auto u = (i + randomDoubleInUnitInterval()) / (imageWidth - 1);
                auto v = (j + randomDoubleInUnitInterval()) / (imageHeight - 1);
                const auto& [origin, dir] = camera.calcRay(u, v);
                auto c = raytrace(origin, dir, objects, maxDepth);
                r += c.r();
                g += c.g();
                b += c.b();
            }
            colors.emplace_back(std::pow(r / nSamplesPerPixel, 1.0 / gamma),
                                std::pow(g / nSamplesPerPixel, 1.0 / gamma),
                                std::pow(b / nSamplesPerPixel, 1.0 / gamma));
        }
    }

    ppm::write("c:\\dev\\image.ppm", imageWidth, imageHeight, colors);

    std::cout << duration_cast<std::chrono::seconds>(steady_clock::now() - start).count() << std::endl;
    return 0;
}
