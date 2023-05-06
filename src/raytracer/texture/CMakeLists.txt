target_sources(raytracer
        PUBLIC
        ImageTexture.h
        ITexture.h
        SolidColor.h

        PRIVATE
        ImageTexture.cpp
        SolidColor.cpp)

target_include_directories(raytracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
