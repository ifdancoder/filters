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

int main() {
    ImageManager manager = ImageManager::getInstance();
    manager.loadByEnv();

    std::vector<std::vector<double>> box3 = {
        {1.0/9, 1.0/9, 1.0/9},
        {1.0/9, 1.0/9, 1.0/9},
        {1.0/9, 1.0/9, 1.0/9}
    };

    manager.applyFilter<ConvolutionFilter>(box3, /*padMode=*/1);
    manager.applyFilter<MedianFilter>(/*radius=*/1);
    manager.applyFilter<ThresholdFilter>(/*threshold=*/130);

    auto result = manager.saveByEnv();
    return 0;
}
