#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

#include <core/IImageSource.h>
#include <core/Image.h>
#include <filters/BaseImage.h>

#include "filters/ConvolutionFilter.h"
#include "filters/MedianFilter.h"
#include "filters/ThresholdFilter.h"

#include "helpers.hpp"

int main() {
    int W = 32, H = 12;
    Image src(W, H);
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            int val = (x * 255) / (W - 1);
            if ((x + y * 7) % 13 == 0) val = std::clamp(val + 80, 0, 255);
            src.at(x, y) = static_cast<uint8_t>(val);
        }
    }

    std::cout << "Исходное изображение:\n";
    printImageASCII(src);

    std::shared_ptr<BaseImage> base;
    base = std::make_shared<BaseImage>(src);

    std::vector<std::vector<double>> box3 = {
        {1.0/9, 1.0/9, 1.0/9},
        {1.0/9, 1.0/9, 1.0/9},
        {1.0/9, 1.0/9, 1.0/9}
    };

    std::shared_ptr<IImageSource> conv = std::make_shared<ConvolutionFilter>(base, box3, /*padMode=*/1);
    std::shared_ptr<IImageSource> med  = std::make_shared<MedianFilter>(conv, /*radius=*/1);
    std::shared_ptr<IImageSource> thr  = std::make_shared<ThresholdFilter>(med, /*threshold=*/130);

    Image afterConv = conv->getImage();
    std::cout << "\nПосле свёртки (размытие):\n";
    printImageASCII(afterConv);

    Image afterMed = med->getImage();
    std::cout << "\nПосле медианного фильтра:\n";
    printImageASCII(afterMed);

    Image afterThr = thr->getImage();
    std::cout << "\nПосле пороговой (логической) фильтрации:\n";
    printImageASCII(afterThr);

    return 0;
}
