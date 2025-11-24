//
// Created by ifdancoder on 16.11.2025.
//

#ifndef FILTERS_CANNYFILTER_H
#define FILTERS_CANNYFILTER_H

#include "FilterDecorator.h"
#include <vector>

class CannyFilter : public FilterDecorator {
protected:
    double lowThreshold;
    double highThreshold;

public:
    explicit CannyFilter(std::shared_ptr<IImageSource> src,
                        double low = 40.0,
                        double high = 200.0);

    [[nodiscard]] std::shared_ptr<Image> applyFilter(std::shared_ptr<Image> in) const override;
};

#endif //FILTERS_CANNYFILTER_H

