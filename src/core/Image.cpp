//
// Created by ifdancoder on 13.10.2025.
//

#include "core/Image.h"

Image::Image(int width, int height) : w(width), h(height), data(w * h, 0) {
}

uint8_t& Image::at(int i) {
    return data[i];
}

uint8_t& Image::at(int x, int y) {
    return at(y * w + x);
}

const uint8_t &Image::at(int i) const {
    return data[i];
}

const uint8_t& Image::at(int x, int y) const {
    return at(y * w + x);
}

int Image::getWidth() const {
    return w;
}

int Image::getHeight() const {
    return h;
}
