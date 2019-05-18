#pragma once

struct Point3D
{
    float X;
    float Y;
    float Z;
    
    Point3D();
    Point3D(float x, float y, float z);
    Point3D operator-() noexcept;
    Point3D operator+(const Point3D &p) noexcept;
    void operator+=(const Point3D &p) noexcept;
    void operator*=(const Point3D &p) noexcept;
    Point3D operator*(const float f) noexcept;
    Point3D inverse();
};