//
// Created by ifdancoder on 20.10.2025.
//

#include "core/StructuringElement.h"
#include <cmath>

StructuringElement::StructuringElement(int w, int h, int centerXInput, int centerYInput): Image(w, h), centerX(centerXInput), centerY(centerYInput) {
}

StructuringElement::StructuringElement(Type type, int size = 3): Image(size, size) {
    switch (type) {
        case SQUARE:
            w = h = size;
            centerX = centerY = size / 2;
            data.resize(h * w, Pixel::maxBrightness());
            for (int y = 0; y < h; ++y) {
                for (int x = 0; x < w; ++x) {
                    at(x, y)  = Pixel::maxBrightness();
                }
            }
            break;
            
        case RHOMBUS:
            w = h = size;
            centerX = centerY = size / 2;
            data.resize(h * w, Pixel::minBrightness());
            for (int x = 0; x < w; ++x) {
                at(x, centerY) = Pixel::maxBrightness();
            }
            for (int y = 0; y < h; ++y) {
                at(centerX, y) = Pixel::maxBrightness();
            }
            break;
            
        case DISK:
            w = h = 2 * size + 1;
            centerX = centerY = size;
            data.resize(h * w, Pixel::maxBrightness());
            for (int y = 0; y < h; ++y) {
                for (int x = 0; x < w; ++x) {
                    double distance = std::sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));
                    at(x, y)  = (distance <= size ? Pixel::maxBrightness() : Pixel::minBrightness());
                }
            }
            break;
    }
}

void StructuringElement::setCenter(int x, int y) {
    centerX = x;
    centerY = y;
}

std::shared_ptr<StructuringElement> StructuringElement::createSquare(int size) {
    return std::make_shared<StructuringElement>(SQUARE, size);
}

std::shared_ptr<StructuringElement> StructuringElement::createRhombus(int size) {
    return std::make_shared<StructuringElement>(RHOMBUS, size);
}

std::shared_ptr<StructuringElement> StructuringElement::createDisk(int radius) {
    return std::make_shared<StructuringElement>(DISK, radius);
}
