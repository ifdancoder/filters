//
// Created by ifdancoder on 13.10.2025.
//

#include "filters/BaseImage.h"

BaseImage::BaseImage(Image i) : img(std::move(i)) {
}

[[nodiscard]] Image BaseImage::getImage() const {
    return img;
}
