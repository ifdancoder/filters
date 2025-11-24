//
// Created by ifdancoder on 20.10.2025.
//

#include "filters/DogFilter.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

#include "core/Pixel.h"
#include "core/StructuringElement.h"
#include "filters/BaseImage.h"
#include "filters/GaussianFilter.h"

DogFilter::DogFilter(std::shared_ptr<IImageSource> src,
                     double sigma1,
                     double sigma2,
                     int kernelSize,
                     int pad)
    : FilterDecorator(std::move(src)),
      sigma1(sigma1), sigma2(sigma2),
      kernelSize(kernelSize), padMode(pad),
      gaussian1(make_shared<GaussianFilter>(src, sigma1, kernelSize, pad)),
      gaussian2(make_shared<GaussianFilter>(src, sigma2, kernelSize, pad)) {
}

std::shared_ptr<Image> DogFilter::applyFilter(std::shared_ptr<Image> in) const {
    const auto after_gaussian1 = gaussian1->applyFilter(in);
    const auto after_gaussian2 = gaussian2->applyFilter(in);

    return after_gaussian1->subtract(*after_gaussian2);
}
