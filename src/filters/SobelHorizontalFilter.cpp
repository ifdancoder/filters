//
// Created by ifdancoder on 13.10.2025.
//

#include "filters/SobelHorizontalFilter.h"

SobelHorizontalFilter::SobelHorizontalFilter(std::shared_ptr<IImageSource> src, int pad)
        : GrayScaleConvolutionFilter(std::move(src), createSobelHorizontalKernel(), pad) {
}

std::vector<std::vector<double>> SobelHorizontalFilter::createSobelHorizontalKernel() {
    return {
        {-1.0, 0.0, 1.0},
        {-2.0, 0.0, 2.0},
        {-1.0, 0.0, 1.0}
    };
}

