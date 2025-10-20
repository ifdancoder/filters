//
// Created by ifdancoder on 20.10.2025.
//

#ifndef FILTERS_GAUSSIANFILTER_H
#define FILTERS_GAUSSIANFILTER_H

#include <core/Pixel.h>
#include <memory>
#include <vector>

#include "FilterDecorator.h"

class GaussianFilter : public FilterDecorator {
private:
    std::vector<std::vector<double>> kernel;
    int kW, kH;
    int padMode;
    double sigma;

    void createGaussianKernel(int size, double sigma);

public:
    explicit GaussianFilter(std::shared_ptr<IImageSource> src,
                   double sigma = 1.0,
                   int kernelSize = 0,
                   int pad = 1);

    [[nodiscard]] Pixel sample(const Image &img, int x, int y) const;

    Image applyFilter(Image &&in) const override;
};

#endif //FILTERS_GAUSSIANFILTER_H