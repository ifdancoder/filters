//
// Created by ifdancoder on 20.10.2025.
//

#ifndef FILTERS_STRUCTURINGELEMENT_H
#define FILTERS_STRUCTURINGELEMENT_H

#include <vector>
#include <memory>

class StructuringElement {
public:
    enum Type {
        SQUARE,
        CROSS,
        DISK
    };

private:
    std::vector<std::vector<bool>> kernel;
    int width, height;
    int centerX, centerY;

public:
    StructuringElement(Type type, int size);
    
    [[nodiscard]] int getWidth() const { return width; }
    [[nodiscard]] int getHeight() const { return height; }
    [[nodiscard]] int getCenterX() const { return centerX; }
    [[nodiscard]] int getCenterY() const { return centerY; }
    
    [[nodiscard]] bool at(int x, int y) const;
    
    static std::shared_ptr<StructuringElement> createSquare(int size);
    static std::shared_ptr<StructuringElement> createCross(int size);
    static std::shared_ptr<StructuringElement> createDisk(int radius);
};

#endif //FILTERS_STRUCTURINGELEMENT_H
