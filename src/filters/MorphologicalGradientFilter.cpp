//
// Created by ifdancoder on 20.10.2025.
//

#include "filters/MorphologicalGradientFilter.h"
#include "../../include/core/StructuringElement.h"
#include "filters/GrayscaleErosionFilter.h"
#include "filters/GrayscaleDilationFilter.h"
#include <algorithm>

MorphologicalGradientFilter::MorphologicalGradientFilter(std::shared_ptr<IImageSource> src, StructuringElement::Type t)
    : FilterDecorator(std::move(src)), _type(t) {
}

std::shared_ptr<Image> MorphologicalGradientFilter::applyFilter(std::shared_ptr<Image> in) const {
    auto out = std::make_shared<Image>(in->getWidth(), in->getHeight());

    for (int y = 0; y < in->getHeight(); ++y) {
        for (int x = 0; x < in->getWidth(); ++x) {
            out->at(x, y) = Pixel(0, 0, 0);
        }
    }

    for (int i = 1; i <= 3; ++i) {
        auto se = StructuringElement::dilated(_type, i);

        auto dilationFilter = std::make_shared<GrayscaleDilationFilter>(nullptr, se);
        std::shared_ptr<Image> dilated = dilationFilter->applyFilter(in);

        auto erosionFilter = std::make_shared<GrayscaleErosionFilter>(nullptr, se);
        std::shared_ptr<Image> eroded = erosionFilter->applyFilter(in);

        for (int y = 0; y < in->getHeight(); ++y) {
            for (int x = 0; x < in->getWidth(); ++x) {
                double dilatedValue = dilated->at(x, y).brightness();
                double erodedValue = eroded->at(x, y).brightness();
                double gradient = dilatedValue - erodedValue;

                double currentValue = out->at(x, y).brightness();
                double newValue = currentValue + gradient;

                int tmpPixelValue = static_cast<uint8_t>(newValue);

                auto value = static_cast<uint8_t>(std::max(0, std::min(255, tmpPixelValue)));
                out->at(x, y) += Pixel(value, value, value);
            }
        }
    }

    for (int y = 0; y < in->getHeight(); ++y) {
        for (int x = 0; x < in->getWidth(); ++x) {
            double value = out->at(x, y).brightness() / 3;

            auto newPixelValue = static_cast<uint8_t>(value);

            out->at(x, y) = Pixel(newPixelValue, newPixelValue, newPixelValue);
        }
    }

    return out;
}
