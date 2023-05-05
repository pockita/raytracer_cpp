target_sources(raytracer
        PUBLIC
        BoundingBox.h
        ColliderList.h
        ColliderTree.h
        ICollider.h
        Sphere.h

        PRIVATE
        BoundingBox.cpp
        ColliderList.cpp
        ColliderTree.cpp
        ICollider.cpp
        Sphere.cpp)

target_include_directories(raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
