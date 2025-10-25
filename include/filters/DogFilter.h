//
// Created by ifdancoder on 20.10.2025.
//

#ifndef FILTERS_DOGFILTER_H
#define FILTERS_DOGFILTER_H
#include "FilterDecorator.h"


class DogFilter : public FilterDecorator {
protected:
    double sigma1, sigma2;
    int kernelSize;
    int padMode;

public:
    [[nodiscard]] static std::vector<std::vector<double>> createDoGKernel(double sigma1, double sigma2, int size);

    explicit DogFilter(std::shared_ptr<IImageSource> src,
              double sigma1 = 1.0,
              double sigma2 = 2.0,
              int kernelSize = 0,
              int pad = 1);

    Image applyFilter(Image &&in) const override;
};


#endif //FILTERS_DOGFILTER_H