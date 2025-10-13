//
// Created by ifdancoder on 14.10.2025.
//

#include "filters/ConvolutionFilter.h"

ConvolutionFilter::ConvolutionFilter(std::shared_ptr<IImageSource> src,
                      const std::vector<std::vector<double> > &kern,
                      int pad)
        : FilterDecorator(std::move(src)), kernel(kern), padMode(pad) {
    kH = (int) kernel.size();
    kW = kH ? (int) kernel[0].size() : 0;
}

[[nodiscard]] uint8_t ConvolutionFilter::sample(const Image &img, int x, int y) const {
    if (x < 0 || x >= img.getWidth() || y < 0 || y >= img.getHeight()) {
        if (padMode == 0) return 0;
        x = std::clamp(x, 0, img.getWidth() - 1);
        y = std::clamp(y, 0, img.getHeight() - 1);
        return img.at(x, y);
    }
    return img.at(x, y);
}

Image ConvolutionFilter::applyFilter(Image &&in) const {
    Image out(in.getWidth(), in.getHeight());
    int kcx = kW / 2;
    int kcy = kH / 2;

    for (int y = 0; y < in.getHeight(); ++y) {
        for (int x = 0; x < in.getWidth(); ++x) {
            double sum = 0.0;
            for (int ky = 0; ky < kH; ++ky) {
                for (int kx = 0; kx < kW; ++kx) {
                    int ix = x + (kx - kcx);
                    int iy = y + (ky - kcy);
                    uint8_t s = sample(in, ix, iy);
                    sum += kernel[ky][kx] * static_cast<double>(s);
                }
            }
            int v = int(std::round(sum));
            v = std::clamp(v, 0, 255);
            out.at(x, y) = static_cast<uint8_t>(v);
        }
    }
    return out;
}