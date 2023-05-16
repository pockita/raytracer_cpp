target_sources(raytracer
        PUBLIC
        BoundingBox.h
        ColliderList.h
        ColliderTree.h
        ConstMedium.h
        ICollider.h
        Sphere.h
        Transformed.h
        XyRectangle.h

        PRIVATE
        BoundingBox.cpp
        ColliderList.cpp
        ColliderTree.cpp
        ConstMedium.cpp
        ICollider.cpp
        Sphere.cpp
        Transformed.cpp
        XyRectangle.cpp)

target_include_directories(raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
