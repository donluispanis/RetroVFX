#include "Geometry.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"
#include "../Utils/Fast.h"
#include <cmath>
#include <utility>

bool GeometryDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    object = {
        {{100, 100, 100}, {100, 200, 100}, {200, 100, 100}, {200, 200, 100}, {100, 100, 200}, {100, 200, 200}, {200, 100, 200}, {200, 200, 200}},
        {{0, 1}, {0, 2}, {2, 3}, {1, 3}, {0, 4}, {1, 5}, {2, 6}, {3, 7}, {4, 5}, {4, 6}, {6, 7}, {5, 7}},
        {}};

    TranslateObject(object, Point3D{-150, -150, -150});
    Rotate3DObjectAroundZAxis(object, Fast::PI / 4.f);
    Rotate3DObjectAroundXAxis(object, Fast::PI / 4.f);
    Generate2DProjection(object);

    return true;
}

bool GeometryDemo::Update(float deltaTime)
{
    //Erase
    RenderObject(object, Pixel(0));

    //Transform
    //Rotate3DObjectAroundXAxis(object, 0.005);
    Rotate3DObjectAroundYAxis(object, 0.005);
    //Rotate3DObjectAroundZAxis(object, 0.005);
    //ScaleObject(object, Point3D{1.0001f,1.0001f,1.0001f});
    TranslateObject(object, Point3D{500, 500, 0});

    //Project
    Generate2DProjection(object);

    //Render
    RenderObject(object, Pixel(255));
    RenderText("Geometry", 5, 5, 2, Pixel{255, 255, 255});

    //Undo some transforms
    TranslateObject(object, Point3D{-500, -500, 0});
    return true;
}

void GeometryDemo::Generate2DProjection(Object3D &object)
{
    object.projectedPoints.clear();

    for (unsigned int i = 0, n = object.indexes.size(); i < n; i++)
    {
        Point3D p = object.points[i];
        object.projectedPoints.push_back({p.X, p.Y});
    }
}

void GeometryDemo::TranslateObject(Object3D &object, Point3D offset)
{  
    std::vector<Point3D> newPoints;
    for (unsigned int i = 0, n = object.indexes.size(); i < n; i++)
    {
        Point3D p = object.points[i];
        newPoints.push_back(Point3D{p.X + offset.X, p.Y + offset.Y, p.Z + offset.Z});
    }
    object.points = newPoints;
}

void GeometryDemo::ScaleObject(Object3D &object, Point3D scale)
{
    for (unsigned int i = 0, n = object.indexes.size(); i < n; i++)
    {
        Point3D p = object.points[i];
        Point3D aux;

        aux.X = p.X * scale.X;
        aux.Y = p.Y * scale.Y;
        aux.Z = p.Y * scale.Z;
        
        object.points[i] = aux;
    }
}

void GeometryDemo::Rotate3DObjectAroundXAxis(Object3D &object, float angle)
{
    for (unsigned int i = 0, n = object.indexes.size(); i < n; i++)
    {
        Point3D p = object.points[i];
        Point3D aux;

        aux.X = p.X;
        aux.Y = p.Y * cosf(angle) - p.Z * sinf(angle);
        aux.Z = p.Y * sinf(angle) + p.Z * cosf(angle);
        
        object.points[i] = aux;
    }
}

void GeometryDemo::Rotate3DObjectAroundYAxis(Object3D &object, float angle)
{
    for (unsigned int i = 0, n = object.indexes.size(); i < n; i++)
    {
        Point3D p = object.points[i];
        Point3D aux;

        aux.X = p.X * cosf(angle) + p.Z * sinf(angle);
        aux.Y = p.Y;
        aux.Z = -p.X * sinf(angle) + p.Z * cosf(angle);

        object.points[i] = aux;
    }
}

void GeometryDemo::Rotate3DObjectAroundZAxis(Object3D &object, float angle)
{
    for (unsigned int i = 0, n = object.indexes.size(); i < n; i++)
    {
        Point3D p = object.points[i];
        Point3D aux;

        aux.X = p.X * cosf(angle) - p.Y * sinf(angle);
        aux.Y = p.X * sinf(angle) + p.Y * cosf(angle);
        aux.Z = p.Z;

        object.points[i] = aux;
    }
}

void GeometryDemo::RenderObject(Object3D object, const Pixel &colour)
{
    for (int i = 0, n = object.indexes.size(); i < n; i++)
    {
        Point2D indexPair = object.indexes[i];
        Point2D startPoint = object.projectedPoints[indexPair.X];
        Point2D endPoint = object.projectedPoints[indexPair.Y];

        RenderLine(startPoint.X, startPoint.Y, endPoint.X, endPoint.Y, colour);
    }
}

bool GeometryDemo::Destroy()
{
    return true;
}