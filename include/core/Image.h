//
// Created by ifdancoder on 13.10.2025.
//

#ifndef FILTERS_IMAGE_H
#define FILTERS_IMAGE_H

#include <cstdint>
#include <vector>

class Image {
protected:
    int w, h;
    std::vector<uint8_t> data;

public:
    Image(int width = 0, int height = 0);

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

    uint8_t &at(int i);

    uint8_t &at(int x, int y);

    [[nodiscard]] const uint8_t &at(int i) const;

    [[nodiscard]] const uint8_t &at(int x, int y) const;
};


#endif //FILTERS_IMAGE_H
