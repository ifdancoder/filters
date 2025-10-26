//
// Created by ifdancoder on 20.10.2025.
//

#ifndef FILTERS_MORPHOLOGICALFILTER_H
#define FILTERS_MORPHOLOGICALFILTER_H

#include "FilterDecorator.h"
#include "StructuringElement.h"
#include <memory>

class MorphologicalFilter : public FilterDecorator {
protected:
    std::shared_ptr<StructuringElement> structuringElement;

    [[nodiscard]] static bool isPixelInBounds(const Image& img, int x, int y) ;

    template<typename Func>
    void iterateStructuringElement(const Image& input, int centerX, int centerY, Func func) const;

public:
    explicit MorphologicalFilter(std::shared_ptr<IImageSource> src, 
                                std::shared_ptr<StructuringElement> se);
};

// Шаблонная реализация


#endif //FILTERS_MORPHOLOGICALFILTER_H
