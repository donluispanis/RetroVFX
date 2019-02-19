#pragma once

#include <vector>
#include "../ClassicDemoTemplate/ClassicDemoTemplate.h"
#include "../Utils/Pixel.h"

struct IWindowManager;

class GeometryDemo : public ClassicDemoTemplate
{
  public:
    GeometryDemo(){};
    virtual ~GeometryDemo(){};

  private:
    struct Point2D
    {
        float X;
        float Y;
    };
    struct Point3D
    {
        float X;
        float Y;
        float Z;
    };
    struct Object3D
    {
        std::vector<Point3D> points;
        std::vector<Point2D> projectedPoints;
        std::vector<Point2D> indexes;
        Pixel colour;
    };

    virtual bool Init() override;
    virtual bool Update(float deltaTime) override;
    virtual bool Destroy() override;

    void RenderObject(Object3D object);

    Pixel *pixels;
    int width, height;
    IWindowManager *windowManager;

    Object3D object;
};