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

    std::vector<std::vector<double>> box3 = {
        {1.0/9, 1.0/9, 1.0/9},
        {1.0/9, 1.0/9, 1.0/9},
        {1.0/9, 1.0/9, 1.0/9}
    };

    manager.applyFilter<ConvolutionFilter>(/*kernel=*/box3, /*padding=*/1);
    manager.applyFilter<MedianFilter>(/*radius=*/1);
    manager.applyFilter<GaussianFilter>(/*sigma=*/1, /*kernel_size=*/29, /*padding=*/0);
    manager.applyFilter<SharpenFilter>(/*strength=*/10, /*padding=*/1);
    manager.applyFilter<DogFilter>(/*sigma1=*/3, /*sigma2=*/10, /*kernel_size=*/1, /*padding=*/1);
    manager.applyFilter<ThresholdFilter>(/*threshold=*/45, /*inversion=*/1);

    auto result = manager.saveByEnv();
    return 0;
}
