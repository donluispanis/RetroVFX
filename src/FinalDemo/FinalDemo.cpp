#include "FinalDemo.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"
#include "../Utils/Fast.h"
#include <climits>
#include <cmath>

bool FinalDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    GenerateGrid(vertexPerWidth, vertexPerDepth, vertexDistance);
    GeneratePerspectiveProjection(grid);

    return true;
}

bool FinalDemo::Destroy()
{
    return true;
}

bool FinalDemo::Update(float deltaTime)
{
    EraseObject(grid);
    ApplyObjectTransformations(deltaTime);
    GeneratePerspectiveProjection(grid);
    RenderObject(grid);
    UndoObjectTransformations(deltaTime);
    return true;
}

static float phasee = 0;
void FinalDemo::ApplyObjectTransformations(float deltaTime)
{
    phasee+=5;
    TranslateObject(grid, Point3D(width/2 - (vertexPerWidth * vertexDistance) / 2, height * 0.75f,-550));
    ApplyWaveTransformation(grid, 50, 0.05, deltaTime, phasee);
}

void FinalDemo::UndoObjectTransformations(float deltaTime)
{
    ApplyWaveTransformation(grid, -50, 0.05, deltaTime, phasee);
    TranslateObject(grid, Point3D(-width/2 + (vertexPerWidth * vertexDistance) / 2, -height * 0.75f,+550));
}

void FinalDemo::GenerateGrid(int vertexPerWidth, int vertexPerDepth, float vertexDistance)
{
    const int size = vertexPerWidth * vertexPerDepth;

    //Generate vertex for the grid
    for (float j = 0; j < vertexPerDepth; j++)
    {
        for (float i = 0; i < vertexPerWidth; i++)
        {
            grid.points.emplace_back(i * vertexDistance, 0, j * vertexDistance);
        }
    }

    //Connect vertex horizontally
    for (float i = 0; i < size; i++)
    {
        if ((int(i + 1) % vertexPerWidth) != 0)
        {
            grid.indexes.emplace_back(Point2D{i, i + 1}, Pixel(0, 0, 125) + Pixel(255) * (Fast::Rand() / (float)ULONG_MAX));
        }
    }
    //Connect vertex vertically
    for (float i = 0; i < (size - vertexPerWidth); i++)
    {
        grid.indexes.emplace_back(Point2D{i, i + vertexPerWidth}, Pixel(0, 0, 125) + Pixel(255) * (Fast::Rand() / (float)ULONG_MAX));
    }
}

void FinalDemo::GeneratePerspectiveProjection(Object3D &object)
{
    const float depthFactor = 0.001;
    const int halftWidth = width / 2;
    const int halftHeight = height / 2;

    object.projectedPoints.clear();

    for (unsigned int i = 0, n = object.points.size(); i < n; i++)
    {
        Point3D p = object.points[i];
        float depth = (p.Z != 0.f) ? (p.Z * depthFactor + 1.f) : 1.f; //Depth can't be 0

        object.projectedPoints.push_back({((p.X - halftWidth) / depth) + halftWidth, ((p.Y - halftHeight) / depth) + halftHeight});
        //Move points to the origin, then apply depth by dividing and then move points back to where they were
    }
}

void FinalDemo::RenderObject(Object3D object)
{
    for (int i = 0, n = object.indexes.size(); i < n; i++)
    {
        Point2D indexPair = object.indexes[i].first;
        Point2D startPoint = object.projectedPoints[indexPair.X];
        Point2D endPoint = object.projectedPoints[indexPair.Y];

        RenderLine(startPoint.X, startPoint.Y, endPoint.X, endPoint.Y, object.indexes[i].second, 2);
    }
}

void FinalDemo::EraseObject(Object3D object)
{
    for (int i = 0, n = object.indexes.size(); i < n; i++)
    {
        Point2D indexPair = object.indexes[i].first;
        Point2D startPoint = object.projectedPoints[indexPair.X];
        Point2D endPoint = object.projectedPoints[indexPair.Y];

        RenderLine(startPoint.X, startPoint.Y, endPoint.X, endPoint.Y, Pixel(0), 2);
    }
}

void FinalDemo::TranslateObject(Object3D &object, Point3D offset)
{
    for (unsigned int i = 0, n = object.points.size(); i < n; i++)
    {
        object.points[i] += offset;
    }
}

void FinalDemo::ApplyWaveTransformation(Object3D &object, float amplitude, float frequency, float deltaTime, float phase)
{
    static float accumulatedTime = 0;
    accumulatedTime += deltaTime;

    for (float j = 0; j < vertexPerDepth; j++)
    {
        for (float i = 0; i < vertexPerWidth; i++)
        {
            //Formula of traveling wave -> ((2 * pi * x) / wavelength) - 2 * pi * frequency * time
            const float wavelength = 1000;
            const float period = 20;
            float wave = (2 * Fast::PI * (grid.points[j * vertexPerWidth + i].Z + phase)) / wavelength + (2 * Fast::PI * accumulatedTime) / period;
            
            grid.points[j * vertexPerWidth + i].Y += amplitude * sin(wave);
        }
    }
}