//
// Created by ifdancoder on 20.10.2025.
//

#ifndef FILTERS_STRUCTURINGELEMENT_H
#define FILTERS_STRUCTURINGELEMENT_H

#include <vector>
#include <memory>

#include "Image.h"

class StructuringElement: public Image {
public:
    enum Type {
        SQUARE,
        RHOMBUS,
        DISK
    };

private:
    int centerX, centerY;

public:
    StructuringElement(int w, int h, int centerXInput, int centerYInput);
    StructuringElement(Type type, int size);

    [[nodiscard]] int getCenterX() const { return centerX; }
    [[nodiscard]] int getCenterY() const { return centerY; }

    void setCenter(int x, int y);
    
    static std::shared_ptr<StructuringElement> createSquare(int size);
    static std::shared_ptr<StructuringElement> createRhombus(int size);
    static std::shared_ptr<StructuringElement> createDisk(int radius);
};

#endif //FILTERS_STRUCTURINGELEMENT_H
