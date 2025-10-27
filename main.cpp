#include <iostream>
#include <memory>
#include <vector>

#include <core/IImageSource.h>
#include <core/Image.h>
#include <core/Pixel.h>
#include <filters/BaseImage.h>

#include "filters/ConvolutionFilter.h"
#include "filters/MedianFilter.h"
#include "filters/ThresholdFilter.h"

#include "core/ImageManager.h"
#include "filters/DogFilter.h"
#include "filters/GaussianFilter.h"
#include "filters/SharpenFilter.h"

// Морфологические фильтры
#include "include/core/StructuringElement.h"
#include "filters/BinaryErosionFilter.h"
#include "filters/BinaryDilationFilter.h"
#include "filters/BinaryOpeningFilter.h"
#include "filters/BinaryClosingFilter.h"
#include "filters/GrayscaleErosionFilter.h"
#include "filters/GrayscaleDilationFilter.h"
#include "filters/GrayscaleOpeningFilter.h"
#include "filters/GrayscaleClosingFilter.h"
#include "filters/EdgeDetectionFilter.h"
#include "filters/MorphologicalGradientFilter.h"

int main() {
    // ImageManager manager = ImageManager::getInstance();
    // manager.loadByEnv();
    //
    // std::vector<std::vector<double>> box3 = {
    //     {1.0/9, 1.0/9, 1.0/9},
    //     {1.0/9, 1.0/9, 1.0/9},
    //     {1.0/9, 1.0/9, 1.0/9}
    // };
    //
    // manager.applyFilter<ConvolutionFilter>(/*kernel=*/box3, /*padding=*/1);
    //
    // // manager.applyFilter<MedianFilter>(/*radius=*/1);
    // // manager.applyFilter<GaussianFilter>(/*sigma=*/1, /*kernel_size=*/29, /*padding=*/0);
    // // manager.applyFilter<SharpenFilter>(/*strength=*/10, /*padding=*/1);
    // // manager.applyFilter<DogFilter>(/*sigma1=*/3, /*sigma2=*/10, /*kernel_size=*/1, /*padding=*/1);
    // // manager.applyFilter<ThresholdFilter>(/*threshold=*/45, /*inversion=*/1);
    //
    // auto result = manager.saveByEnv();
    //
    // // Морфологические фильтры
    // auto square = StructuringElement::createSquare(3);
    // auto cross = StructuringElement::createCross(3);
    // auto disk = StructuringElement::createDisk(3);
    // auto bigDisk = StructuringElement::createDisk(10);
    //
    // auto current_structuring_element = disk;
    // auto current_big_structuring_element = bigDisk;
    //
    ImageManager grayscale_manager = ImageManager::getInstance();
    grayscale_manager.load("input/input3.jpg");
    //
    // grayscale_manager.applyFilter<GrayscaleErosionFilter>(/*structuring_element=*/current_structuring_element);
    // grayscale_manager.applyFilter<GrayscaleDilationFilter>(/*structuring_element=*/current_structuring_element);
    // grayscale_manager.applyFilter<GrayscaleClosingFilter>(/*structuring_element=*/current_structuring_element);
    // grayscale_manager.applyFilter<GrayscaleOpeningFilter>(/*structuring_element=*/current_structuring_element);
    // grayscale_manager.applyFilter<EdgeDetectionFilter>(/*structuring_element=*/current_structuring_element);
    grayscale_manager.applyFilter<MorphologicalGradientFilter>(StructuringElement::RHOMBUS);
    //
    //
    auto result2 = grayscale_manager.save("output/grayscale_morphological_gradient_test.jpg");

    // ImageManager binary_manager = ImageManager::getInstance();
    // binary_manager.load("input/input2.jpg");
    // binary_manager.applyFilter<BinaryErosionFilter>(/*structuring_element=*/current_structuring_element);
    // binary_manager.applyFilter<BinaryDilationFilter>(/*structuring_element=*/current_structuring_element);
    // binary_manager.applyFilter<BinaryOpeningFilter>(/*structuring_element=*/current_big_structuring_element);
    // binary_manager.applyFilter<BinaryClosingFilter>(/*structuring_element=*/current_big_structuring_element);
    // auto result3 = binary_manager.save("output/binary_opening.jpg");

    // tmpm.applyFilter<BinaryDilationFilter>(/*structuring_element=*/rhombus_element);
    // tmpm.applyFilter<BinaryDilationFilter>(/*structuring_element=*/rhombus_element);
    // tmpm.applyFilter<BinaryDilationFilter>(/*structuring_element=*/rhombus_element);
    // tmpm.applyFilter<BinaryDilationFilter>(/*structuring_element=*/rhombus_element);
    // tmpm.applyFilter<BinaryDilationFilter>(/*structuring_element=*/rhombus_element);

    return 0;
}
