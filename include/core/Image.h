//
// Created by ifdancoder on 13.10.2025.
//

#ifndef FILTERS_IMAGE_H
#define FILTERS_IMAGE_H

#include <cstdint>
#include <vector>
#include <opencv2/core/mat.hpp>

#include "Pixel.h"

class Image {
protected:
    int w, h;
    std::vector<Pixel> data;

public:
    explicit Image(int width = 0, int height = 0);

    explicit Image(const cv::Mat& image);

    [[nodiscard]] cv::Mat toMat() const;

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

    Pixel &at(int i);

    Pixel &at(int x, int y);

    [[nodiscard]] const Pixel &at(int i) const;

    [[nodiscard]] const Pixel &at(int x, int y) const;
};


#endif //FILTERS_IMAGE_H
