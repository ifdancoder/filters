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
        : FilterDecorator(std::move(src)), padMode(pad), sigma(sigma) {

    if (kernelSize <= 0) {
        kernelSize = static_cast<int>(std::ceil(6 * sigma));
        if (kernelSize % 2 == 0) kernelSize++; // делаем нечетным
    }

    if (kernelSize % 2 == 0) {
        throw std::invalid_argument("Kernel size must be odd");
    }

    createGaussianKernel(kernelSize, sigma);
    kH = static_cast<int>(kernel.size());
    kW = kH ? static_cast<int>(kernel[0].size()) : 0;
}

void GaussianFilter::createGaussianKernel(int size, double sigma) {
    kernel.resize(size, std::vector<double>(size, 0.0));

    int center = size / 2;
    double sum = 0.0;
    double sigmaSquared = 2.0 * sigma * sigma;

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            int dx = x - center;
            int dy = y - center;
            double value = std::exp(-(dx * dx + dy * dy) / sigmaSquared);
            kernel[y][x] = value;
            sum += value;
        }
    }

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            kernel[y][x] /= sum;
        }
    }
}

[[nodiscard]] Pixel GaussianFilter::sample(const Image &img, int x, int y) const {
    if (x < 0 || x >= img.getWidth() || y < 0 || y >= img.getHeight()) {
        if (padMode == 0) return Pixel(0);
        x = std::clamp(x, 0, img.getWidth() - 1);
        y = std::clamp(y, 0, img.getHeight() - 1);
        return img.at(x, y);
    }
    return img.at(x, y);
}

Image GaussianFilter::applyFilter(Image &&in) const {
    Image out(in.getWidth(), in.getHeight());
    int kcx = kW / 2;
    int kcy = kH / 2;

    for (int y = 0; y < in.getHeight(); ++y) {
        for (int x = 0; x < in.getWidth(); ++x) {
            Pixel sum = Pixel();
            for (int ky = 0; ky < kH; ++ky) {
                for (int kx = 0; kx < kW; ++kx) {
                    int ix = x + (kx - kcx);
                    int iy = y + (ky - kcy);
                    Pixel s = sample(in, ix, iy);
                    sum += kernel[ky][kx] * s;
                }
            }
            out.at(x, y) = sum;
        }
    }
    return out;
}