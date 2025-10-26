//
// Created by ifdancoder on 20.10.2025.
//

#include "filters/BinaryErosionFilter.h"
#include <algorithm>

BinaryErosionFilter::BinaryErosionFilter(std::shared_ptr<IImageSource> src,
                                         std::shared_ptr<StructuringElement> se)
    : MorphologicalFilter(std::move(src), std::move(se)) {
}

Image BinaryErosionFilter::applyFilter(Image &&in) const {
    Image out(in.getWidth(), in.getHeight());
    
    for (int y = 0; y < in.getHeight(); ++y) {
        for (int x = 0; x < in.getWidth(); ++x) {
            bool result = true;

            iterateStructuringElement(in, x, y, [&](int imgX, int imgY, int seX, int seY) {
                if (!isPixelInBounds(in, imgX, imgY) || in.at(imgX, imgY).brightness() == 0) {
                    result = false;
                }
            });
            
            Pixel value = result ? Pixel::maxBrightness() : Pixel::minBrightness();
            out.at(x, y) = value;
        }
    }
    
    return out;
}
