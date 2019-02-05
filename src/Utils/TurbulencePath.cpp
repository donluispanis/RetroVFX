#include "TurbulencePath.h"
#include "Fast.h"

TurbulencePath::TurbulencePath(float* sineTable, float *cosineTable, int mathTableSize)
{
    this->sineTable = sineTable;
    this->cosineTable = cosineTable;
    this->mathTableSize = mathTableSize;
}

void TurbulencePath::CreateTurbulencePath(float pathVelocity, int pathRadius, int pathComplexity)
{
    this->pathVelocity = pathVelocity;
    this->pathRadius = pathRadius;
    this->pathComplexity = pathComplexity;

    for(int i = 0; i < pathComplexity; i++)
    {
        paths.push_back(Path{
                (pathRadius * 2) / (i + 2),
                (int)Fast::Rand() % mathTableSize,
                i % 2 == 0 ? 1 : -1,
                0});
    }
}

void TurbulencePath::UpdateTurbulencePath(float deltaTime, float &pathX, float &pathY)
{
    pathX = 0.f;
    pathY = 0.f;

    for (int i = 0, n = paths.size(); i < n; i++)
    {
        Path &p = paths[i];
        p.advance += deltaTime * 0.1;
        int waveAmplitude = (p.advance * p.radius * pathVelocity) / float(i + 2);
        pathX += cosineTable[int(waveAmplitude + p.phase) % mathTableSize];
        pathY += sineTable[int(waveAmplitude + p.phase) % mathTableSize];
    }

    pathX /= (float)pathComplexity;
    pathY /= (float)pathComplexity;

    pathX *= pathRadius;
    pathY *= pathRadius;
}