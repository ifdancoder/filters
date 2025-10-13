//
// Created by ifdancoder on 14.10.2025.
//

#ifndef FILTERS_MEDIANFILTER_H
#define FILTERS_MEDIANFILTER_H

#include "FilterDecorator.h"


class MedianFilter : public FilterDecorator {
protected:
    int radius;

public:
    MedianFilter(std::shared_ptr<IImageSource> src, int r = 1);

    Image applyFilter(Image &&in) const override;
};


#endif //FILTERS_MEDIANFILTER_H
