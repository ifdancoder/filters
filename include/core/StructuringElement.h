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
    explicit StructuringElement(Type type);

    [[nodiscard]] int getCenterX() const { return centerX; }
    [[nodiscard]] int getCenterY() const { return centerY; }

    void setCenter(int x, int y);
    
    static std::shared_ptr<StructuringElement> createSquare();
    static std::shared_ptr<StructuringElement> createRhombus();
    static std::shared_ptr<StructuringElement> createDisk();

    std::shared_ptr<StructuringElement> static dilated(Type type, std::shared_ptr<StructuringElement> se, int n);
    std::shared_ptr<StructuringElement> static dilated(Type type, int n);
    std::shared_ptr<StructuringElement> static dilated(Type type, std::shared_ptr<StructuringElement> se);
};

#endif //FILTERS_STRUCTURINGELEMENT_H
