//
// Created by ifdancoder on 20.10.2025.
//

#include "filters/BinaryClosingFilter.h"
#include "filters/BinaryErosionFilter.h"
#include "filters/BinaryDilationFilter.h"

BinaryClosingFilter::BinaryClosingFilter(std::shared_ptr<IImageSource> src, 
                                         std::shared_ptr<StructuringElement> se)
    : MorphologicalFilter(std::move(src), std::move(se)) {
}

std::shared_ptr<Image> BinaryClosingFilter::applyFilter(std::shared_ptr<Image> in) const {
    auto dilationFilter = std::make_shared<BinaryDilationFilter>(nullptr, structuringElement);
    std::shared_ptr<Image> dilated = dilationFilter->applyFilter(in);

    auto erosionFilter = std::make_shared<BinaryErosionFilter>(nullptr, structuringElement);
    std::shared_ptr<Image> result = erosionFilter->applyFilter(std::move(dilated));

    return result;
}
