//
// Created by ifdancoder on 20.10.2025.
//

#include "filters/BinaryDilationFilter.h"

BinaryDilationFilter::BinaryDilationFilter(std::shared_ptr<IImageSource> src,
                                           std::shared_ptr<StructuringElement> se)
    : MorphologicalFilter(std::move(src), std::move(se)) {
}

std::shared_ptr<Image> BinaryDilationFilter::applyFilter(std::shared_ptr<Image> in) const {

    std::shared_ptr<Image> processing_image = in;

    auto structuring_element = dynamic_pointer_cast<StructuringElement>(processing_image);

    std::shared_ptr<StructuringElement> tmp_element;

    if (structuring_element != nullptr) {
        tmp_element = expandStructuringElement(std::shared_ptr<StructuringElement>(structuring_element), structuringElement);
        processing_image = tmp_element;
    }
    std::shared_ptr<Image> processing_image_shared_ptr = std::shared_ptr<Image>(processing_image);

    std::shared_ptr<Image> out;

    if (structuring_element != nullptr) {
        out = std::make_shared<StructuringElement>(tmp_element->getWidth(), tmp_element->getHeight(), tmp_element->getCenterX(), tmp_element->getCenterY());
    } else {
        out = std::make_shared<Image>(processing_image_shared_ptr->getWidth(), processing_image_shared_ptr->getHeight());
    }

    for (int y = 0; y < processing_image_shared_ptr->getHeight(); ++y) {
        for (int x = 0; x < processing_image_shared_ptr->getWidth(); ++x) {
            bool result = false;

            iterateStructuringElement(processing_image_shared_ptr, x, y, [&](int imgX, int imgY, int seX, int seY) {
                if (isPixelInBounds(processing_image_shared_ptr, imgX, imgY) && processing_image_shared_ptr->at(imgX, imgY) == Pixel::maxBrightness()) {
                    result = true;
                }
            });

            out->at(x, y) = result ? Pixel::maxBrightness() : Pixel::minBrightness();
        }
    }

    return out;
}