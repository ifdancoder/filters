//
// Created by ifdancoder on 20.10.2025.
//

#include "filters/BinaryDilationFilter.h"

BinaryDilationFilter::BinaryDilationFilter(std::shared_ptr<IImageSource> src,
                                           std::shared_ptr<StructuringElement> se)
    : MorphologicalFilter(std::move(src), std::move(se)) {
}

Image BinaryDilationFilter::applyFilter(Image &&in) const {
    Image out(in.getWidth(), in.getHeight());
    
    for (int y = 0; y < in.getHeight(); ++y) {
        for (int x = 0; x < in.getWidth(); ++x) {
            bool result = false;

            iterateStructuringElement(in, x, y, [&](int imgX, int imgY, int seX, int seY) {
                if (isPixelInBounds(in, imgX, imgY) && in.at(imgX, imgY).brightness() == 255) {
                    result = true;
                }
            });
            
            Pixel value = result ? Pixel::maxBrightness() : Pixel::minBrightness();
            out.at(x, y) = value;
        }
    }
    
    return out;
}
