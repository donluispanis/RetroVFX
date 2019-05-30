#pragma once

#include "../../Utils/Object3D.h"

struct FinalDemo;

class Imp_Geometry
{
public:
    void InitGeometry(int width, int height, FinalDemo* engine);
    void UpdateGeometry(float deltaTime, float accumulatedTime, float startTime);
    void CloseGeometry();

private:
    void GenerateGrid(int vertexPerWidth, int vertexPerDepth, float vertexDistance);
    void GenerateSphere(int gridSize, float radius);
    void GeneratePerspectiveProjection(Object3D &object);
    void RenderObject(Object3D object);
    void EraseObject(Object3D object);
    void TranslateObject(Object3D &object, Point3D offset);
    void ApplyWaveTransformation(Object3D &object, float amplitude, float wavelength, float deltaTime);
    void ApplyObjectTransformations(float deltaTime);
    void UndoObjectTransformations(float deltaTime);
    Point3D GetPointInSphereFromPlane(const int gridX, const int gridY, const int gridSize, const float radius);

    Object3D grid;
    Object3D sphere;
    const int vertexPerWidth = 30;
    const int vertexPerDepth = 30;
    const int vertexDistance = 250;
    float phase = 0.f;
    float phaseVelocity = 1.f;

    float waveAmplitude = 0.f;
    float waveAmplitudeVelocity = 0.f;
    float colourOpacityIn = 0.f;
    float colourOpacityOut = 1.f;
    Point3D position;

    bool renderLines = true;

    Point3D colourDeformator = Point3D(1.f, 1.f, 1.f);

    int width, height;
    FinalDemo* engine;
};