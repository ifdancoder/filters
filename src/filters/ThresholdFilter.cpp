//
// Created by ifdancoder on 14.10.2025.
//

#include "filters/ThresholdFilter.h"

ThresholdFilter::ThresholdFilter(std::shared_ptr<IImageSource> src, uint8_t th, bool inv)
    : FilterDecorator(std::move(src)), threshold(th), invert(inv) {
}

std::shared_ptr<Image> ThresholdFilter::applyFilter(std::shared_ptr<Image> in) const {
    auto out = std::make_shared<Image>(in->getWidth(), in->getHeight());
    for (int i = 0; i < in->getWidth() * in->getHeight(); ++i) {
        Pixel v = in->at(i);
        Pixel res = (v >= threshold) ? Pixel::maxBrightness() : Pixel::minBrightness();
        if (invert) {
            res = res.invert();
        }
        out->at(i) = res;
    }
    return out;
}
