//
// Created by ifdancoder on 14.10.2025.
//

#include "filters/SharpenFilter.h"

#include <algorithm>
#include <cmath>

#include "core/Pixel.h"

SharpenFilter::SharpenFilter(std::shared_ptr<IImageSource> src,
                             double strengthInput,
                             int pad): ConvolutionFilter(std::move(src), createSharpenKernel(strengthInput), pad) {
    strength = strengthInput;
}

std::vector<std::vector<double>> SharpenFilter::createSharpenKernel(double strengthInput) {
    std::vector<std::vector<double>> tmp_kernel = {
        {0, -1, 0},
        {-1, 5, -1},
        {0, -1, 0}
    };

    tmp_kernel[1][1] = 4.0 + strengthInput;

    double sum = 0.0;
    for (const auto& row : tmp_kernel) {
        for (double val : row) {
            sum += val;
        }
    }

    if (std::abs(sum - 1.0) > 1e-6) {
        for (auto& row : tmp_kernel) {
            for (double& val : row) {
                val /= sum;
            }
        }
    }

    return tmp_kernel;
}
