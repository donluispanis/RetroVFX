#include <utility>
#include "Pixel.h"

Pixel::Pixel() 
    : R(0), G(0), B(0){};

Pixel::Pixel(unsigned char i) 
    : R(i), G(i), B(i){};

Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b) 
    : R(r), G(g), B(b){};

Pixel Pixel::operator+(const Pixel &p) const noexcept
{
    return Pixel(
            (p.R + this->R > 255) ? 255 : p.R + this->R,
            (p.G + this->G > 255) ? 255 : p.G + this->G,
            (p.B + this->B > 255) ? 255 : p.B + this->B);
}

Pixel Pixel::operator-(const Pixel &p) const noexcept
{
    return Pixel(
            (p.R - this->R < 0) ? 0 : p.R + this->R,
            (p.G - this->G < 0) ? 0 : p.G + this->G,
            (p.B - this->B < 0) ? 0 : p.B + this->B);
}

Pixel Pixel::operator*(const float f) const noexcept
{
    return Pixel(this->R * f, this->G * f, this->B * f);
}

bool Pixel::operator==(const Pixel &p) const noexcept
{
    return (this->R == p.R) && (this->G == p.G) && (this->B == p.B);
}

bool Pixel::operator!=(const Pixel &p) const noexcept
{
    return (this->R != p.R) || (this->G != p.G) || (this->B != p.B);
}