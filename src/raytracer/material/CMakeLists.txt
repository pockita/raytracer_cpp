target_sources(raytracer
        PUBLIC
        Dielectric.h
        DiffuseLight.h
        IMaterial.h
        Isotropic.h
        Lambertian.h
        Metal.h

        PRIVATE
        Dielectric.cpp
        DiffuseLight.cpp
        IMaterial.cpp
        Isotropic.cpp
        Lambertian.cpp
        Metal.cpp)

target_include_directories(raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
