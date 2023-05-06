add_executable(raytracer_cpp)

target_sources(raytracer_cpp
        PRIVATE
        image_utils.h
        image_utils.cpp
        main.cpp
        ppm.h
        ppm.cpp)

add_subdirectory(math)
add_subdirectory(raytracer)

target_link_libraries(raytracer_cpp PRIVATE raytracer)
