//
// Created by ifdancoder on 14.10.2025.
//

#include "filters/ConvolutionFilter.h"

#include <algorithm>
#include <cmath>

#include "core/Pixel.h"
#include "core/StructuringElement.h"

ConvolutionFilter::ConvolutionFilter(std::shared_ptr<IImageSource> src,
                                     const std::vector<std::vector<double> > &kern,
                                     int pad)
        : FilterDecorator(std::move(src)), kernel(kern), padMode(pad) {
    kH = (int) kernel.size();
    kW = kH ? (int) kernel[0].size() : 0;
}

Pixel ConvolutionFilter::sample(const std::shared_ptr<Image> &img, int x, int y) const {
    if (x < 0 || x >= img->getWidth() || y < 0 || y >= img->getHeight()) {
        if (padMode == 0) return Pixel(0);
        x = std::clamp(x, 0, img->getWidth() - 1);
        y = std::clamp(y, 0, img->getHeight() - 1);
        return img->at(x, y);
    }
    return img->at(x, y);
}

std::shared_ptr<Image> ConvolutionFilter::applyFilter(std::shared_ptr<Image> in) const {
    auto out = std::make_shared<Image>(in->getWidth(), in->getHeight());
    int kcx = kW / 2;
    int kcy = kH / 2;

    for (int y = 0; y < in->getHeight(); ++y) {
        for (int x = 0; x < in->getWidth(); ++x) {
            Pixel sum = Pixel();
            for (int ky = 0; ky < kH; ++ky) {
                for (int kx = 0; kx < kW; ++kx) {
                    int ix = x + (kx - kcx);
                    int iy = y + (ky - kcy);
                    Pixel s = sample(in, ix, iy);
                    sum += kernel[ky][kx] * s;
                }
            }
            sum.clamp();
            out->at(x, y) = sum;
        }
    }
    return out;
}