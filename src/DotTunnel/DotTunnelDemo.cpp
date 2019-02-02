#include "DotTunnelDemo.h"
#include "../Utils/Pixel.h"
#include "../Utils/ColourStamp.h"
#include "../Utils/ColourStampGradients.h"
#include "../Utils/Fast.h"
#include "../Utils/InputValues.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"
#include <vector>

struct TurbulencePath
{
    int radius;
    int phase;
    int direction;
    float advance;
};

bool DotTunnelDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    mathTableSize = 1024;
    sineTable = Fast::GenerateSineTable(mathTableSize);
    cosineTable = Fast::GenerateCosineTable(mathTableSize);

    circleCount = 20;
    defaultCircle.x = width / 2;
    defaultCircle.y = height / 2;
    defaultCircle.radius = 20;
    defaultCircle.rotation = 0;
    defaultCircle.density = 10;
    defaultCircle.colour = Pixel(255);
    maxCircleRadius = height;
    dotSize = 2;

    pathX = 0.f;
    pathY = 0.f;
    pathRadius = height / 2;
    pathComplexity = 4;
    pathVelocity = 10;

    radiusVelocity = 1;
    defaultRotationVelocity = 20;
    rotationVelocity = defaultRotationVelocity;

    pathCirclesDistance = 2;

    colourMapSize = 50;
    colourMap = new Pixel[colourMapSize];
    ColourStamp::GenerateGradient(ColourStampGradients::RAINBOW, colourMap, colourMapSize);
    currentColour = 0;

    InitCircleQueue();

    return true;
}

void DotTunnelDemo::InitCircleQueue()
{
    UpdateTunnelPath(100);

    circles.push_back(Circle{defaultCircle.x + int(pathX * pathRadius),
                             defaultCircle.y + int(pathY * pathRadius),
                             defaultCircle.radius,
                             defaultCircle.rotation,
                             defaultCircle.density,
                             colourMap[currentColour]});
}

bool DotTunnelDemo::Update(float deltaTime)
{
    UpdateCircleQueue(deltaTime);
    UpdateTunnelPath(deltaTime);
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
    if (circles[0].radius > defaultCircle.radius + (defaultCircle.radius * pathCirclesDistance) / circleCount)
    {
        currentColour++;
        circles.push_front({defaultCircle.x + int(pathX * pathRadius),
                            defaultCircle.y + int(pathY * pathRadius),
                            defaultCircle.radius,
                            defaultCircle.rotation,
                            defaultCircle.density,
                            colourMap[currentColour % colourMapSize]});
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
    bool isGoingUp = windowManager->IsKeyDown((int)Key::UP);
    bool isGoingDown = windowManager->IsKeyDown((int)Key::DOWN);
    bool isGoingLeft = windowManager->IsKeyDown((int)Key::LEFT);
    bool isGoingRight = windowManager->IsKeyDown((int)Key::RIGHT);

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
    bool isIncreasingSpeed = windowManager->IsKeyDown((int)Key::W);
    bool isDecreasingSpeed = windowManager->IsKeyDown((int)Key::S);

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
    bool isDotSizeIncreasing = windowManager->IsKeyDown((int)Key::D);
    bool isDotSizeDecreasing = windowManager->IsKeyDown((int)Key::A);
    static bool isIncreasingHeld = false;
    static bool isDecreasingHeld = false;

    if (isDotSizeIncreasing && !isIncreasingHeld)
    {
        if (dotSize < 15)
        {
            dotSize++;
            ClearScreen(Pixel(0));
        }
        isIncreasingHeld = true;
    }
    else if (!isDotSizeIncreasing)
    {
        isIncreasingHeld = false;
    }

    if (isDotSizeDecreasing && !isDecreasingHeld)
    {
        if (dotSize > 1)
        {
            dotSize--;
            ClearScreen(Pixel(0));
        }
        isDecreasingHeld = true;
    }
    else if (!isDotSizeDecreasing)
    {
        isDecreasingHeld = false;
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

    if(opacity < 0.f)
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

void DotTunnelDemo::UpdateTunnelPath(float deltaTime)
{
    static std::vector<TurbulencePath> turbulencePaths;

    pathX = 0.f;
    pathY = 0.f;

    for (int i = 0; i < pathComplexity; i++)
    {
        if ((int)turbulencePaths.size() < pathComplexity)
        {
            turbulencePaths.push_back(TurbulencePath{
                height / (i + 2),
                (int)Fast::Rand() % mathTableSize,
                i % 2 == 0 ? 1 : -1,
                0});
        }

        TurbulencePath &tP = turbulencePaths[i];
        tP.advance += deltaTime * 0.1;
        int waveAmplitude = (tP.advance * tP.radius * pathVelocity) / float(i + 2);
        pathX += cosineTable[int(waveAmplitude + tP.phase) % mathTableSize];
        pathY += sineTable[int(waveAmplitude + tP.phase) % mathTableSize];
    }

    pathX /= (float)pathComplexity;
    pathY /= (float)pathComplexity;
}

bool DotTunnelDemo::Destroy()
{
    delete[] sineTable;
    delete[] cosineTable;

    return true;
}