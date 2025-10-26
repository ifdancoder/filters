//
// Created by ifdancoder on 20.10.2025.
//

#include "filters/BinaryOpeningFilter.h"
#include "filters/BinaryErosionFilter.h"
#include "filters/BinaryDilationFilter.h"

BinaryOpeningFilter::BinaryOpeningFilter(std::shared_ptr<IImageSource> src, 
                                         std::shared_ptr<StructuringElement> se)
    : MorphologicalFilter(std::move(src), std::move(se)) {
}

std::shared_ptr<Image> BinaryOpeningFilter::applyFilter(std::shared_ptr<Image> in) const {
    auto erosionFilter = std::make_shared<BinaryErosionFilter>(nullptr, structuringElement);
    std::shared_ptr<Image> eroded = erosionFilter->applyFilter(in);

    auto dilationFilter = std::make_shared<BinaryDilationFilter>(nullptr, structuringElement);
    std::shared_ptr<Image> result = dilationFilter->applyFilter(std::move(eroded));

    return result;
}
