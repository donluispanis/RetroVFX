#pragma once

struct Point2D
{
    float X;
    float Y;

    Point2D();
    Point2D(float x, float y);
    Point2D operator+(const Point2D &p);
    Point2D operator-(const Point2D &p);
    void operator+=(const Point2D &p) noexcept;
    void operator*=(const float) noexcept;
};