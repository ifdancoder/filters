//
// Created by ifdancoder on 20.10.2025.
//

#include "filters/GrayscaleOpeningFilter.h"
#include "filters/GrayscaleErosionFilter.h"
#include "filters/GrayscaleDilationFilter.h"

GrayscaleOpeningFilter::GrayscaleOpeningFilter(std::shared_ptr<IImageSource> src, 
                                               std::shared_ptr<StructuringElement> se)
    : MorphologicalFilter(std::move(src), std::move(se)) {
}

std::shared_ptr<Image> GrayscaleOpeningFilter::applyFilter(std::shared_ptr<Image> in) const {
    auto erosionFilter = std::make_shared<GrayscaleErosionFilter>(nullptr, structuringElement);
    std::shared_ptr<Image> eroded = erosionFilter->applyFilter(in);

    auto dilationFilter = std::make_shared<GrayscaleDilationFilter>(nullptr, structuringElement);
    std::shared_ptr<Image> result = dilationFilter->applyFilter(std::move(eroded));

    return result;
}
