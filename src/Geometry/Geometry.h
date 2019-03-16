#pragma once

#include "../ClassicDemoTemplate/ClassicDemoTemplate.h"
#include "../Utils/Pixel.h"
#include "Object3D.h"

struct IWindowManager;

class GeometryDemo : public ClassicDemoTemplate
{
  public:
    GeometryDemo(){};
    virtual ~GeometryDemo(){};

  private:

    virtual bool Init() override;
    virtual bool Update(float deltaTime) override;
    virtual bool Destroy() override;

    void RegisterInput();
    void UpdateInput(float deltaTime);

    void InitialiseTransformations();
    void CreateCube();
    void CreatePyramid();
    void CreateStar();
    void ApplyObjectTransformations();
    void UndoObjectTransformations();
    void ApplyPerspective();
    void RenderInstructions();
    void Generate2DProjection(Object3D &object);
    void GeneratePerspectiveProjection(Object3D &object);
    void TranslateObject(Object3D &object, Point3D offset);
    void ScaleObject(Object3D &object, Point3D scale);
    void Rotate3DObjectAroundXAxis(Object3D &object, float angle);
    void Rotate3DObjectAroundYAxis(Object3D &object, float angle);
    void Rotate3DObjectAroundZAxis(Object3D &object, float angle);
    void RenderObject(Object3D object, const Pixel &colour);
    void EraseObject(Object3D object);

    Pixel *pixels;
    int width, height;
    IWindowManager *windowManager;

    std::vector<Object3D> objects;
    std::vector<Point3D> transformations;
    std::vector<float> transformMultiplier;
    std::vector<const char*> transformText;
    unsigned int objectsIndex, transformationsIndex;
    bool perspective;
};