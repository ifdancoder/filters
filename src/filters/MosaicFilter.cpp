//
// Created by ifdancoder on 16.11.2025.
//

#include "filters/MosaicFilter.h"
#include "core/Pixel.h"

MosaicFilter::MosaicFilter(std::shared_ptr<IImageSource> src, int size)
    : FilterDecorator(std::move(src)), blockSize(size) {
}

std::shared_ptr<Image> MosaicFilter::applyFilter(std::shared_ptr<Image> in) const {
    auto out = std::make_shared<Image>(in->getWidth(), in->getHeight());

    for (int blockY = 0; blockY < in->getHeight(); blockY += blockSize) {
        for (int blockX = 0; blockX < in->getWidth(); blockX += blockSize) {
            int endX = std::min(blockX + blockSize, in->getWidth());
            int endY = std::min(blockY + blockSize, in->getHeight());

            int sumR = 0, sumG = 0, sumB = 0;
            int count = 0;

            for (int y = blockY; y < endY; ++y) {
                for (int x = blockX; x < endX; ++x) {
                    const auto& pixel = in->at(x, y);
                    sumR += pixel.getR();
                    sumG += pixel.getG();
                    sumB += pixel.getB();
                    ++count;
                }
            }

            Pixel avgPixel(sumR / count, sumG / count, sumB / count);

            for (int y = blockY; y < endY; ++y) {
                for (int x = blockX; x < endX; ++x) {
                    out->at(x, y) = avgPixel;
                }
            }
        }
    }

    return out;
}

