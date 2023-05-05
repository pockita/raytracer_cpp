target_sources(raytracer
        PUBLIC
        Dielectric.h
        IMaterial.h
        Lambertian.h
        Metal.h

        PRIVATE
        Dielectric.cpp
        IMaterial.cpp
        Lambertian.cpp
        Metal.cpp)

target_include_directories(raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
