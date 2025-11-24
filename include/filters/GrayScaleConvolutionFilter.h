//
// Created by ifdancoder on 14.10.2025.
//

#ifndef FILTERS_GRAYSCALECONVOLUTIONFILTER_H
#define FILTERS_GRAYSCALECONVOLUTIONFILTER_H

#include <core/Pixel.h>

#include "ConvolutionFilter.h"
#include "core/StructuringElement.h"

class GrayScaleConvolutionFilter : public ConvolutionFilter {
public:
    GrayScaleConvolutionFilter(std::shared_ptr<IImageSource> src,
                      const std::vector<std::vector<double>> &kern,
                      int pad = 1);

    [[nodiscard]] Pixel sample(const std::shared_ptr<Image> &img, int x, int y) const override;
};


#endif //FILTERS_GRAYSCALECONVOLUTIONFILTER_H
