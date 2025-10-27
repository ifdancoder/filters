//
// Created by ifdancoder on 20.10.2025.
//

#ifndef FILTERS_GRAYSCALECLOSINGFILTER_H
#define FILTERS_GRAYSCALECLOSINGFILTER_H

#include "MorphologicalFilter.h"

class GrayscaleClosingFilter : public MorphologicalFilter {
public:
    explicit GrayscaleClosingFilter(std::shared_ptr<IImageSource> src, 
                                   std::shared_ptr<StructuringElement> se);

    [[nodiscard]] std::shared_ptr<Image> applyFilter(std::shared_ptr<Image> in) const override;
};

#endif //FILTERS_GRAYSCALECLOSINGFILTER_H
