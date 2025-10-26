//
// Created by ifdancoder on 20.10.2025.
//

#ifndef FILTERS_BINARYOPENINGFILTER_H
#define FILTERS_BINARYOPENINGFILTER_H

#include "MorphologicalFilter.h"

class BinaryOpeningFilter : public MorphologicalFilter {
public:
    explicit BinaryOpeningFilter(std::shared_ptr<IImageSource> src, 
                                std::shared_ptr<StructuringElement> se);

    Image applyFilter(Image &&in) const override;
};

#endif //FILTERS_BINARYOPENINGFILTER_H
