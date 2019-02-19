#include "Geometry.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"

bool GeometryDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    object = {
        {},
        {{100, 100}, {100, 200}, {200, 100}, {200, 200}},
        {{0, 1}, {0, 2}, {2, 3}, {1, 3}},
        {255, 255, 255}};

    return true;
}

bool GeometryDemo::Update(float deltaTime)
{
    RenderObject(object);
    RenderText("Geometry", 5, 5, 2, Pixel{255, 255, 255});
    return true;
}

void GeometryDemo::RenderObject(Object3D object)
{
    for (int i = 0, n = object.indexes.size(); i < n; i++)
    {
        Point2D indexPair = object.indexes[i];
        Point2D startPoint = object.projectedPoints[indexPair.X];
        Point2D endPoint = object.projectedPoints[indexPair.Y];

        RenderLine(startPoint.X, startPoint.Y, endPoint.X, endPoint.Y, object.colour);
    }
}

bool GeometryDemo::Destroy()
{
    return true;
}