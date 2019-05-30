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

    Pixel *texture;
    int texWidth, texHeight;

    void UpdatePath(float deltaTime);

    Point2D cameraPosition;
    float cameraAngle = 0.f;
    float textureScale = 20.f;

    std::deque<waypoint> waypoints;

    int width, height;
    Pixel *pixels;
    FinalDemo *engine;
};