#pragma once

#include <vector>
#include <utility>
#include "../Utils/Point2D.h"
#include "../Utils/Point3D.h"
#include "../Utils/Pixel.h"

struct Object3D
{
    std::vector<Point3D> points;
    std::vector<Pixel> colours;
    std::vector<Point2D> indexes;
    std::vector<Point2D> projectedPoints;
};