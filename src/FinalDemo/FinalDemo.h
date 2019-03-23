#pragma once

#include "../ClassicDemoTemplate/ClassicDemoTemplate.h"
#include "../Utils/Object3D.h"

struct Pixel;
struct IWindowManager;

class FinalDemo : public ClassicDemoTemplate
{
  public:
    FinalDemo(){};
    virtual ~FinalDemo(){};

  private:
    virtual bool Init() override;
    virtual bool Update(float deltaTime) override;
    virtual bool Destroy() override;

    void GenerateGrid(int vertexPerWidth, int vertexPerDepth, float vertexDistance);

    void GeneratePerspectiveProjection(Object3D &object);
    void RenderObject(Object3D object);
    void EraseObject(Object3D object);
    void TranslateObject(Object3D &object, Point3D offset);
    void ApplyWaveTransformation(Object3D &object, float amplitude, float wavelength, float deltaTime);
    void ApplyObjectTransformations(float deltaTime);
    void UndoObjectTransformations(float deltaTime);

    Pixel *pixels;
    int width, height;
    IWindowManager* windowManager;

    Object3D grid;
    const int vertexPerWidth = 70;
    const int vertexPerDepth = 30;
    const int vertexDistance = 100;
    float phase = 0;
};