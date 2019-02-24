#pragma once

struct Point3D
{
    float X;
    float Y;
    float Z;
    
    Point3D();
    Point3D(float x, float y, float z);
    void operator+=(const Point3D &p) noexcept;
    void operator*=(const Point3D &p) noexcept;
};