//
// Created by ifdancoder on 20.10.2025.
//

#ifndef FILTERS_DOGFILTER_H
#define FILTERS_DOGFILTER_H
#include "FilterDecorator.h"
#include "GaussianFilter.h"
#include "core/StructuringElement.h"


class DogFilter : public FilterDecorator {
protected:
    double sigma1, sigma2;
    int kernelSize;
    int padMode;
    std::shared_ptr<GaussianFilter> gaussian1;
    std::shared_ptr<GaussianFilter> gaussian2;

public:
    explicit DogFilter(std::shared_ptr<IImageSource> src,
              double sigma1 = 1.0,
              double sigma2 = 2.0,
              int kernelSize = 0,
              int pad = 1);

    [[nodiscard]] std::shared_ptr<Image> applyFilter(std::shared_ptr<Image> in) const override;
};


#endif //FILTERS_DOGFILTER_H