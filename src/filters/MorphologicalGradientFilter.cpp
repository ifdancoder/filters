//
// Created by ifdancoder on 20.10.2025.
//

#include "filters/MorphologicalGradientFilter.h"
#include "filters/StructuringElement.h"
#include "filters/GrayscaleErosionFilter.h"
#include "filters/GrayscaleDilationFilter.h"
#include <algorithm>

MorphologicalGradientFilter::MorphologicalGradientFilter(std::shared_ptr<IImageSource> src)
    : FilterDecorator(std::move(src)) {
}

Image MorphologicalGradientFilter::applyFilter(Image &&in) const {
    Image result(in.getWidth(), in.getHeight());

    for (int y = 0; y < in.getHeight(); ++y) {
        for (int x = 0; x < in.getWidth(); ++x) {
            result.at(x, y) = Pixel(0, 0, 0);
        }
    }

    for (int i = 1; i <= 3; ++i) {
        int size = 2 * i + 1;
        auto se = StructuringElement::createSquare(size);

        auto dilationFilter = std::make_shared<GrayscaleDilationFilter>(nullptr, se);
        Image dilated = dilationFilter->applyFilter(Image(in));

        auto erosionFilter = std::make_shared<GrayscaleErosionFilter>(nullptr, se);
        Image eroded = erosionFilter->applyFilter(Image(in));

        for (int y = 0; y < in.getHeight(); ++y) {
            for (int x = 0; x < in.getWidth(); ++x) {
                double dilatedValue = dilated.at(x, y).brightness();
                double erodedValue = eroded.at(x, y).brightness();
                double gradient = dilatedValue - erodedValue;

                double currentValue = result.at(x, y).brightness();
                double newValue = currentValue + gradient;

                int tmpPixelValue = static_cast<uint8_t>(newValue);

                auto value = static_cast<uint8_t>(std::max(0, std::min(255, tmpPixelValue)));
                result.at(x, y) = Pixel(value, value, value);
            }
        }
    }

    for (int y = 0; y < in.getHeight(); ++y) {
        for (int x = 0; x < in.getWidth(); ++x) {
            double value = result.at(x, y).brightness() / 3;

            auto newPixelValue = static_cast<uint8_t>(value);

            result.at(x, y) = Pixel(newPixelValue, newPixelValue, newPixelValue);
        }
    }

    return result;
}
