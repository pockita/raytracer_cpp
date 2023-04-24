add_library(math)

target_sources(math
        PUBLIC
        math_utils.h
        Point3.h
        Vector3.h

        PRIVATE
        Point3.cpp
        Vector3.cpp)

target_include_directories(math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
