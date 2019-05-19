#pragma once

struct Pixel
{
    unsigned char R = 0;
    unsigned char G = 0;
    unsigned char B = 0;

    Pixel();
    Pixel(unsigned char i);
    Pixel(unsigned char r, unsigned char g, unsigned char b);
    Pixel operator+(const Pixel &p) const noexcept;
    Pixel operator-(const Pixel &p) const noexcept;
    Pixel operator*(const float f) const noexcept;
    bool operator==(const Pixel &p) const noexcept;
    bool operator!=(const Pixel &p) const noexcept;
};