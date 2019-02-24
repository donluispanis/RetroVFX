#pragma once

#include <vector>
#include "../Utils/Point2D.h"
#include "../Utils/Point3D.h"

struct Object3D
{
    std::vector<Point3D> points;
    std::vector<Point2D> indexes;
    std::vector<Point2D> projectedPoints;
};