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

std::shared_ptr<Image> GrayscaleClosingFilter::applyFilter(std::shared_ptr<Image> in) const {
    auto dilationFilter = std::make_shared<GrayscaleDilationFilter>(nullptr, structuringElement);
    std::shared_ptr<Image> dilated = dilationFilter->applyFilter(in);

    auto erosionFilter = std::make_shared<GrayscaleErosionFilter>(nullptr, structuringElement);
    std::shared_ptr<Image> result = erosionFilter->applyFilter(std::move(dilated));

    return result;
}
