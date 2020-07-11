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
    objectsIndex = 1;
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
        {},
        {{0, 1},
         {0, 2},
         {2, 3},
         {1, 3},
         {0, 4},
         {1, 5},
         {2, 6},
         {3, 7},
         {4, 5},
         {4, 6},
         {6, 7},
         {5, 7}},
        {}});

    TranslateObject(objects[0], Point3D{-50, -50, -50});
    Rotate3DObjectAroundZAxis(objects[0], Fast::PI / 4.f);
    Rotate3DObjectAroundXAxis(objects[0], Fast::PI / 4.f);
    GeneratePerspectiveProjection(objects[0]);
}

void GeometryDemo::CreatePyramid()
{
    objects.push_back(Object3D{
        {{0, -75, 0}, {-100, 75, -100}, {-100, 75, 100}, {100, 75, -100}, {100, 75, 100}},
        {},
        {{0, 1},
         {0, 2},
         {0, 3},
         {0, 4},
         {1, 2},
         {1, 3},
         {2, 4},
         {3, 4}},
        {}});

    TranslateObject(objects[1], Point3D{0, 0, 200});
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
        {},
        {{0, 1},
         {0, 2},
         {0, 3},
         {0, 4},
         {0, 5},
         {0, 6},
         {0, 7},
         {0, 8},
         {0, 9},
         {0, 10},
         {0, 11},
         {0, 12}},
        {}});

    TranslateObject(objects[2], Point3D{-125, 0, 300});
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
    windowManager->RegisterKeyInput((int)Key::R);
    windowManager->RegisterKeyInput((int)Key::F);
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
    RenderText("Tap R to change transformation mode", 5, 5, 2, Pixel{255, 255, 255});
    RenderText("Tap F to deactivate/active perspective", 5, 20, 2, Pixel{255, 255, 255});
    RenderText("Tap space to change the model", 5, 35, 2, Pixel{255, 255, 255});
    RenderText("Use q, w, e, a, s, d to move in 3d space", 5, 50, 2, Pixel{255, 255, 255});
    RenderText(transformText[transformationsIndex], 5, 75, 2, Pixel{255, 255, 255});
}

void GeometryDemo::UndoObjectTransformations()
{
    TranslateObject(objects[objectsIndex], -transformations[0]);
    Rotate3DObjectAroundXAxis(objects[objectsIndex], transformations[1].Z);
    Rotate3DObjectAroundYAxis(objects[objectsIndex], transformations[1].X);
    Rotate3DObjectAroundZAxis(objects[objectsIndex], transformations[1].Y);
    ScaleObject(objects[objectsIndex], transformations[2].inverse());
}

void GeometryDemo::Generate2DProjection(Object3D &object)
{
    object.projectedPoints.clear();

    for (Point3D p : object.points)
    {
        object.projectedPoints.push_back({p.X, p.Y});
    }
}

void GeometryDemo::GeneratePerspectiveProjection(Object3D &object)
{
    const float depthFactor = 0.001;
    const int halftWidth = width / 2;
    const int halftHeight = height / 2;

    object.projectedPoints.clear();

    for (const Point3D &p : object.points)
    {
        float depth = (p.Z != 0.f) ? (p.Z * depthFactor) : 1.f; //Depth can't be 0

        object.projectedPoints.push_back({((p.X - halftWidth) / depth) + halftWidth,
                                          ((p.Y - halftHeight) / depth) + halftHeight});
        //Move points to the origin, then apply depth by dividing and then move points back to where they were
    }
}

void GeometryDemo::TranslateObject(Object3D &object, Point3D offset)
{
    for (Point3D &p : object.points)
    {
        p += offset;
    }
}

void GeometryDemo::ScaleObject(Object3D &object, Point3D scale)
{
    for (Point3D &p : object.points)
    {
        p *= scale;
    }
}

void GeometryDemo::Rotate3DObjectAroundXAxis(Object3D &object, float angle)
{
    for (Point3D &p : object.points)
    {
        p = Point3D(
            p.X,
            p.Y * cosf(angle) - p.Z * sinf(angle),
            p.Y * sinf(angle) + p.Z * cosf(angle));
    }
}

void GeometryDemo::Rotate3DObjectAroundYAxis(Object3D &object, float angle)
{
    for (Point3D &p : object.points)
    {
        p = Point3D(
            p.X * cosf(angle) + p.Z * sinf(angle),
            p.Y,
            -p.X * sinf(angle) + p.Z * cosf(angle));
    }
}

void GeometryDemo::Rotate3DObjectAroundZAxis(Object3D &object, float angle)
{
    for (Point3D &p : object.points)
    {
        p = Point3D(
            p.X * cosf(angle) - p.Y * sinf(angle),
            p.X * sinf(angle) + p.Y * cosf(angle),
            p.Z);
    }
}

void GeometryDemo::RenderObject(Object3D object, const Pixel &colour)
{
    for (const Point2D &indexPair : object.indexes)
    {
        Point2D startPoint = object.projectedPoints[indexPair.X];
        Point2D endPoint = object.projectedPoints[indexPair.Y];

        RenderLine(startPoint.X, startPoint.Y, endPoint.X, endPoint.Y, colour, 1);
    }
}

void GeometryDemo::EraseObject(Object3D object)
{
    RenderObject(object, Pixel(0));
}

void GeometryDemo::UpdateInput(float deltaTime)
{
    bool changeMode = windowManager->IsKeyPressed((int)Key::R);
    bool changeModel = windowManager->IsKeyPressed((int)Key::SPACE);
    bool changePerspective = windowManager->IsKeyPressed((int)Key::F);
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
    if (changePerspective)
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