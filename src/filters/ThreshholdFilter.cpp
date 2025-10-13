//
// Created by ifdancoder on 14.10.2025.
//

#include "filters/ThresholdFilter.h"

ThresholdFilter::ThresholdFilter(std::shared_ptr<IImageSource> src, uint8_t th, bool inv)
    : FilterDecorator(std::move(src)), threshold(th), invert(inv) {
}

Image ThresholdFilter::applyFilter(Image &&in) const {
    Image out(in.getWidth(), in.getHeight());
    for (int i = 0; i < in.getWidth() * in.getHeight(); ++i) {
        uint8_t v = in.at(i);
        uint8_t res = (v >= threshold) ? 255 : 0;
        if (invert) res = 255 - res;
        out.at(i) = res;
    }
    return out;
}
