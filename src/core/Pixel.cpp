//
// Created by ifdancoder on 19.10.2025.
//

#include "core/Pixel.h"

#include <algorithm>
#include <iosfwd>
#include <random>

Pixel::Pixel(Pixel &pixel, bool isUseClamp) : r(pixel.getR()), g(pixel.getG()), b(pixel.getB()), is_use_clamp(isUseClamp)  {
    clamp();
}

Pixel::Pixel(uint8_t rInput, uint8_t gInput, uint8_t bInput, bool isUseClamp) : r(rInput), g(gInput), b(bInput),
                                                                                is_use_clamp(isUseClamp) {
    clamp();
}

Pixel Pixel::maxBrightness() {
    return {255, 255, 255};
}

Pixel Pixel::minBrightness() {
    return {0, 0, 0};
}

Pixel Pixel::fromBrightness(double brightness, bool isUseClamp) {
    brightness = std::clamp(brightness, 0.0, 255.0);

    return Pixel(brightness, brightness, brightness, isUseClamp);
}

uint8_t Pixel::getClampedValue(double value) {
    return std::clamp(value, 0.0, 255.0);
}

uint8_t Pixel::getClampedConditionalValue(double value, std::initializer_list<Pixel> processing) {
    bool clamp_condition = true;

    for (const auto pixel: processing) {
        if (!pixel.isClamping()) {
            clamp_condition = false;
            break;
        }
    }

    auto new_value = value;

    if (clamp_condition) {
        new_value = getClampedValue(value);
    }

    return new_value;
}

bool Pixel::isClamping() const {
    return is_use_clamp;
}

Pixel Pixel::getGrayscaled() {
    return fromBrightness(std::clamp(brightness(), 0.0, 255.0));
}

thread_local std::mt19937 generator(std::random_device{}());

uint8_t randomDouble(double min = 0, double max = 255) {
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}

Pixel Pixel::randPixel() {
    uint8_t r = randomDouble();
    uint8_t g = randomDouble();
    uint8_t b = randomDouble();
    return {r, g, b};
}

uint8_t Pixel::getR() const { return r; }
uint8_t Pixel::getG() const { return g; }
uint8_t Pixel::getB() const { return b; }

void Pixel::setR(uint8_t value) { r = value; }
void Pixel::setG(uint8_t value) { g = value; }
void Pixel::setB(uint8_t value) { b = value; }

Pixel Pixel::operator*(double scalar) const {
    return Pixel(
        getClampedConditionalValue(r * scalar, {*this}),
        getClampedConditionalValue(g * scalar, {*this}),
        getClampedConditionalValue(b * scalar, {*this})
    );
}

Pixel operator*(double scalar, const Pixel &pixel) {
    return pixel * scalar;
}

Pixel operator*(int scalar, const Pixel &pixel) {
    return pixel * scalar;
}

Pixel Pixel::operator/(double scalar) const {
    if (scalar == 0) {
        return {};
    }

    return Pixel(
        getClampedConditionalValue(r / scalar, {*this}),
        getClampedConditionalValue(g / scalar, {*this}),
        getClampedConditionalValue(b / scalar, {*this})
    );
}

Pixel Pixel::operator+(const Pixel &other) const {
    return Pixel(
        getClampedConditionalValue(r + other.r, {*this, other}),
        getClampedConditionalValue(g + other.g, {*this, other}),
        getClampedConditionalValue(b + other.b, {*this, other})
    );
}

Pixel Pixel::operator-(const Pixel &other) const {
    return Pixel(
        getClampedConditionalValue(r - other.r, {*this, other}),
        getClampedConditionalValue(g - other.g, {*this, other}),
        getClampedConditionalValue(b - other.b, {*this, other})
    );
}

Pixel &Pixel::operator*=(double scalar) {
    *this = *this * scalar;
    return *this;
}

Pixel &Pixel::operator/=(double scalar) {
    *this = *this / scalar;
    return *this;
}

Pixel &Pixel::operator+=(const Pixel &other) {
    *this = *this + other;
    return *this;
}

Pixel &Pixel::operator-=(const Pixel &other) {
    *this = *this - other;
    return *this;
}

bool Pixel::operator==(const Pixel &other) const {
    return r == other.r && g == other.g && b == other.b;
}

bool Pixel::operator!=(const Pixel &other) const {
    return !(*this == other);
}

double Pixel::brightness() const {
    return (r + g + b) / 3.0;
}

void Pixel::clamp() {
    r = getClampedConditionalValue(r, {*this});
    g = getClampedConditionalValue(g, {*this});
    b = getClampedConditionalValue(b, {*this});
}

Pixel Pixel::invert() const {
    return Pixel(255 - r, 255 - g, 255 - b);
}

bool Pixel::operator<(const Pixel &other) const {
    return this->brightness() < other.brightness();
}

bool Pixel::operator<=(const Pixel &other) const {
    return this->brightness() <= other.brightness();
}

bool Pixel::operator>(const Pixel &other) const {
    return this->brightness() > other.brightness();
}

bool Pixel::operator>=(const Pixel &other) const {
    return this->brightness() >= other.brightness();
}

bool Pixel::operator<(double value) const {
    return this->brightness() < value;
}

bool Pixel::operator<=(double value) const {
    return this->brightness() <= value;
}

bool Pixel::operator>(double value) const {
    return this->brightness() > value;
}

bool Pixel::operator>=(double value) const {
    return this->brightness() >= value;
}

bool operator<(double value, const Pixel &pixel) {
    return value < pixel.brightness();
}

bool operator<=(double value, const Pixel &pixel) {
    return value <= pixel.brightness();
}

bool operator>(double value, const Pixel &pixel) {
    return value > pixel.brightness();
}

bool operator>=(double value, const Pixel &pixel) {
    return value >= pixel.brightness();
}

std::ostream &operator<<(std::ostream &os, const Pixel &pixel) {
    os << "Pixel(R:" << static_cast<int>(pixel.getR()) << "\t"
            << ", G:" << static_cast<int>(pixel.getG()) << "\t"
            << ", B:" << static_cast<int>(pixel.getB()) << "\t"
            << ", isClamping:" << static_cast<int>(pixel.isClamping())
            << ")";
    return os;
}
