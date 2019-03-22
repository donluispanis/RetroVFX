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

    perspective = true;
    objectsIndex = 0;
    transformationsIndex = 0;

    CreateCube();
    CreatePyramid();
    CreateStar();

    InitialiseTransformations();

    RegisterInput();

    return true;
}

bool GeometryDemo::Destroy()
{
    return true;
}

void GeometryDemo::InitialiseTransformations()
{
    transformations.push_back(Point3D(width / 2, height / 2, 400.f));
    transformations.push_back(Point3D(0.f, 0.f, 0.f));
    transformations.push_back(Point3D(1.f, 1.f, 1.f));

    transformMultiplier.push_back(100.f);
    transformMultiplier.push_back(1.f);
    transformMultiplier.push_back(1.f);

    transformText.push_back("Translation mode");
    transformText.push_back("Rotation mode");
    transformText.push_back("Scaling mode");
}

void GeometryDemo::CreateCube()
{
    objects.push_back(Object3D{
        {{100, 100, 100}, {100, 200, 100}, {200, 100, 100}, {200, 200, 100}, {100, 100, 200}, {100, 200, 200}, {200, 100, 200}, {200, 200, 200}},
        {std::make_pair<Point2D, Pixel>({0, 1}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({0, 2}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({2, 3}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({1, 3}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({0, 4}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({1, 5}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({2, 6}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({3, 7}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({4, 5}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({4, 6}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({6, 7}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({5, 7}, {0,0,0})},
        {}});

    TranslateObject(objects[0], Point3D{-150, -150, -150});
    Rotate3DObjectAroundZAxis(objects[0], Fast::PI / 4.f);
    Rotate3DObjectAroundXAxis(objects[0], Fast::PI / 4.f);
    GeneratePerspectiveProjection(objects[0]);
}

void GeometryDemo::CreatePyramid()
{
    objects.push_back(Object3D{
        {{0, -75, 0}, {-100, 75, -100}, {-100, 75, 100}, {100, 75, -100}, {100, 75, 100}},
        {std::make_pair<Point2D, Pixel>({0, 1}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({0, 2}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({0, 3}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({0, 4}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({1, 2}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({1, 3}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({2, 4}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({3, 4}, {0,0,0})},
        {}});

    GeneratePerspectiveProjection(objects[1]);
}

void GeometryDemo::CreateStar()
{
    objects.push_back(Object3D{
        {{0, 0, 0},
         {100, 100, 0},
         {100, -100, 0},
         {100, 0, 100},
         {100, 0, -100},
         {-100, 100, 0},
         {-100, -100, 0},
         {-100, 0, 100},
         {-100, 0, -100},
         {0, 100, 100},
         {0, -100, 100},
         {0, 100, -100},
         {0, -100, -100}},
        {std::make_pair<Point2D, Pixel>({0, 1}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({0, 2}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({0, 3}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({0, 4}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({0, 5}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({0, 6}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({0, 7}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({0, 8}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({0, 9}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({0, 10}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({0, 11}, {0,0,0}),
        std::make_pair<Point2D, Pixel>({0, 12}, {0,0,0})},
        {}});

    Rotate3DObjectAroundYAxis(objects[2], Fast::PI / 8.f);
    GeneratePerspectiveProjection(objects[2]);
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
    windowManager->RegisterKeyInput((int)Key::X);
}

bool GeometryDemo::Update(float deltaTime)
{
    UpdateInput(deltaTime);

    EraseObject(objects[objectsIndex]);
    ApplyObjectTransformations();
    ApplyPerspective();
    RenderObject(objects[objectsIndex], Pixel(255));
    RenderInstructions();
    UndoObjectTransformations();

    return true;
}

void GeometryDemo::ApplyObjectTransformations()
{
    ScaleObject(objects[objectsIndex], transformations[2]);
    Rotate3DObjectAroundZAxis(objects[objectsIndex], -transformations[1].Y);
    Rotate3DObjectAroundYAxis(objects[objectsIndex], -transformations[1].X);
    Rotate3DObjectAroundXAxis(objects[objectsIndex], -transformations[1].Z);
    TranslateObject(objects[objectsIndex], transformations[0]);
}

void GeometryDemo::ApplyPerspective()
{
    if (perspective)
    {
        GeneratePerspectiveProjection(objects[objectsIndex]);
    }
    else
    {
        Generate2DProjection(objects[objectsIndex]);
    }
}

void GeometryDemo::RenderInstructions()
{
    RenderText("Tap z to change transformation (translation, rotation, scaling)", 5, 5, 2, Pixel{255, 255, 255});
    RenderText("Tap x to deactivate/active perspective", 5, 20, 2, Pixel{255, 255, 255});
    RenderText("Tap space to change the model", 5, 35, 2, Pixel{255, 255, 255});
    RenderText("Use q, w, e, a, s, d to move in 3d space", 5, 50, 2, Pixel{255, 255, 255});
    RenderText(transformText[transformationsIndex], 5, 75, 2, Pixel{255, 255, 255});
}

void GeometryDemo::UndoObjectTransformations()
{
    TranslateObject(objects[objectsIndex], Point3D(-transformations[0].X, -transformations[0].Y, -transformations[0].Z));
    Rotate3DObjectAroundXAxis(objects[objectsIndex], transformations[1].Z);
    Rotate3DObjectAroundYAxis(objects[objectsIndex], transformations[1].X);
    Rotate3DObjectAroundZAxis(objects[objectsIndex], transformations[1].Y);
    ScaleObject(objects[objectsIndex], Point3D(1 / transformations[2].X, 1 / transformations[2].Y, 1 / transformations[2].Z));
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

void GeometryDemo::GeneratePerspectiveProjection(Object3D &object)
{
    const float depthFactor = 0.001;
    const int halftWidth = width / 2;
    const int halftHeight = height / 2;

    object.projectedPoints.clear();

    for (unsigned int i = 0, n = object.points.size(); i < n; i++)
    {
        Point3D p = object.points[i];
        float depth = (p.Z != 0.f) ? (p.Z * depthFactor) : 1.f; //Depth can't be 0

        object.projectedPoints.push_back({((p.X - halftWidth) / depth) + halftWidth, ((p.Y - halftHeight) / depth) + halftHeight});
        //Move points to the origin, then apply depth by dividing and then move points back to where they were
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
        Point2D indexPair = object.indexes[i].first;
        Point2D startPoint = object.projectedPoints[indexPair.X];
        Point2D endPoint = object.projectedPoints[indexPair.Y];

        RenderLine(startPoint.X, startPoint.Y, endPoint.X, endPoint.Y, colour);
    }
}

void GeometryDemo::EraseObject(Object3D object)
{
    RenderObject(object, Pixel(0));
}

void GeometryDemo::UpdateInput(float deltaTime)
{
    bool changeMode = windowManager->IsKeyPressed((int)Key::Z);
    bool changeModel = windowManager->IsKeyPressed((int)Key::SPACE);
    bool changePerspective = windowManager->IsKeyPressed((int)Key::X);
    bool goLeft = windowManager->IsKeyHeld((int)Key::A);
    bool goRight = windowManager->IsKeyHeld((int)Key::D);
    bool goForward = windowManager->IsKeyHeld((int)Key::W);
    bool goBackwards = windowManager->IsKeyHeld((int)Key::S);
    bool goUp = windowManager->IsKeyHeld((int)Key::Q);
    bool goDown = windowManager->IsKeyHeld((int)Key::E);

    if (changeMode)
    {
        transformationsIndex++;
        if (transformationsIndex == transformations.size())
        {
            transformationsIndex = 0;
        }
        ClearScreen(Pixel(0));
    }
    if (changeModel)
    {
        objectsIndex++;
        if (objectsIndex == objects.size())
        {
            objectsIndex = 0;
        }
        ClearScreen(Pixel(0));
    }
    if(changePerspective)
    {
        perspective = !perspective;
    }

    if (goLeft)
    {
        transformations[transformationsIndex].X -= deltaTime * transformMultiplier[transformationsIndex];
    }
    if (goRight)
    {
        transformations[transformationsIndex].X += deltaTime * transformMultiplier[transformationsIndex];
    }
    if (goUp)
    {
        transformations[transformationsIndex].Y -= deltaTime * transformMultiplier[transformationsIndex];
    }
    if (goDown)
    {
        transformations[transformationsIndex].Y += deltaTime * transformMultiplier[transformationsIndex];
    }
    if (goBackwards)
    {
        transformations[transformationsIndex].Z -= deltaTime * transformMultiplier[transformationsIndex];
    }
    if (goForward)
    {
        transformations[transformationsIndex].Z += deltaTime * transformMultiplier[transformationsIndex];
    }
}