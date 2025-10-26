//
// Created by ifdancoder on 20.10.2025.
//

#include "filters/GrayscaleErosionFilter.h"
#include <algorithm>

GrayscaleErosionFilter::GrayscaleErosionFilter(std::shared_ptr<IImageSource> src,
                                               std::shared_ptr<StructuringElement> se)
    : MorphologicalFilter(std::move(src), std::move(se)) {
}

Image GrayscaleErosionFilter::applyFilter(Image &&in) const {
    Image out(in.getWidth(), in.getHeight());

    for (int y = 0; y < in.getHeight(); ++y) {
        for (int x = 0; x < in.getWidth(); ++x) {
            double minValue = 255;

            iterateStructuringElement(in, x, y, [&](int imgX, int imgY, int seX, int seY) {
                if (isPixelInBounds(in, imgX, imgY)) {
                    double pixelValue = in.at(imgX, imgY).brightness();
                    minValue = std::min(minValue, pixelValue);
                }
            });

            auto newPixelValue = static_cast<uint8_t>(minValue);

            out.at(x, y) = Pixel(newPixelValue, newPixelValue, newPixelValue);
        }
    }

    return out;
}
