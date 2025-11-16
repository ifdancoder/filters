//
// Created by ifdancoder on 16.11.2025.
//

#ifndef FILTERS_MOSAICFILTER_H
#define FILTERS_MOSAICFILTER_H

#include "FilterDecorator.h"


class MosaicFilter : public FilterDecorator {
protected:
    int blockSize;

public:
    explicit MosaicFilter(std::shared_ptr<IImageSource> src, int size = 10);

    [[nodiscard]] std::shared_ptr<Image> applyFilter(std::shared_ptr<Image> in) const override;
};


#endif //FILTERS_MOSAICFILTER_H

