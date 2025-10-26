//
// Created by ifdancoder on 20.10.2025.
//

#include "filters/EdgeDetectionFilter.h"
#include "filters/GrayscaleErosionFilter.h"
#include "filters/GrayscaleDilationFilter.h"

EdgeDetectionFilter::EdgeDetectionFilter(std::shared_ptr<IImageSource> src, 
                                         std::shared_ptr<StructuringElement> se)
    : MorphologicalFilter(std::move(src), std::move(se)) {
}

std::shared_ptr<Image> EdgeDetectionFilter::applyFilter(std::shared_ptr<Image> in) const {
    auto dilationFilter = std::make_shared<GrayscaleDilationFilter>(nullptr, structuringElement);
    std::shared_ptr<Image> dilated = dilationFilter->applyFilter(in);

    auto erosionFilter = std::make_shared<GrayscaleErosionFilter>(nullptr, structuringElement);
    std::shared_ptr<Image> eroded = erosionFilter->applyFilter(in);

    auto out = std::make_shared<Image>(in->getWidth(), in->getHeight());
    for (int y = 0; y < in->getHeight(); ++y) {
        for (int x = 0; x < in->getWidth(); ++x) {
            double dilatedValue = dilated->at(x, y).brightness();
            double erodedValue = eroded->at(x, y).brightness();
            double diff = dilatedValue - erodedValue;

            uint8_t value = static_cast<uint8_t>(std::max(0, std::min(255, static_cast<int>(diff))));
            out->at(x, y) = Pixel(value, value, value);
        }
    }

    return out;
}
