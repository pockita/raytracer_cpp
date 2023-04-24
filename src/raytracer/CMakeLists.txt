add_library(raytracer raytracer.cpp raytracer.h)

target_sources(raytracer
        PUBLIC
        Camera.h
        Color.h
        Dielectric.h
        ICollider.h
        IMaterial.h
        Lambertian.h
        Metal.h
        raytracer_utils.h
        Sphere.h

        PRIVATE
        Camera.cpp
        Color.cpp
        Dielectric.cpp
        ICollider.cpp
        IMaterial.cpp
        Lambertian.cpp
        Metal.cpp
        raytracer_utils.cpp
        Sphere.cpp)

target_include_directories(raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(raytracer PUBLIC math)
