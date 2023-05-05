add_library(raytracer)

target_sources(raytracer
        PUBLIC
        Camera.h
        Color.h
        Dielectric.h
        IMaterial.h
        Lambertian.h
        Metal.h
        raytracer.h
        raytracer_utils.h

        PRIVATE
        Camera.cpp
        Color.cpp
        Dielectric.cpp
        IMaterial.cpp
        Lambertian.cpp
        Metal.cpp
        raytracer.cpp
        raytracer_utils.cpp)

target_include_directories(raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(collider)

target_link_libraries(raytracer PUBLIC math)
