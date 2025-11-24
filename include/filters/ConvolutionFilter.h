//
// Created by ifdancoder on 14.10.2025.
//

#ifndef FILTERS_CONVOLUTIONFILTER_H
#define FILTERS_CONVOLUTIONFILTER_H

#include <core/Pixel.h>

#include "FilterDecorator.h"
#include "core/StructuringElement.h"

class ConvolutionFilter : public FilterDecorator {
protected:
    std::vector<std::vector<double> > kernel;
    int kW, kH;
    int padMode;

public:
    ConvolutionFilter(std::shared_ptr<IImageSource> src,
                      const std::vector<std::vector<double>> &kern,
                      int pad = 1);

    [[nodiscard]] virtual Pixel sample(const std::shared_ptr<Image> &img, int x, int y) const;

    [[nodiscard]] std::shared_ptr<Image> applyFilter(std::shared_ptr<Image> in) const override;
};


#endif //FILTERS_CONVOLUTIONFILTER_H
