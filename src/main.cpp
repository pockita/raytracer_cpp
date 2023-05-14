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
#include "ColliderTree.h"
#include "DiffuseLight.h"
#include "Lambertian.h"
#include "raytracer.h"
#include "raytracer_utils.h"
#include "SolidColor.h"
#include "Transformed.h"
#include "XyRectangle.h"

#include "ppm.h"

int main() {
    using std::chrono::duration_cast;
    using std::chrono::steady_clock;
    using namespace math;
    using namespace raytracer;

    const double aspectRatio = 1.0;
    const int imageWidth = 500;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int nSamplesPerPixel = 250;
    const int maxDepth = 10;

    auto addBox = [](
            double xSize, double ySize, double zSize,
            double rx, double ry, double rz,
            const Vector3& offset,
            int materialId,
            std::vector<ColliderPtr>& colliderPtrs) {

        auto pXyFace = std::make_shared<XyRectangle>(0.0, xSize, 0.0, ySize, 0.0, materialId);
        auto pYzFace = std::make_shared<XyRectangle>(0.0, ySize, 0.0, zSize, 0.0, materialId);
        auto pZxFace = std::make_shared<XyRectangle>(0.0, zSize, 0.0, xSize, 0.0, materialId);

        std::vector<ColliderPtr> aFaceColliders;
        aFaceColliders.push_back(std::make_shared<Transformed>(pXyFace, 0.0, 0.0, 0.0, Vector3{0.0, 0.0, zSize}));
        aFaceColliders.push_back(std::make_shared<Transformed>(pXyFace, 0.0, 180.0, 0.0, Vector3{xSize, 0.0, 0.0}));
        aFaceColliders.push_back(std::make_shared<Transformed>(pYzFace, 90.0, 0.0, 90.0, Vector3{xSize, 0.0, 0.0}));
        aFaceColliders.push_back(std::make_shared<Transformed>(pYzFace, -90.0, 0.0, 90.0, Vector3{0.0, 0.0, zSize}));
        aFaceColliders.push_back(std::make_shared<Transformed>(pZxFace, -90.0, -90.0, 0.0, Vector3{0.0, ySize, 0.0}));
        aFaceColliders.push_back(std::make_shared<Transformed>(pZxFace, 90.0, -90.0, 0.0, Vector3{xSize, 0.0, 0.0}));

        for (auto& pCollider : aFaceColliders) {
            colliderPtrs.push_back(std::make_shared<Transformed>(std::move(pCollider), rx, ry, rz, offset));
        }
    };

    auto pGrayTexture = std::make_shared<SolidColor>(Color{0.73, 0.73, 0.73});
    auto pRedTexture = std::make_shared<SolidColor>(Color{0.65, 0.05, 0.05});
    auto pGreenTexture = std::make_shared<SolidColor>(Color{0.12, 0.45, 0.15});
    auto pLightTexture = std::make_shared<SolidColor>(Color{15.0, 15.0, 15.0});

    std::vector<MaterialPtr> materialPtrs{
        std::make_shared<Lambertian>(pGrayTexture),
        std::make_shared<Lambertian>(pRedTexture),
        std::make_shared<Lambertian>(pGreenTexture),
        std::make_shared<DiffuseLight>(pLightTexture),
    };

    auto pGrayXYRect = std::make_shared<XyRectangle>(0.0, 555.0, 0.0, 555.0, 0.0, 0);
    auto pRedXYRect = std::make_shared<XyRectangle>(0.0, 555.0, 0.0, 555.0, 0.0, 1);
    auto pGreenXYRect = std::make_shared<XyRectangle>(0.0, 555.0, 0.0, 555.0, 0.0, 2);
    auto pLightXYRect = std::make_shared<XyRectangle>(0.0, 130.0, 0.0, 130.0, 0.0, 3);

    std::vector<ColliderPtr> colliderPtrs{
        std::make_shared<Transformed>(pGrayXYRect, 90.0, 0.0, 0.0, Vector3{0.0, 0.0, 0.0}),
        std::make_shared<Transformed>(pGrayXYRect, 90.0, 0.0, 0.0, Vector3{0.0, 555.0, 0.0}),
        std::make_shared<Transformed>(pLightXYRect, 90.0, 0.0, 0.0, Vector3{213.0, 555.0 - 1.0e-6, 227.0}),

        std::make_shared<Transformed>(pGrayXYRect, 0.0, 0.0, 0.0, Vector3{0.0, 0.0, 555.0}),

        std::make_shared<Transformed>(pGreenXYRect, 0.0, -90.0, 0.0, Vector3{555.0, 0.0, 0.0}),
        std::make_shared<Transformed>(pRedXYRect, 0.0, -90.0, 0.0, Vector3{0.0, 0.0, 0.0}),
    };

    addBox(165.0, 165.0, 165.0, 0.0, -18.0, 0.0, {130.0, 0.0, 65.0}, 0, colliderPtrs);
    addBox(165.0, 330.0, 165.0, 0.0, 15.0, 0.0, {256.0, 0.0, 295.0}, 0, colliderPtrs);

    ColliderTree sceneCollider{colliderPtrs, 0, colliderPtrs.size()};
    auto backgroundColor = Color{0.0, 0.0, 0.0};

    const Point3 lookFrom{278, 278, -800};
    const Point3 lookAt{278,278,0};
    const Vector3 viewUp{0.0, 1.0, 0.0};
    const double verticalFieldOfView = 40.0;
    const double focusDist = (lookFrom - lookAt).len() + 0.5;
    const double aperture = 0.0;
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
                auto c = raytrace(origin, dir, backgroundColor, sceneCollider, materialPtrs, maxDepth);
                r += c.r();
                g += c.g();
                b += c.b();
            }
            colors.emplace_back(std::pow(r / nSamplesPerPixel, 1.0 / gamma),
                                std::pow(g / nSamplesPerPixel, 1.0 / gamma),
                                std::pow(b / nSamplesPerPixel, 1.0 / gamma));
        }
    }

    std::cout << duration_cast<std::chrono::seconds>(steady_clock::now() - start).count() << std::endl;

    ppm::write("c:\\dev\\image.ppm", imageWidth, imageHeight, colors);

    return 0;
}
