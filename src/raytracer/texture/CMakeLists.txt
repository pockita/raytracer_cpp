target_sources(raytracer
        PUBLIC
        ImageTexture.h
        ITexture.h
        NoiseTexture.h
        SolidColor.h

        PRIVATE
        ImageTexture.cpp
        NoiseTexture.cpp
        Perlin.h
        Perlin.cpp
        SolidColor.cpp)

target_include_directories(raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
