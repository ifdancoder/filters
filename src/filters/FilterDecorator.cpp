//
// Created by ifdancoder on 14.10.2025.
//

#include "filters/FilterDecorator.h"

FilterDecorator::FilterDecorator(std::shared_ptr<IImageSource> src) : inner(std::move(src)) {}

Image FilterDecorator::getImage() const {
    Image in = inner->getImage();
    return applyFilter(std::move(in));
}
