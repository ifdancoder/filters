cmake_minimum_required(VERSION 4.0)
project(filters)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(filters main.cpp
        src/core/Image.cpp
        include/core/Image.h
        include/core/IImageSource.h
        src/filters/BaseImage.cpp
        include/filters/BaseImage.h
        src/filters/FilterDecorator.cpp
        include/filters/FilterDecorator.h
        src/filters/ConvolutionFilter.cpp
        include/filters/ConvolutionFilter.h
        include/filters/ThresholdFilter.h
        src/filters/ThreshholdFilter.cpp
        src/filters/MedianFilter.cpp
        include/filters/MedianFilter.h
        helpers.hpp
)
