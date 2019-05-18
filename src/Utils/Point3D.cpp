#include "Point3D.h"
#include <utility>

Point3D::Point3D()
    : X(0.f), Y(0.f), Z(0.f)
{
}

Point3D::Point3D(float x, float y, float z)
    : X(x), Y(y), Z(z)
{
}

Point3D Point3D::operator-() noexcept
{
    return std::move(
        Point3D(
            -this->X,
            -this->Y,
            -this->Z));
}

Point3D Point3D::operator+(const Point3D &p) noexcept
{
    return std::move(
        Point3D(
            this->X + p.X,
            this->Y + p.Y,
            this->Z + p.Z));
}

void Point3D::operator+=(const Point3D &p) noexcept
{
    this->X += p.X;
    this->Y += p.Y;
    this->Z += p.Z;
}

void Point3D::operator*=(const Point3D &p) noexcept
{
    this->X *= p.X;
    this->Y *= p.Y;
    this->Z *= p.Z;
}

Point3D Point3D::operator*(const float f) noexcept
{
    return std::move(
        Point3D(
            this->X * f,
            this->Y * f,
            this->Z * f));
}

Point3D Point3D::inverse()
{
    return std::move(
        Point3D(
            1 / this->X,
            1 / this->Y,
            1 / this->Z));
}