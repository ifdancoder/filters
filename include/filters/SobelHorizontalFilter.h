//
// Created by ifdancoder on 13.10.2025.
//

#ifndef FILTERS_SOBELHORIZONTALFILTER_H
#define FILTERS_SOBELHORIZONTALFILTER_H

#include <memory>
#include <vector>
#include "GrayScaleConvolutionFilter.h"
#include "FilterDecorator.h"

class SobelHorizontalFilter : public GrayScaleConvolutionFilter {
public:
    explicit SobelHorizontalFilter(std::shared_ptr<IImageSource> src, int pad = 1);

    static std::vector<std::vector<double>> createSobelHorizontalKernel();
};

#endif //FILTERS_SOBELHORIZONTALFILTER_H

