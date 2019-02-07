#include "DotTunnelDemo.h"
#include "../Utils/Fast.h"
#include "../Utils/Pixel.h"
#include "../Utils/ColourStamp.h"
#include "../Utils/InputValues.h"
#include "../Utils/TurbulencePath.h"
#include "../Utils/ColourStampGradients.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"

bool DotTunnelDemo::Init()
{
    InitWindowManagerData();
    InitDefaultCircleData();
    InitMathTables();
    InitTurbulencePath();
    InitColourMap();
    InitInput();

    AddCircle();

    return true;
}

void DotTunnelDemo::InitWindowManagerData()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();
}

void DotTunnelDemo::InitDefaultCircleData()
{
    maxCircleRadius = height;
    circleCount = 20;
    dotSize = 2;
    defaultCircle = Circle{width / 2.f, height / 2.f, 20, 0, 10, Pixel()};

    radiusVelocity = 1;
    defaultRotationVelocity = 20;
    rotationVelocity = defaultRotationVelocity;

    circlesGapDistance = 2;
}

void DotTunnelDemo::InitMathTables()
{
    mathTableSize = 1024;
    sineTable = Fast::GenerateSineTable(mathTableSize);
    cosineTable = Fast::GenerateCosineTable(mathTableSize);
}

void DotTunnelDemo::InitTurbulencePath()
{
    turbulencePath = new TurbulencePath(sineTable, cosineTable, mathTableSize);
    turbulencePath->CreateTurbulencePath(10, height / 2, 4);
    turbulencePath->UpdateTurbulencePath(100, pathX, pathY);
}

void DotTunnelDemo::InitColourMap()
{
    colourMapSize = 50;
    colourMap = new Pixel[colourMapSize];
    ColourStamp::GenerateGradient(ColourStampGradients::RAINBOW, colourMap, colourMapSize);
    currentColour = 0;
}

bool DotTunnelDemo::Destroy()
{
    Fast::DeleteMathTable(sineTable);
    Fast::DeleteMathTable(cosineTable);

    delete turbulencePath;
    delete[] colourMap;

    return true;
}

void DotTunnelDemo::InitInput()
{
    windowManager->RegisterKeyInput((int)Key::A);
    windowManager->RegisterKeyInput((int)Key::W);
    windowManager->RegisterKeyInput((int)Key::S);
    windowManager->RegisterKeyInput((int)Key::D);
    windowManager->RegisterKeyInput((int)Key::UP);
    windowManager->RegisterKeyInput((int)Key::DOWN);
    windowManager->RegisterKeyInput((int)Key::LEFT);
    windowManager->RegisterKeyInput((int)Key::RIGHT);
}

void DotTunnelDemo::AddCircle()
{
    circles.push_front(Circle{defaultCircle.x + (int)pathX,
                              defaultCircle.y + (int)pathY,
                              defaultCircle.radius,
                              defaultCircle.rotation,
                              defaultCircle.density,
                              colourMap[currentColour % colourMapSize]});
}

bool DotTunnelDemo::Update(float deltaTime)
{
    UpdateCircleQueue(deltaTime);
    turbulencePath->UpdateTurbulencePath(deltaTime, pathX, pathY);
    UpdateInput(deltaTime);

    RenderText("Keep pressed the arrow keys to control the tunnel", 5, 5, 2, Pixel(255));
    RenderText("Keep pressed W/S to increase/decrease velocity", 5, 20, 2, Pixel(255));
    RenderText("Tap A/D to increase/decrease dot size", 5, 35, 2, Pixel(255));

    return true;
}

void DotTunnelDemo::UpdateCircleQueue(float deltaTime)
{
    for (auto c : circles)
    {
        EraseCircle(c);
    }

    PopulateCircleQueue();

    for (auto &c : circles)
    {
        UpdateCircle(c, deltaTime);
        DrawCircle(c);
    }
}

void DotTunnelDemo::PopulateCircleQueue()
{
    if (circles[0].radius > defaultCircle.radius + (defaultCircle.radius * circlesGapDistance) / circleCount)
    {
        currentColour++;
        AddCircle();
    }
    if (circles[circles.size() - 1].radius > maxCircleRadius)
    {
        circles.pop_back();
    }
}

