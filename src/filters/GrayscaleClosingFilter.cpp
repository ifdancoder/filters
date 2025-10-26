//
// Created by ifdancoder on 20.10.2025.
//

#include "filters/GrayscaleClosingFilter.h"
#include "filters/GrayscaleErosionFilter.h"
#include "filters/GrayscaleDilationFilter.h"

GrayscaleClosingFilter::GrayscaleClosingFilter(std::shared_ptr<IImageSource> src, 
                                               std::shared_ptr<StructuringElement> se)
    : MorphologicalFilter(std::move(src), std::move(se)) {
}

Image GrayscaleClosingFilter::applyFilter(Image &&in) const {
    auto dilationFilter = std::make_shared<GrayscaleDilationFilter>(nullptr, structuringElement);
    Image dilated = dilationFilter->applyFilter(Image(in));

    auto erosionFilter = std::make_shared<GrayscaleErosionFilter>(nullptr, structuringElement);
    Image result = erosionFilter->applyFilter(std::move(dilated));

    return result;
}
