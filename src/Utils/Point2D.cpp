#include "Point2D.h"

#include <utility>

Point2D::Point2D()
    : X(0.f), Y(0.f)
{
}

Point2D::Point2D(float x, float y)
    : X(x), Y(y)
{
}

Point2D Point2D::operator+(const Point2D &p)
{
    return std::move(
        Point2D(
            this->X + p.X,
            this->Y + p.Y));
}

Point2D Point2D::operator-(const Point2D &p)
{
    return std::move(
        Point2D(
            this->X - p.X,
            this->Y - p.Y));
}

void Point2D::operator+=(const Point2D &p) noexcept
{
    this->X += p.X;
    this->Y += p.Y;
}

void Point2D::operator*=(const float n) noexcept
{
    this->X *= n;
    this->Y *= n;
}