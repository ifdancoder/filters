//
// Created by ifdancoder on 13.10.2025.
//

#include "filters/BaseImage.h"

BaseImage::BaseImage(const std::shared_ptr<Image>& i) : img(i) {
}

[[nodiscard]] std::shared_ptr<Image> BaseImage::getImage() const {
    return img;
}
