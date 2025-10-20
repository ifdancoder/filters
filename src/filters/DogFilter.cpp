//
// Created by ifdancoder on 20.10.2025.
//

#include "filters/DogFilter.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

#include "core/Pixel.h"
#include "filters/GaussianFilter.h"

DogFilter::DogFilter(std::shared_ptr<IImageSource> src,
                     double sigma1,
                     double sigma2,
                     int kernelSize,
                     int pad)
        : FilterDecorator(std::move(src)),
          sigma1(sigma1), sigma2(sigma2),
          kernelSize(kernelSize), padMode(pad) {

    if (sigma1 >= sigma2) {
        throw std::invalid_argument("sigma1 must be less than sigma2 for DoG filter");
    }
}

std::vector<std::vector<double>> DogFilter::createDoGKernel(double sigma1, double sigma2, int size) {
    if (size <= 0) {
        size = static_cast<int>(std::ceil(6 * sigma2));
        if (size % 2 == 0) size++;
    }

    auto kernel1 = GaussianFilter::createGaussianKernel(size, sigma1);
    auto kernel2 = GaussianFilter::createGaussianKernel(size, sigma2);

    std::vector<std::vector<double>> dogKernel(size, std::vector<double>(size, 0.0));

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            dogKernel[y][x] = kernel1[y][x] - kernel2[y][x];
        }
    }

    return dogKernel;
}