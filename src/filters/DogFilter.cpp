//
// Created by ifdancoder on 20.10.2025.
//

#include "filters/DogFilter.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

#include "core/Pixel.h"
#include "core/StructuringElement.h"
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

std::shared_ptr<Image> DogFilter::applyFilter(std::shared_ptr<Image> in) const {
    auto kernel = createDoGKernel(sigma1, sigma2, kernelSize);
    int kH = static_cast<int>(kernel.size());
    int kW = kH ? static_cast<int>(kernel[0].size()) : 0;
    int kcx = kW / 2;
    int kcy = kH / 2;
    
    auto out = std::make_shared<Image>(in->getWidth(), in->getHeight());
    
    for (int y = 0; y < in->getHeight(); ++y) {
        for (int x = 0; x < in->getWidth(); ++x) {
            Pixel sum = Pixel();
            for (int ky = 0; ky < kH; ++ky) {
                for (int kx = 0; kx < kW; ++kx) {
                    int ix = x + (kx - kcx);
                    int iy = y + (ky - kcy);
                    
                    Pixel s;
                    if (ix < 0 || ix >= in->getWidth() || iy < 0 || iy >= in->getHeight()) {
                        if (padMode == 0) {
                            s = Pixel(0);
                        } else {
                            ix = std::clamp(ix, 0, in->getWidth() - 1);
                            iy = std::clamp(iy, 0, in->getHeight() - 1);
                            s = in->at(ix, iy);
                        }
                    } else {
                        s = in->at(ix, iy);
                    }
                    
                    sum += kernel[ky][kx] * s;
                }
            }
            sum.clamp();
            out->at(x, y) = sum;
        }
    }
    
    return out;
}