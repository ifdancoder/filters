//
// Created by ifdancoder on 20.10.2025.
//

#ifndef FILTERS_SHARPENFILTER_H
#define FILTERS_SHARPENFILTER_H
#include "ConvolutionFilter.h"
#include "FilterDecorator.h"


class SharpenFilter : public ConvolutionFilter {
protected:
    double strength;

public:
    static std::vector<std::vector<double>> createSharpenKernel(double strength);

    explicit SharpenFilter(std::shared_ptr<IImageSource> src,
                  double strength = 1.0,
                  int pad = 1);
};

#endif //FILTERS_SHARPENFILTER_H