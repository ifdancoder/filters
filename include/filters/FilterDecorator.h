//
// Created by ifdancoder on 14.10.2025.
//

#ifndef FILTERS_FILTERDECORATOR_H
#define FILTERS_FILTERDECORATOR_H
#include <memory>

#include "core/IImageSource.h"


class FilterDecorator : public IImageSource {
protected:
    std::shared_ptr<IImageSource> inner;

public:
    FilterDecorator(std::shared_ptr<IImageSource> src);

    virtual ~FilterDecorator() = default;

    [[nodiscard]] Image getImage() const;

    virtual Image applyFilter(Image &&in) const = 0;
};


#endif //FILTERS_FILTERDECORATOR_H