void DotTunnelDemo::UpdateInput(float deltaTime)
{
    UpdatePositionFromInput(deltaTime);
    UpdateVelocityFromInput(deltaTime);
    UpdateDotSizeFromInput(deltaTime);
}

void DotTunnelDemo::UpdatePositionFromInput(float deltaTime)
{
    bool isGoingUp = windowManager->IsKeyHeld((int)Key::UP);
    bool isGoingDown = windowManager->IsKeyHeld((int)Key::DOWN);
    bool isGoingLeft = windowManager->IsKeyHeld((int)Key::LEFT);
    bool isGoingRight = windowManager->IsKeyHeld((int)Key::RIGHT);

    if (isGoingUp)
    {
        defaultCircle.y -= deltaTime * 100;
    }
    if (isGoingDown)
    {
        defaultCircle.y += deltaTime * 100;
    }
    if (isGoingLeft)
    {
        defaultCircle.x -= deltaTime * 100;
    }
    if (isGoingRight)
    {
        defaultCircle.x += deltaTime * 100;
    }
}

void DotTunnelDemo::UpdateVelocityFromInput(float deltaTime)
{
    bool isIncreasingSpeed = windowManager->IsKeyHeld((int)Key::W);
    bool isDecreasingSpeed = windowManager->IsKeyHeld((int)Key::S);

    if (isIncreasingSpeed)
    {
        if (radiusVelocity < 5.f)
            radiusVelocity += deltaTime;
        if (rotationVelocity < defaultRotationVelocity * 5.f)
            rotationVelocity += deltaTime * defaultRotationVelocity;
    }
    if (isDecreasingSpeed)
    {
        if (radiusVelocity > 0.3f)
            radiusVelocity -= deltaTime;
        if (rotationVelocity > defaultRotationVelocity)
            rotationVelocity -= deltaTime * defaultRotationVelocity;
    }
}

void DotTunnelDemo::UpdateDotSizeFromInput(float deltaTime)
{
    bool isDotSizeIncreasing = windowManager->IsKeyPressed((int)Key::D);
    bool isDotSizeDecreasing = windowManager->IsKeyPressed((int)Key::A);

    if (isDotSizeIncreasing && dotSize < 15)
    {
        dotSize++;
        ClearScreen(Pixel(0));
    }

    if (isDotSizeDecreasing && dotSize > 1)
    {
        dotSize--;
        ClearScreen(Pixel(0));
    }
}

void DotTunnelDemo::DrawCircle(const Circle &c)
{
    float increment = 1 / (float)(c.density);
    int indexFactor = mathTableSize / (2 * Fast::PI);
    int x, y;

    for (float i = 0, n = 2 * Fast::PI; i < n; i += increment)
    {
        x = sineTable[int(i * indexFactor + c.rotation) % mathTableSize] * c.radius + c.x;
        y = cosineTable[int(i * indexFactor + c.rotation) % mathTableSize] * c.radius + c.y;

        Pixel finalColour = c.colour * CalculateOpacity(c.radius);
        RenderDot(x, y, finalColour, dotSize);
    }
}

float DotTunnelDemo::CalculateOpacity(const float radius)
{
    float opacity = 1.f;
    float fadeIn = 1.3, fadeOut = 0.7;

    if (radius < defaultCircle.radius * fadeIn)
    {
        opacity = 1 / (defaultCircle.radius * fadeIn - radius + 1); //Starts at 0 and goes up to 1
    }

    if (radius > maxCircleRadius * fadeOut)
    {
        opacity = (maxCircleRadius - radius) / (maxCircleRadius - maxCircleRadius * fadeOut); //Starts at 1 and goes down to 0
    }

    if (opacity < 0.f)
    {
        opacity *= -1.f;
    }

    return opacity;
}

void DotTunnelDemo::UpdateCircle(Circle &c, float deltaTime)
{
    c.radius += c.radius * deltaTime * radiusVelocity;
    c.rotation += deltaTime * rotationVelocity;
}

void DotTunnelDemo::EraseCircle(const Circle &circle)
{
    Circle c = circle;
    c.colour = Pixel();
    DrawCircle(c);
}