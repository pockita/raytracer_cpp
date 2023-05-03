target_sources(raytracer
        PUBLIC
        ICollider.h
        Sphere.h

        PRIVATE
        ICollider.cpp
        Sphere.cpp)

target_include_directories(raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
