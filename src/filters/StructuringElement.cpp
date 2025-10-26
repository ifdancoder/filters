//
// Created by ifdancoder on 20.10.2025.
//

#include "filters/StructuringElement.h"
#include <cmath>

StructuringElement::StructuringElement(Type type, int size) {
    switch (type) {
        case SQUARE:
            width = height = size;
            centerX = centerY = size / 2;
            kernel.resize(height, std::vector<bool>(width, true));
            break;
            
        case CROSS:
            width = height = size;
            centerX = centerY = size / 2;
            kernel.resize(height, std::vector<bool>(width, false));
            for (int x = 0; x < width; ++x) {
                kernel[centerY][x] = true;
            }
            for (int y = 0; y < height; ++y) {
                kernel[y][centerX] = true;
            }
            break;
            
        case DISK:
            width = height = 2 * size + 1;
            centerX = centerY = size;
            kernel.resize(height, std::vector<bool>(width, false));
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    double distance = std::sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));
                    kernel[y][x] = (distance <= size);
                }
            }
            break;
    }
}

bool StructuringElement::at(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return false;
    }
    return kernel[y][x];
}

std::shared_ptr<StructuringElement> StructuringElement::createSquare(int size) {
    return std::make_shared<StructuringElement>(SQUARE, size);
}

std::shared_ptr<StructuringElement> StructuringElement::createCross(int size) {
    return std::make_shared<StructuringElement>(CROSS, size);
}

std::shared_ptr<StructuringElement> StructuringElement::createDisk(int radius) {
    return std::make_shared<StructuringElement>(DISK, radius);
}
