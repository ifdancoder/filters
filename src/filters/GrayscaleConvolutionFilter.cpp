//
// Created by ifdancoder on 14.10.2025.
//

#include "filters/GrayScaleConvolutionFilter.h"

#include <algorithm>

#include "core/Pixel.h"
#include "core/StructuringElement.h"

GrayScaleConvolutionFilter::GrayScaleConvolutionFilter(std::shared_ptr<IImageSource> src,
const std::vector<std::vector<double>> &kern, int pad)
    : ConvolutionFilter(std::move(src), kern, pad) {
}

Pixel GrayScaleConvolutionFilter::sample(const std::shared_ptr<Image> &img, int x, int y) const {
    Pixel pixel;

    if (x < 0 || x >= img->getWidth() || y < 0 || y >= img->getHeight()) {
        if (padMode == 0) return Pixel(0);
        x = std::clamp(x, 0, img->getWidth() - 1);
        y = std::clamp(y, 0, img->getHeight() - 1);
        pixel = img->at(x, y);
    } else {
        pixel = img->at(x, y);
    }

    return pixel.getGrayscaled();
}
