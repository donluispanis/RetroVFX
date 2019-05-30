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
    void UpdateEnding(float deltaTime, float accumulatedTime, float startTime, bool &tunnelBeat);
    void CloseEnding();

private:
    void InitDefaultCircleValues();
    void InitTunnelColours();
    void InitTurbulencePath();

    void DrawCircle(const Circle &c);
    float CalculateOpacity(const float radius);
    void UpdateCircle(Circle &c, float deltaTime);
    void EraseCircle(const Circle &circle);
    void AddCircle();
    void UpdateCircleQueue(float deltaTime);
    void PopulateCircleQueue();

    void UpdateRotatingLine(float deltaTime);
    void EraseText(int textDisplacementX, int textDisplacementY);
    void TransitionToBlackScreen(float deltaTime);
    void UpdateTunnel(float deltaTime, bool &tunnelBeat);
    void DrawText(float deltaTime);
    void FadeOut(float deltaTime);

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

    float accumulator = -6.f;
    float opacity = 0.f;
    int textDisplacementX = 0, textDisplacementY = 0;

    int width, height;
    int halfWidth;
    FinalDemo *engine;
    float *cosineTable, *sineTable;
    const int mathTableSize = 1024;
};