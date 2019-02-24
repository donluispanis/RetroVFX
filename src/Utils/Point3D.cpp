#include "Point3D.h"

Point3D::Point3D()
    : X(0.f), Y(0.f), Z(0.f)
{
}

Point3D::Point3D(float x, float y, float z)
    : X(x), Y(y), Z(z)
{
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