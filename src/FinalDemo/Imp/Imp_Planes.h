#pragma once

#include "../../Utils/Pixel.h"
#include "../../Utils/Point2D.h"
#include <deque>

struct FinalDemo;

class Imp_Planes
{
public:
    void InitPlanes(int width, int height, Pixel *pixels, FinalDemo *engine);
    void UpdatePlanes(float deltaTime, float accumulatedTime, float startTime);
    void ClosePlanes();

private:
    struct waypoint
    {
        float x, y, ang, scale, time;
    };

    void InitialiseTexture();
    void InitialiseWaypoints();
    bool ClearScreenCloseToHorizon(int i, int j, int nw, int totalHeight, int totalHeight1, float accumulatedTime, float startTime);
    bool IsPointOutOfBounds(Point2D &rotatedPoint);
    void UpdatePath(float deltaTime);

    Pixel *texture;
    int texWidth, texHeight;

    Point2D cameraPosition;
    float cameraAngle = 0.f;
    float textureScale = 20.f;

    std::deque<waypoint> waypoints;

    bool clearScreen = false;
    const int fieldOfView = 500;

    int width, height;
    Pixel *pixels;
    FinalDemo *engine;
};