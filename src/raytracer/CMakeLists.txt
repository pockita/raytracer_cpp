add_library(raytracer)

target_sources(raytracer
        PUBLIC
        Camera.h
        Color.h
        raytracer.h
        raytracer_utils.h

        PRIVATE
        Camera.cpp
        Color.cpp
        raytracer.cpp
        raytracer_utils.cpp)

target_include_directories(raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(collider)
add_subdirectory(material)
add_subdirectory(texture)

target_link_libraries(raytracer PUBLIC math)
