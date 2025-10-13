//
// Created by ifdancoder on 14.10.2025.
//

#include <iostream>

#include "core/Image.h"

void printImageASCII(const Image& img) {
    static const char* ramps = " .:-=+*#%@";
    int levels = 10;
    for (int y = 0; y < img.getHeight(); ++y) {
        for (int x = 0; x < img.getWidth(); ++x) {
            int v = img.at(x, y);
            int idx = v * (levels - 1) / 255;
            std::cout << ramps[idx];
        }
        std::cout << '\n';
    }
}
