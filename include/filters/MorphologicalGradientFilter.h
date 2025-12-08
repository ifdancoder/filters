//
// Created by ifdancoder on 20.10.2025.
//

#ifndef FILTERS_MORPHOLOGICALGRADIENTFILTER_H
#define FILTERS_MORPHOLOGICALGRADIENTFILTER_H

#include "FilterDecorator.h"
#include <memory>

class MorphologicalGradientFilter : public FilterDecorator {
protected:
    uint8_t iterations = 3;
    StructuringElement::Type _type;
public:
    explicit MorphologicalGradientFilter(std::shared_ptr<IImageSource> src, StructuringElement::Type t, uint8_t iterations = 3);

    [[nodiscard]] std::shared_ptr<Image> applyFilter(std::shared_ptr<Image> in) const override;
};

#endif //FILTERS_MORPHOLOGICALGRADIENTFILTER_H
