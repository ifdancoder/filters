//
// Created by ifdancoder on 20.10.2025.
//

#include "core/StructuringElement.h"
#include <cmath>
#include <utility>

#include "filters/BaseImage.h"
#include "filters/BinaryDilationFilter.h"

#define STRUCTURING_ELEMENT_SIZE 3

StructuringElement::StructuringElement(int w, int h, int centerXInput, int centerYInput): Image(w, h), centerX(centerXInput), centerY(centerYInput) {
}

StructuringElement::StructuringElement(Type type): Image(STRUCTURING_ELEMENT_SIZE, STRUCTURING_ELEMENT_SIZE) {
    switch (type) {
        case SQUARE:
            w = h = STRUCTURING_ELEMENT_SIZE;
            centerX = centerY = STRUCTURING_ELEMENT_SIZE / 2;
            data.resize(h * w, Pixel::maxBrightness());
            for (int y = 0; y < h; ++y) {
                for (int x = 0; x < w; ++x) {
                    at(x, y)  = Pixel::maxBrightness();
                }
            }
            break;
            
        case RHOMBUS:
            w = h = STRUCTURING_ELEMENT_SIZE;
            centerX = centerY = STRUCTURING_ELEMENT_SIZE / 2;
            data.resize(h * w, Pixel::minBrightness());
            for (int x = 0; x < w; ++x) {
                at(x, centerY) = Pixel::maxBrightness();
            }
            for (int y = 0; y < h; ++y) {
                at(centerX, y) = Pixel::maxBrightness();
            }
            break;
            
        case DISK:
            w = h = 2 * STRUCTURING_ELEMENT_SIZE + 1;
            centerX = centerY = STRUCTURING_ELEMENT_SIZE;
            data.resize(h * w, Pixel::maxBrightness());
            for (int y = 0; y < h; ++y) {
                for (int x = 0; x < w; ++x) {
                    double distance = std::sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));
                    at(x, y)  = (distance <= STRUCTURING_ELEMENT_SIZE ? Pixel::maxBrightness() : Pixel::minBrightness());
                }
            }
            break;
    }
}

void StructuringElement::setCenter(int x, int y) {
    centerX = x;
    centerY = y;
}

std::shared_ptr<StructuringElement> StructuringElement::createSquare() {
    return std::make_shared<StructuringElement>(SQUARE);
}

std::shared_ptr<StructuringElement> StructuringElement::createRhombus() {
    return std::make_shared<StructuringElement>(RHOMBUS);
}

std::shared_ptr<StructuringElement> StructuringElement::createDisk() {
    return std::make_shared<StructuringElement>(DISK);
}

std::shared_ptr<StructuringElement> StructuringElement::dilated(Type type, std::shared_ptr<StructuringElement> se = nullptr, int n = 0) {
    auto th = std::make_shared<StructuringElement>(type);
    auto bi = std::make_shared<BaseImage>(th);

    if (se == nullptr) {
        se = std::make_shared<StructuringElement>(type);
    }

    BinaryDilationFilter filter = BinaryDilationFilter(bi, std::move(se));

    for (int i = 0; i < n; i++) {
        th = std::dynamic_pointer_cast<StructuringElement>(filter.applyFilter(th));
    }

    return th;
}

std::shared_ptr<StructuringElement> StructuringElement::dilated(Type type, int n) {
    return dilated(type, nullptr, n);
}

std::shared_ptr<StructuringElement> StructuringElement::dilated(Type type, std::shared_ptr<StructuringElement> se) {
    return dilated(type, std::move(se), 0);
}
