//
// Created by ifdancoder on 20.10.2025.
//

#ifndef FILTERS_GRAYSCALEOPENINGFILTER_H
#define FILTERS_GRAYSCALEOPENINGFILTER_H

#include "MorphologicalFilter.h"

class GrayscaleOpeningFilter : public MorphologicalFilter {
public:
    explicit GrayscaleOpeningFilter(std::shared_ptr<IImageSource> src, 
                                   std::shared_ptr<StructuringElement> se);

    std::shared_ptr<Image> applyFilter(std::shared_ptr<Image> in) const override;
};

#endif //FILTERS_GRAYSCALEOPENINGFILTER_H
