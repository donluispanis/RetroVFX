#pragma once

#include "../../DotTunnel/Circle.h"
#include "../../Utils/Point2D.h"
#include "../../Utils/TurbulencePath.h"
#include <deque>

struct FinalDemo;

class Imp_Ending
{
public:
    void InitEnding(int width, int height, FinalDemo *engine, float *cosTable, float *sinTable);
    void UpdateEnding(float deltaTime, float accumulatedTime, float startTime);
    void CloseEnding();

private:
    void DrawCircle(const Circle &c);
    float CalculateOpacity(const float radius);
    void UpdateCircle(Circle &c, float deltaTime);
    void EraseCircle(const Circle &circle);
    void AddCircle();
    void UpdateCircleQueue(float deltaTime);
    void PopulateCircleQueue();

    Point2D start, end;
    Point2D tunnelCenter;
    Point2D initialTunnelCenter;
    TurbulencePath *turbulencePath;

    std::deque<Circle> circles;
    int circleCount;
    Circle defaultCircle;
    int maxCircleRadius;
    int dotSize;
    int circlesGapDistance;
    int pointsPerCircle;

    float radiusVelocity;
    float rotationVelocity;
    float defaultRotationVelocity;

    int tunnelColourMapSize;
    Pixel *tunnelColourMap;
    int tunnelCurrentColour;

    bool drawTunnel = false;
    bool eraseText = false;
    float transitionAdvance = 0.f;
    float globalEndingOpacity = 1.f;
    bool tunnelBeat = false;

    int width, height;
    FinalDemo *engine;
    float *cosineTable, *sineTable;
    const int mathTableSize = 1024;
};