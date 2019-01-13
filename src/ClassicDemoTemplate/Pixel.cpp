#include <utility>
#include "ClassicDemoTemplate.h"
#include "Pixel.h"

ClassicDemoTemplate::Pixel::Pixel() 
    : R(0), G(0), B(0){};

ClassicDemoTemplate::Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b) 
    : R(r), G(g), B(b){};

ClassicDemoTemplate::Pixel ClassicDemoTemplate::Pixel::operator+(const Pixel &p) const
{
    return std::move(
        Pixel(
            (p.R + this->R > 255) ? 255 : p.R + this->R,
            (p.G + this->G > 255) ? 255 : p.G + this->G,
            (p.B + this->B > 255) ? 255 : p.B + this->B));
}

ClassicDemoTemplate::Pixel ClassicDemoTemplate::Pixel::operator-(const Pixel &p) const
{
    return std::move(
        Pixel(
            (p.R - this->R < 0) ? 0 : p.R + this->R,
            (p.G - this->G < 0) ? 0 : p.G + this->G,
            (p.B - this->B < 0) ? 0 : p.B + this->B));
}

ClassicDemoTemplate::Pixel ClassicDemoTemplate::Pixel::operator*(const float f) const
{
    return std::move(Pixel(this->R * f, this->G * f, this->B * f));
}

void ClassicDemoTemplate::Pixel::Clear()
{
    R = 0;
    G = 0;
    B = 0;
}