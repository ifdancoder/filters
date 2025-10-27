//
// Created by ifdancoder on 20.10.2025.
//

#ifndef FILTERS_BINARYEROSIONFILTER_H
#define FILTERS_BINARYEROSIONFILTER_H

#include "MorphologicalFilter.h"

class BinaryErosionFilter : public MorphologicalFilter {
public:
    explicit BinaryErosionFilter(std::shared_ptr<IImageSource> src, 
                                std::shared_ptr<StructuringElement> se);

    [[nodiscard]] std::shared_ptr<Image> applyFilter(std::shared_ptr<Image> in) const override;
};

#endif //FILTERS_BINARYEROSIONFILTER_H
