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
    Image img;

public:
    explicit BaseImage(Image i);

    [[nodiscard]] Image getImage() const override;
};


#endif //FILTERS_BASEIMAGE_H
