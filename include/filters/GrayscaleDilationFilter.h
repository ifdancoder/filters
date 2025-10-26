//
// Created by ifdancoder on 20.10.2025.
//

#ifndef FILTERS_GRAYSCALEDILATIONFILTER_H
#define FILTERS_GRAYSCALEDILATIONFILTER_H

#include "MorphologicalFilter.h"

class GrayscaleDilationFilter : public MorphologicalFilter {
public:
    explicit GrayscaleDilationFilter(std::shared_ptr<IImageSource> src, 
                                    std::shared_ptr<StructuringElement> se);

    std::shared_ptr<Image> applyFilter(std::shared_ptr<Image> in) const override;
};

#endif //FILTERS_GRAYSCALEDILATIONFILTER_H
