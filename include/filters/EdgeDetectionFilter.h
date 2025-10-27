//
// Created by ifdancoder on 20.10.2025.
//

#ifndef FILTERS_EDGEDETECTIONFILTER_H
#define FILTERS_EDGEDETECTIONFILTER_H

#include "MorphologicalFilter.h"

class EdgeDetectionFilter : public MorphologicalFilter {
public:
    explicit EdgeDetectionFilter(std::shared_ptr<IImageSource> src, 
                                std::shared_ptr<StructuringElement> se);

    [[nodiscard]] std::shared_ptr<Image> applyFilter(std::shared_ptr<Image> in) const override;
};

#endif //FILTERS_EDGEDETECTIONFILTER_H
