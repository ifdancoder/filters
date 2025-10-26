//
// Created by ifdancoder on 20.10.2025.
//

#ifndef FILTERS_GRAYSCALEEROSIONFILTER_H
#define FILTERS_GRAYSCALEEROSIONFILTER_H

#include "MorphologicalFilter.h"

class GrayscaleErosionFilter : public MorphologicalFilter {
public:
    explicit GrayscaleErosionFilter(std::shared_ptr<IImageSource> src,
                                   std::shared_ptr<StructuringElement> se);

    std::shared_ptr<Image> applyFilter(std::shared_ptr<Image> in) const override;
};

#endif //FILTERS_GRAYSCALEEROSIONFILTER_H
