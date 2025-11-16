cmake_minimum_required(VERSION 4.0)
project(filters)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        dotenv
        GIT_REPOSITORY https://github.com/SermetPekin/dotenv.git
        GIT_TAG main
)
FetchContent_MakeAvailable(dotenv)

find_path(DOTENV_INCLUDE_DIR
        NAMES dotenv.h env.h
        PATHS ${dotenv_SOURCE_DIR} ${dotenv_BINARY_DIR}
        PATH_SUFFIXES include src
)

if(DOTENV_INCLUDE_DIR)
    include_directories(${DOTENV_INCLUDE_DIR})
    message(STATUS "Found dotenv headers in: ${DOTENV_INCLUDE_DIR}")
else()
    message(WARNING "Could not find dotenv headers")
endif()

find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(HDF5 REQUIRED hdf5)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(include)

link_directories(/usr/lib)

add_executable(
        filters main.cpp

        include/core/IImageSource.h

        include/core/Image.h
        src/core/Image.cpp

        include/core/Pixel.h
        src/core/Pixel.cpp

        include/filters/BaseImage.h
        src/filters/BaseImage.cpp

        include/filters/ConvolutionFilter.h
        src/filters/ConvolutionFilter.cpp

        include/filters/FilterDecorator.h
        src/filters/FilterDecorator.cpp

        include/filters/MedianFilter.h
        src/filters/MedianFilter.cpp

        include/filters/ThresholdFilter.h
        src/filters/ThresholdFilter.cpp

        include/core/ImageManager.h
        src/core/ImageManager.cpp

        include/filters/GaussianFilter.h
        src/filters/GaussianFilter.cpp

        include/filters/SharpenFilter.h
        src/filters/SharpenFilter.cpp

        include/filters/DogFilter.h
        src/filters/DogFilter.cpp

        include/filters/CannyFilter.h
        src/filters/CannyFilter.cpp

        include/filters/MosaicFilter.h
        src/filters/MosaicFilter.cpp

        # Морфологические фильтры
        include/core/StructuringElement.h
        src/core/StructuringElement.cpp

        include/filters/MorphologicalFilter.h
        src/filters/MorphologicalFilter.cpp

        include/filters/BinaryErosionFilter.h
        src/filters/BinaryErosionFilter.cpp

        include/filters/BinaryDilationFilter.h
        src/filters/BinaryDilationFilter.cpp

        include/filters/BinaryOpeningFilter.h
        src/filters/BinaryOpeningFilter.cpp

        include/filters/BinaryClosingFilter.h
        src/filters/BinaryClosingFilter.cpp

        include/filters/GrayscaleErosionFilter.h
        src/filters/GrayscaleErosionFilter.cpp

        include/filters/GrayscaleDilationFilter.h
        src/filters/GrayscaleDilationFilter.cpp

        include/filters/GrayscaleOpeningFilter.h
        src/filters/GrayscaleOpeningFilter.cpp

        include/filters/GrayscaleClosingFilter.h
        src/filters/GrayscaleClosingFilter.cpp

        include/filters/EdgeDetectionFilter.h
        src/filters/EdgeDetectionFilter.cpp

        include/filters/MorphologicalGradientFilter.h
        src/filters/MorphologicalGradientFilter.cpp
)

target_link_libraries(filters ${OpenCV_LIBS} ${HDF5_LIBRARIES})