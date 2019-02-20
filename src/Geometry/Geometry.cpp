#include "Geometry.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"
#include <cmath>
#include <utility>

GeometryDemo::Point3D::Point3D()
    : X(0.f), Y(0.f), Z(0.f)
{
}

GeometryDemo::Point3D::Point3D(float x, float y, float z)
    : X(x), Y(y), Z(z)
{
}

GeometryDemo::Point3D GeometryDemo::Point3D::operator+=(const Point3D &p) const
{
    return std::move(
        Point3D(
            this->X + p.X,
            this->Y + p.Y,
            this->Z + p.Z));
}

bool GeometryDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    object = {
        {{100, 100, 100}, {100, 200, 100}, {200, 100, 100}, {200, 200, 100}, {150, 150, 200}, {150, 250, 200}, {250, 150, 200}, {250, 250, 200}},
        {{0, 1}, {0, 2}, {2, 3}, {1, 3}, {0, 4}, {1, 5}, {2, 6}, {3, 7}, {4, 5}, {4, 6}, {6, 7}, {5, 7}},
        {}};

    TranslateObject(object, Point3D(300, 300, 0));
    Generate2DProjection(object);

    return true;
}

bool GeometryDemo::Update(float deltaTime)
{
    RenderObject(object, Pixel(0));
    Rotate3DObjectAroundZAxis(object, 0.001);
    Generate2DProjection(object);
    RenderObject(object, Pixel(255));
    RenderText("Geometry", 5, 5, 2, Pixel{255, 255, 255});
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
    for (unsigned int i = 0, n = object.indexes.size(); i < n; i++)
    {
        object.points[i] += offset;
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