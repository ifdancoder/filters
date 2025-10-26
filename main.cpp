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
#include "filters/StructuringElement.h"
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
    ImageManager manager = ImageManager::getInstance();
    manager.loadByEnv();

    std::vector<std::vector<double>> box3 = {
        {1.0/9, 1.0/9, 1.0/9},
        {1.0/9, 1.0/9, 1.0/9},
        {1.0/9, 1.0/9, 1.0/9}
    };

    // Обычные фильтры
    // manager.applyFilter<ConvolutionFilter>(/*kernel=*/box3, /*padding=*/1);
    // manager.applyFilter<MedianFilter>(/*radius=*/1);
    // manager.applyFilter<GaussianFilter>(/*sigma=*/1, /*kernel_size=*/29, /*padding=*/0);
    // manager.applyFilter<SharpenFilter>(/*strength=*/10, /*padding=*/1);
    // manager.applyFilter<DogFilter>(/*sigma1=*/3, /*sigma2=*/10, /*kernel_size=*/1, /*padding=*/1);
    // manager.applyFilter<ThresholdFilter>(/*threshold=*/45, /*inversion=*/1);

    // Морфологические фильтры
    auto square = StructuringElement::createSquare(5);
    auto cross = StructuringElement::createCross(5);
    auto disk = StructuringElement::createDisk(5);

    auto current_structuring_element = disk;

    // Полутоновые морфологические операции
    // manager.applyFilter<GrayscaleErosionFilter>(/*structuring_element=*/current_structuring_element);
    // manager.applyFilter<GrayscaleDilationFilter>(/*structuring_element=*/current_structuring_element);
    // manager.applyFilter<GrayscaleClosingFilter>(/*structuring_element=*/current_structuring_element);
    // manager.applyFilter<GrayscaleOpeningFilter>(/*structuring_element=*/current_structuring_element);
    // manager.applyFilter<EdgeDetectionFilter>(/*structuring_element=*/current_structuring_element);
    // manager.applyFilter<MorphologicalGradientFilter>();

    // manager.applyFilter<BinaryErosionFilter>(/*structuring_element=*/current_structuring_element);
    // manager.applyFilter<BinaryDilationFilter>(/*structuring_element=*/current_structuring_element);
    manager.applyFilter<BinaryOpeningFilter>(/*structuring_element=*/current_structuring_element);
    // manager.applyFilter<BinaryClosingFilter>(/*structuring_element=*/current_structuring_element);

    auto result = manager.saveByEnv();
    return 0;
}
