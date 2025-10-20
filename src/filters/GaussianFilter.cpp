//
// Created by ifdancoder on 20.10.2025.
//

#include "filters/GaussianFilter.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>

#include "core/Pixel.h"

GaussianFilter::GaussianFilter(std::shared_ptr<IImageSource> src,
                               double sigma,
                               int kernelSize,
                               int pad)
        : ConvolutionFilter(std::move(src), createGaussianKernel(kernelSize, sigma), pad), sigma(sigma) {

    if (kernelSize <= 0) {
        kernelSize = static_cast<int>(std::ceil(6 * sigma));
        if (kernelSize % 2 == 0) kernelSize++;
    }

    if (kernelSize % 2 == 0) {
        throw std::invalid_argument("Kernel size must be odd");
    }

    ;
    kH = static_cast<int>(kernel.size());
    kW = kH ? static_cast<int>(kernel[0].size()) : 0;
}

std::vector<std::vector<double>> GaussianFilter::createGaussianKernel(int size, double sigma) {
    std::vector<std::vector<double>> tmp_kernel(size, std::vector<double>(size, 0.0));

    int center = size / 2;
    double sum = 0.0;
    double sigmaSquared = 2.0 * sigma * sigma;

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            int dx = x - center;
            int dy = y - center;
            double value = std::exp(-(dx * dx + dy * dy) / sigmaSquared);
            tmp_kernel[y][x] = value;
            sum += value;
        }
    }

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            tmp_kernel[y][x] /= sum;
        }
    }

    return tmp_kernel;
}