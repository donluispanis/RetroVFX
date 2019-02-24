#include "Geometry.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"
#include "../Utils/Fast.h"
#include "../Utils/InputValues.h"
#include <cmath>
 
bool GeometryDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    objects.push_back(Object3D{
        {{100, 100, 100}, {100, 200, 100}, {200, 100, 100}, {200, 200, 100}, {100, 100, 200}, {100, 200, 200}, {200, 100, 200}, {200, 200, 200}},
        {{0, 1}, {0, 2}, {2, 3}, {1, 3}, {0, 4}, {1, 5}, {2, 6}, {3, 7}, {4, 5}, {4, 6}, {6, 7}, {5, 7}},
        {}});

    TranslateObject(objects[0], Point3D{-150, -150, -150});
    Rotate3DObjectAroundZAxis(objects[0], Fast::PI / 4.f);
    Rotate3DObjectAroundXAxis(objects[0], Fast::PI / 4.f);
    Generate2DProjection(objects[0]);

    transformations.push_back(Point3D(width / 2, height / 2, 0.f));
    transformations.push_back(Point3D(0.f,0.f,0.f));
    transformations.push_back(Point3D(1.f,1.f,1.f));

    transformMultiplier.push_back(100.f);
    transformMultiplier.push_back(1.f);
    transformMultiplier.push_back(1.f);

    objectsIndex = 0;
    transformationsIndex = 0;

    RegisterInput();

    RenderText("Translation mode", 5, 60, 2, Pixel{255, 255, 255});

    return true;
}

bool GeometryDemo::Destroy()
{
    return true;
}

void GeometryDemo::RegisterInput()
{
    windowManager->RegisterKeyInput((int)Key::SPACE);
    windowManager->RegisterKeyInput((int)Key::Q);
    windowManager->RegisterKeyInput((int)Key::W);
    windowManager->RegisterKeyInput((int)Key::E);
    windowManager->RegisterKeyInput((int)Key::A);
    windowManager->RegisterKeyInput((int)Key::S);
    windowManager->RegisterKeyInput((int)Key::D);
    windowManager->RegisterKeyInput((int)Key::Z);
}

bool GeometryDemo::Update(float deltaTime)
{
    UpdateInput(deltaTime);

    //Erase
    RenderObject(objects[0], Pixel(0));
    static float scale = 1.f;
    scale += 0.001f;
    static float angle = 0.f;
    angle += 0.005f;

    //Transform
    ScaleObject(objects[objectsIndex], transformations[2]);
    Rotate3DObjectAroundYAxis(objects[objectsIndex], transformations[1].Y);
    Rotate3DObjectAroundXAxis(objects[objectsIndex], transformations[1].X);
    Rotate3DObjectAroundZAxis(objects[objectsIndex], transformations[1].Z);
    TranslateObject(objects[objectsIndex], transformations[0]);

    //Project
    Generate2DProjection(objects[objectsIndex]);

    //Render
    RenderObject(objects[objectsIndex], Pixel(255));
    RenderText("Tap z to change transformation (translation, rotation, scaling)", 5, 5, 2, Pixel{255, 255, 255});
    RenderText("Tap space to change the model", 5, 20, 2, Pixel{255, 255, 255});
    RenderText("Use q, w, e, a, s, d to move in 3d space", 5, 35, 2, Pixel{255, 255, 255});

    //Undo transforms
    TranslateObject(objects[objectsIndex], Point3D(-transformations[0].X, -transformations[0].Y, -transformations[0].Z));
    Rotate3DObjectAroundZAxis(objects[objectsIndex], -transformations[1].Z);
    Rotate3DObjectAroundXAxis(objects[objectsIndex], -transformations[1].X);
    Rotate3DObjectAroundYAxis(objects[objectsIndex], -transformations[1].Y);
    ScaleObject(objects[objectsIndex], Point3D(1 / transformations[2].X, 1 / transformations[2].Y, 1 / transformations[2].Z));

    return true;
}

void GeometryDemo::Generate2DProjection(Object3D &object)
{
    object.projectedPoints.clear();

    for (unsigned int i = 0, n = object.points.size(); i < n; i++)
    {
        Point3D p = object.points[i];
        object.projectedPoints.push_back({p.X, p.Y});
    }
}

