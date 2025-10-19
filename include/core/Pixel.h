//
// Created by ifdancoder on 19.10.2025.
//

#ifndef FILTERS_PIXEL_H
#define FILTERS_PIXEL_H
#include <cstdint>
#include <iostream>


class Pixel {
protected:
    uint8_t r, g, b;

public:
    explicit Pixel(uint8_t rInput = 0, uint8_t gInput = 0, uint8_t bInput = 0);

    static Pixel maxBrightness();
    static Pixel minBrightness();
    static Pixel randPixel();

    [[nodiscard]] uint8_t getR() const;
    [[nodiscard]] uint8_t getG() const;
    [[nodiscard]] uint8_t getB() const;

    void setR(uint8_t value);
    void setG(uint8_t value);
    void setB(uint8_t value);

    friend Pixel operator*(double scalar, const Pixel& pixel);

    Pixel operator*(double scalar) const;

    Pixel operator/(double scalar) const;

    Pixel operator+(const Pixel& other) const;

    Pixel operator-(const Pixel& other) const;

    Pixel& operator*=(double scalar);

    Pixel& operator/=(double scalar);

    Pixel& operator+=(const Pixel& other);

    Pixel& operator-=(const Pixel& other);

    bool operator==(const Pixel& other) const;
    bool operator!=(const Pixel& other) const;

    bool operator<(const Pixel& other) const;

    bool operator<=(const Pixel& other) const;

    bool operator>(const Pixel& other) const;

    bool operator>=(const Pixel& other) const;

    bool operator<(double value) const;

    bool operator<=(double value) const;

    bool operator>(double value) const;

    bool operator>=(double value) const;

    friend bool operator<(double value, const Pixel& pixel);

    friend bool operator<=(double value, const Pixel& pixel);

    friend bool operator>(double value, const Pixel& pixel);

    friend bool operator>=(double value, const Pixel& pixel);

    friend std::ostream& operator<<(std::ostream& os, const Pixel& pixel);

    [[nodiscard]] double brightness() const;

    [[nodiscard]] Pixel invert() const;
};


#endif //FILTERS_PIXEL_H
