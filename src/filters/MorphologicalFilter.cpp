//
// Created by ifdancoder on 20.10.2025.
//

#include "filters/MorphologicalFilter.h"

MorphologicalFilter::MorphologicalFilter(std::shared_ptr<IImageSource> src, 
                                         std::shared_ptr<StructuringElement> se)
    : FilterDecorator(std::move(src)), structuringElement(std::move(se)) {
}

bool MorphologicalFilter::isPixelInBounds(const Image& img, int x, int y) {
    return x >= 0 && x < img.getWidth() && y >= 0 && y < img.getHeight();
}

template<typename Func>
void MorphologicalFilter::iterateStructuringElement(const Image& input, int centerX, int centerY, Func func) const {
    int seWidth = structuringElement->getWidth();
    int seHeight = structuringElement->getHeight();
    int seCenterX = structuringElement->getCenterX();
    int seCenterY = structuringElement->getCenterY();

    for (int seY = 0; seY < seHeight; ++seY) {
        for (int seX = 0; seX < seWidth; ++seX) {
            if (structuringElement->at(seX, seY)) {
                int imgX = centerX + seX - seCenterX;
                int imgY = centerY + seY - seCenterY;
                func(imgX, imgY, seX, seY);
            }
        }
    }
}