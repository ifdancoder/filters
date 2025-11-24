//
// Created by ifdancoder on 13.10.2025.
//

#include "filters/SobelVerticalFilter.h"

SobelVerticalFilter::SobelVerticalFilter(std::shared_ptr<IImageSource> src, int pad)
        : GrayScaleConvolutionFilter(std::move(src), createSobelVerticalKernel(), pad) {
}

std::vector<std::vector<double>> SobelVerticalFilter::createSobelVerticalKernel() {
    return {
        {-1.0, -2.0, -1.0},
        { 0.0,  0.0,  0.0},
        { 1.0,  2.0,  1.0}
    };
}

