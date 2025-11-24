//
// Created by ifdancoder on 13.10.2025.
//

#include "filters/SobelDiagonalFilter.h"
#include <stdexcept>

SobelDiagonalFilter::SobelDiagonalFilter(std::shared_ptr<IImageSource> src, int angle, int pad)
        : GrayScaleConvolutionFilter(std::move(src), createSobelDiagonalKernel(angle), pad) {
    if (angle != 45 && angle != 135) {
        throw std::invalid_argument("Angle must be 45 or 135 degrees");
    }
}

std::vector<std::vector<double>> SobelDiagonalFilter::createSobelDiagonalKernel(int angle) {
    if (angle == 45) {
        return {
            {-2.0, -1.0,  0.0},
            {-1.0,  0.0,  1.0},
            { 0.0,  1.0,  2.0}
        };
    }
    if (angle == 135) {
        return {
            { 0.0,  1.0,  2.0},
            {-1.0,  0.0,  1.0},
            {-2.0, -1.0,  0.0}
        };
    }
    throw std::invalid_argument("Angle must be 45 or 135 degrees");
}

