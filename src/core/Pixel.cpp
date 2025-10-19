//
// Created by ifdancoder on 19.10.2025.
//

#include "core/Pixel.h"

#include <algorithm>
#include <iosfwd>
#include <random>

Pixel::Pixel(uint8_t rInput, uint8_t gInput, uint8_t bInput) : r(rInput), g(gInput), b(bInput) {
}

Pixel Pixel::maxBrightness() {
    return Pixel(255, 255, 255);
}

Pixel Pixel::minBrightness() {
    return Pixel(0, 0, 0);
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
    return Pixel(r, g, b);
}

uint8_t Pixel::getR() const { return r; }
uint8_t Pixel::getG() const { return g; }
uint8_t Pixel::getB() const { return b; }

void Pixel::setR(uint8_t value) { r = value; }
void Pixel::setG(uint8_t value) { g = value; }
void Pixel::setB(uint8_t value) { b = value; }

Pixel Pixel::operator*(double scalar) const {
    return Pixel(
        std::clamp(r * scalar, 0.0, 255.0),
        std::clamp(g * scalar, 0.0, 255.0),
        std::clamp(b * scalar, 0.0, 255.0)
    );
}

Pixel operator*(double scalar, const Pixel &pixel) {
    return pixel * scalar;
}

Pixel operator*(int scalar, const Pixel &pixel) {
    return pixel * scalar;
}

Pixel Pixel::operator/(double scalar) const {
    if (scalar == 0) return Pixel();
    return Pixel(
        static_cast<uint8_t>(std::clamp(r / scalar, 0.0, 255.0)),
        static_cast<uint8_t>(std::clamp(g / scalar, 0.0, 255.0)),
        static_cast<uint8_t>(std::clamp(b / scalar, 0.0, 255.0))
    );
}

Pixel Pixel::operator+(const Pixel &other) const {
    return Pixel(
        static_cast<uint8_t>(std::clamp(r + other.r, 0, 255)),
        static_cast<uint8_t>(std::clamp(g + other.g, 0, 255)),
        static_cast<uint8_t>(std::clamp(b + other.b, 0, 255))
    );
}

Pixel Pixel::operator-(const Pixel &other) const {
    return Pixel(
        static_cast<uint8_t>(std::clamp(r - other.r, 0, 255)),
        static_cast<uint8_t>(std::clamp(g - other.g, 0, 255)),
        static_cast<uint8_t>(std::clamp(b - other.b, 0, 255))
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
    return (r + g + b) / 3.0f;
}

Pixel Pixel::invert() const {
    return Pixel(255 - r, 255 - g, 255 - b);
}

bool Pixel::operator<(const Pixel& other) const {
    return this->brightness() < other.brightness();
}

bool Pixel::operator<=(const Pixel& other) const {
    return this->brightness() <= other.brightness();
}

bool Pixel::operator>(const Pixel& other) const {
    return this->brightness() > other.brightness();
}

bool Pixel::operator>=(const Pixel& other) const {
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

bool operator<(double value, const Pixel& pixel) {
    return value < pixel.brightness();
}

bool operator<=(double value, const Pixel& pixel) {
    return value <= pixel.brightness();
}

bool operator>(double value, const Pixel& pixel) {
    return value > pixel.brightness();
}

bool operator>=(double value, const Pixel& pixel) {
    return value >= pixel.brightness();
}

std::ostream& operator<<(std::ostream& os, const Pixel& pixel) {
    os << "Pixel(R:" << static_cast<int>(pixel.getR()) << "\t"
       << ", G:" << static_cast<int>(pixel.getG()) << "\t"
       << ", B:" << static_cast<int>(pixel.getB())
       << ")";
    return os;
}