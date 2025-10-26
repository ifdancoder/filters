//
// Created by ifdancoder on 20.10.2025.
//

#include "filters/MorphologicalFilter.h"

#include <map>

MorphologicalFilter::MorphologicalFilter(std::shared_ptr<IImageSource> src, 
                                         std::shared_ptr<StructuringElement> se)
    : FilterDecorator(std::move(src)), structuringElement(std::move(se)) {
}


bool MorphologicalFilter::isPixelInBounds(const std::shared_ptr<Image>& img, int x, int y) {
    return x >= 0 && x < img->getWidth() && y >= 0 && y < img->getHeight();
}

std::shared_ptr<StructuringElement> MorphologicalFilter::expand_structuring_element(const std::shared_ptr<StructuringElement> &se, const std::shared_ptr<StructuringElement> &se2) {
    int width = se2->getWidth();
    int height = se2->getHeight();

    int current_width = se->getWidth();
    int current_height = se->getHeight();

    int anchorX = se2->getCenterX();
    int anchorY = se2->getCenterY();

    int current_anchorX = se->getCenterX();
    int current_anchorY = se->getCenterY();

    int expandLeft = anchorX;
    int expandRight = width - anchorX - 1;
    int expandTop = anchorY;
    int expandBottom = height - anchorY - 1;

    int newWidth = current_width + expandLeft + expandRight;
    int newHeight = current_height + expandTop + expandBottom;

    int new_anchorX = current_anchorX + expandLeft;
    int new_anchorY = current_anchorY + expandTop;

    std::shared_ptr<StructuringElement> expanded = std::make_shared<StructuringElement>(newWidth, newHeight, new_anchorX, new_anchorY);

    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            expanded->at(x, y) = Pixel::minBrightness();
        }
    }

    int offsetX = expandLeft;
    int offsetY = expandTop;

    for (int y = 0; y < current_height; ++y) {
        for (int x = 0; x < current_width; ++x) {
            expanded->at(x + offsetX, y + offsetY) = se->at(x, y);
        }
    }

    return expanded;
}