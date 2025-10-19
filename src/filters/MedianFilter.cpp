//
// Created by ifdancoder on 14.10.2025.
//

#include "filters/MedianFilter.h"
#include "core/Pixel.h"
#include <algorithm>

MedianFilter::MedianFilter(std::shared_ptr<IImageSource> src, int r)
    : FilterDecorator(std::move(src)), radius(r) {
}

Image MedianFilter::applyFilter(Image &&in) const {
    int ws = 2 * radius + 1;
    Image out(in.getWidth(), in.getHeight());
    std::vector<Pixel> window;
    window.reserve(ws * ws);

    for (int y = 0; y < in.getHeight(); ++y) {
        for (int x = 0; x < in.getWidth(); ++x) {
            window.clear();
            for (int dy = -radius; dy <= radius; ++dy) {
                for (int dx = -radius; dx <= radius; ++dx) {
                    int ix = std::clamp(x + dx, 0, in.getWidth() - 1);
                    int iy = std::clamp(y + dy, 0, in.getHeight() - 1);
                    window.push_back(in.at(ix, iy));
                }
            }
            std::nth_element(window.begin(), window.begin() + window.size() / 2, window.end());
            out.at(x, y) = window[window.size() / 2];
        }
    }
    return out;
}
