//
// Created by ifdancoder on 14.10.2025.
//

#ifndef FILTERS_FILTERDECORATOR_H
#define FILTERS_FILTERDECORATOR_H
#include <memory>

#include "core/IImageSource.h"
#include "core/StructuringElement.h"


class FilterDecorator : public IImageSource {
protected:
    std::shared_ptr<IImageSource> inner;

public:
    explicit FilterDecorator(std::shared_ptr<IImageSource> src);

    ~FilterDecorator() override = default;

    [[nodiscard]] std::shared_ptr<Image> getImage() const override;

    [[nodiscard]] virtual std::shared_ptr<Image> applyFilter(std::shared_ptr<Image> in) const = 0;
};


#endif //FILTERS_FILTERDECORATOR_H
