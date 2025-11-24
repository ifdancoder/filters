//
// Created by ifdancoder on 13.10.2025.
//

#ifndef FILTERS_SOBELVERTICALFILTER_H
#define FILTERS_SOBELVERTICALFILTER_H

#include <memory>
#include <vector>
#include "GrayScaleConvolutionFilter.h"
#include "FilterDecorator.h"

class SobelVerticalFilter : public GrayScaleConvolutionFilter {
public:
    explicit SobelVerticalFilter(std::shared_ptr<IImageSource> src, int pad = 1);

    static std::vector<std::vector<double>> createSobelVerticalKernel();
};

#endif //FILTERS_SOBELVERTICALFILTER_H

