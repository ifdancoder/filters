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

int main() {
    ImageManager manager = ImageManager::getInstance();
    manager.loadByEnv();

    // std::vector<std::vector<double>> box3 = {
    //     {1.0/9, 1.0/9, 1.0/9},
    //     {1.0/9, 1.0/9, 1.0/9},
    //     {1.0/9, 1.0/9, 1.0/9}
    // };

    // manager.applyFilter<ConvolutionFilter>(box3, /*padMode=*/1);
    // manager.applyFilter<MedianFilter>(/*radius=*/1);
    // manager.applyFilter<GaussianFilter>(1, 29, 0);
    manager.applyFilter<SharpenFilter>(10, 1);
    // manager.applyFilter<DogFilter>(3, 10);
    // manager.applyFilter<ThresholdFilter>(/*th=*/1, /*inv=*/1);

    auto result = manager.saveByEnv();
    return 0;
}