void GeometryDemo::TranslateObject(Object3D &object, Point3D offset)
{
    for (unsigned int i = 0, n = object.points.size(); i < n; i++)
    {
        object.points[i] += offset;
    }
}

void GeometryDemo::ScaleObject(Object3D &object, Point3D scale)
{
    for (unsigned int i = 0, n = object.points.size(); i < n; i++)
    {
        object.points[i] *= scale;
    }
}

void GeometryDemo::Rotate3DObjectAroundXAxis(Object3D &object, float angle)
{
    for (unsigned int i = 0, n = object.points.size(); i < n; i++)
    {
        Point3D p = object.points[i];

        object.points[i] = Point3D(
            p.X,
            p.Y * cosf(angle) - p.Z * sinf(angle),
            p.Y * sinf(angle) + p.Z * cosf(angle));
    }
}

void GeometryDemo::Rotate3DObjectAroundYAxis(Object3D &object, float angle)
{
    for (unsigned int i = 0, n = object.points.size(); i < n; i++)
    {
        Point3D p = object.points[i];

        object.points[i] = Point3D(
            p.X * cosf(angle) + p.Z * sinf(angle),
            p.Y,
            -p.X * sinf(angle) + p.Z * cosf(angle));
    }
}

void GeometryDemo::Rotate3DObjectAroundZAxis(Object3D &object, float angle)
{
    for (unsigned int i = 0, n = object.points.size(); i < n; i++)
    {
        Point3D p = object.points[i];

        object.points[i] = Point3D(
            p.X * cosf(angle) - p.Y * sinf(angle),
            p.X * sinf(angle) + p.Y * cosf(angle),
            p.Z);
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

void GeometryDemo::UpdateInput(float deltaTime)
{
    bool changeMode = windowManager->IsKeyPressed((int)Key::Z);
    bool changeModel = windowManager->IsKeyPressed((int)Key::SPACE);
    bool goLeft = windowManager->IsKeyHeld((int)Key::A);
    bool goRight = windowManager->IsKeyHeld((int)Key::D);
    bool goForward = windowManager->IsKeyHeld((int)Key::W);
    bool goBackwards = windowManager->IsKeyHeld((int)Key::S);
    bool goUp = windowManager->IsKeyHeld((int)Key::Q);
    bool goDown = windowManager->IsKeyHeld((int)Key::E);

    if(changeMode)
    {
        transformationsIndex++;
        if(transformationsIndex == transformations.size())
        {
            transformationsIndex = 0;
        }

        if(transformationsIndex == 0)
        {
            ClearScreen(Pixel(0));
            RenderText("Translation mode", 5, 60, 2, Pixel{255, 255, 255});
        }
        if(transformationsIndex == 1)
        {
            ClearScreen(Pixel(0));
            RenderText("Rotation mode", 5, 60, 2, Pixel{255, 255, 255});
        }
        if(transformationsIndex == 2)
        {
            ClearScreen(Pixel(0));
            RenderText("Scaling mode", 5, 60, 2, Pixel{255, 255, 255});
        }
    }
    if(changeModel)
    {
        objectsIndex++;
        if(objectsIndex == objects.size())
        {
            objectsIndex = 0;
        }
    }

    if(goLeft)
    {
        transformations[transformationsIndex].X -= deltaTime * transformMultiplier[transformationsIndex];
    }
    if(goRight)
    {
        transformations[transformationsIndex].X += deltaTime * transformMultiplier[transformationsIndex];
    }
    if(goUp)
    {
        transformations[transformationsIndex].Y -= deltaTime * transformMultiplier[transformationsIndex];
    }
    if(goDown)
    {
        transformations[transformationsIndex].Y += deltaTime * transformMultiplier[transformationsIndex];
    }
    if(goBackwards)
    {
        transformations[transformationsIndex].Z -= deltaTime * transformMultiplier[transformationsIndex];
    }
    if(goForward)
    {
        transformations[transformationsIndex].Z += deltaTime * transformMultiplier[transformationsIndex];
    }
}