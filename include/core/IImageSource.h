//
// Created by ifdancoder on 13.10.2025.
//

#ifndef FILTERS_IIMAGESOURCE_H
#define FILTERS_IIMAGESOURCE_H

#include "Image.h"

class IImageSource {
public:
    virtual ~IImageSource() = default;

    [[nodiscard]] virtual Image getImage() const = 0;
};


#endif //FILTERS_IIMAGESOURCE_H
