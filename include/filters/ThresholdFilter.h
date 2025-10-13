//
// Created by ifdancoder on 14.10.2025.
//

#ifndef FILTERS_THRESHOLDER_H
#define FILTERS_THRESHOLDER_H

#include "FilterDecorator.h"

class ThresholdFilter : public FilterDecorator {
protected:
    uint8_t threshold;
    bool invert;

public:
    ThresholdFilter(std::shared_ptr<IImageSource> src, uint8_t th = 128, bool inv = false);

    Image applyFilter(Image &&in) const override;
};

#endif //FILTERS_THRESHOLDER_H
