//
// Created by ifdancoder on 13.10.2025.
//

#ifndef FILTERS_SOBELDIAGONALFILTER_H
#define FILTERS_SOBELDIAGONALFILTER_H

#include <memory>
#include <vector>
#include "FilterDecorator.h"
#include "GrayScaleConvolutionFilter.h"

class SobelDiagonalFilter : public GrayScaleConvolutionFilter {
public:
    explicit SobelDiagonalFilter(std::shared_ptr<IImageSource> src, int angle = 45, int pad = 1);

    static std::vector<std::vector<double>> createSobelDiagonalKernel(int angle);
};

#endif //FILTERS_SOBELDIAGONALFILTER_H

