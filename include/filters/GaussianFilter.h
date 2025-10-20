//
// Created by ifdancoder on 20.10.2025.
//

#ifndef FILTERS_GAUSSIANFILTER_H
#define FILTERS_GAUSSIANFILTER_H

#include <core/Pixel.h>
#include <memory>
#include <vector>

#include "ConvolutionFilter.h"
#include "FilterDecorator.h"

class GaussianFilter : public ConvolutionFilter {
protected:
    double sigma;

public:
    static std::vector<std::vector<double>>  createGaussianKernel(int size, double sigma);

    explicit GaussianFilter(std::shared_ptr<IImageSource> src,
                   double sigma = 1.0,
                   int kernelSize = 0,
                   int pad = 1);
};

#endif //FILTERS_GAUSSIANFILTER_H