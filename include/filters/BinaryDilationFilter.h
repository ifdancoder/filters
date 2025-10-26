//
// Created by ifdancoder on 20.10.2025.
//

#ifndef FILTERS_BINARYDILATIONFILTER_H
#define FILTERS_BINARYDILATIONFILTER_H

#include "MorphologicalFilter.h"

class BinaryDilationFilter : public MorphologicalFilter {
public:
    explicit BinaryDilationFilter(std::shared_ptr<IImageSource> src, 
                                 std::shared_ptr<StructuringElement> se);

    std::shared_ptr<Image> applyFilter(std::shared_ptr<Image> in) const override;
};

#endif //FILTERS_BINARYDILATIONFILTER_H
