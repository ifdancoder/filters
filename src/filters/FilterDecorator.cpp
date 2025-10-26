//
// Created by ifdancoder on 14.10.2025.
//

#include "filters/FilterDecorator.h"

FilterDecorator::FilterDecorator(std::shared_ptr<IImageSource> src) : inner(std::move(src)) {}

std::shared_ptr<Image> FilterDecorator::getImage() const {
    return applyFilter(inner->getImage());
}
