//
// Created by ifdancoder on 13.10.2025.
//

#ifndef FILTERS_BASEIMAGE_H
#define FILTERS_BASEIMAGE_H

#include <utility>

#include "core/Image.h"
#include "core/IImageSource.h"

class BaseImage : public IImageSource {
protected:
    std::shared_ptr<Image> img;

public:
    explicit BaseImage(const std::shared_ptr<Image>& i);

    [[nodiscard]] std::shared_ptr<Image> getImage() const override;
};


#endif //FILTERS_BASEIMAGE_H
