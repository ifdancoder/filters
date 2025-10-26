//
// Created by ifdancoder on 20.10.2025.
//

#ifndef FILTERS_MORPHOLOGICALFILTER_H
#define FILTERS_MORPHOLOGICALFILTER_H

#include "FilterDecorator.h"
#include "../core/StructuringElement.h"
#include <memory>

class MorphologicalFilter : public FilterDecorator {
protected:
    std::shared_ptr<StructuringElement> structuringElement;

    [[nodiscard]] static bool isPixelInBounds(const std::shared_ptr<Image>& img, int x, int y);

    template<typename Func>
    void iterateStructuringElement(const std::shared_ptr<Image>& input, int centerX, int centerY, Func func) const;

public:
    [[nodiscard]] static std::shared_ptr<StructuringElement> expand_structuring_element(const std::shared_ptr<StructuringElement> &se, const std::shared_ptr<StructuringElement> &se2) ;

    explicit MorphologicalFilter(std::shared_ptr<IImageSource> src, 
                                std::shared_ptr<StructuringElement> se);
};

template<typename Func>
void MorphologicalFilter::iterateStructuringElement(const std::shared_ptr<Image>& input, int centerX, int centerY, Func func) const {
    int seWidth = structuringElement->getWidth();
    int seHeight = structuringElement->getHeight();
    int seCenterX = structuringElement->getCenterX();
    int seCenterY = structuringElement->getCenterY();

    for (int seY = 0; seY < seHeight; ++seY) {
        for (int seX = 0; seX < seWidth; ++seX) {
            if (structuringElement->at(seX, seY) == Pixel::maxBrightness()) {
                int imgX = centerX + seX - seCenterX;
                int imgY = centerY + seY - seCenterY;
                func(imgX, imgY, seX, seY);
            }
        }
    }
}


#endif //FILTERS_MORPHOLOGICALFILTER_H
