add_library(math)

target_sources(math
        PUBLIC
        math_utils.h
        Matrix3x3.h
        Point3.h
        Vector3.h

        PRIVATE
        Matrix3x3.cpp
        Point3.cpp
        Vector3.cpp)

target_include_directories(math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
