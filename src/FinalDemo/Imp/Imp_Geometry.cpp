#include "Imp_Includes.h"

void FinalDemo::InitGeometry()
{
    GenerateGrid(vertexPerWidth, vertexPerDepth, vertexDistance);
    GeneratePerspectiveProjection(grid);
    ApplyWaveTransformation(grid, 0, 1.5, 0);
}

void FinalDemo::CloseGeometry()
{
}

void FinalDemo::UpdateGeometry(float deltaTime)
{
    EraseObject(grid);
    ApplyObjectTransformations(deltaTime);
    GeneratePerspectiveProjection(grid);
    RenderObject(grid);
    UndoObjectTransformations(deltaTime);
}

void FinalDemo::ApplyObjectTransformations(float deltaTime)
{
    phase += 1 * deltaTime;
    static float aux = 0;
    aux += 0.0;
    TranslateObject(grid, Point3D(width / 2 + aux, height / 2 - aux, 0));
    ///ApplyWaveTransformation(grid, 0, 1.5, deltaTime);
}

void FinalDemo::UndoObjectTransformations(float deltaTime)
{
    static float aux = 0;
    aux += 0.0;
    //ApplyWaveTransformation(grid, 0, 1.5, deltaTime);
    TranslateObject(grid, Point3D(-width / 2 - aux, -height / 2 + aux, 0));
}

void FinalDemo::GenerateGrid(int vertexPerWidth, int vertexPerDepth, float vertexDistance)
{
    const int size = vertexPerWidth * vertexPerDepth;

    //Generate vertex for the grid
    for (float j = 0; j < vertexPerDepth; j++)
    {
        for (float i = 0; i < vertexPerWidth; i++)
        {
            grid.points.emplace_back(i * vertexDistance, 0, j * vertexDistance);
        }
    }

    //Insert indexes from far to close, so we don't have problems when painting
    for (float i = size - 1; i >= 0; i--)
    {
        if ((int(i + 1) % vertexPerWidth) != 0)
        {
            grid.indexes.emplace_back(Point2D{i, i + 1});
            grid.indexes.emplace_back(Point2D{i, i - 1});
        }
        if (i < size - vertexPerWidth)
        {
            grid.indexes.emplace_back(Point2D{i, i + vertexPerWidth});
            grid.indexes.emplace_back(Point2D{i, i - vertexPerWidth});
        }
    }

    grid.points.clear();

    for (float j = 0; j < vertexPerDepth; j++)
    {
        for (float i = 0; i < vertexPerWidth; i++)
        {
            grid.points.push_back(GetPointInSphereFromPlane(i, j, vertexPerWidth, 300.f));
        }
    }
}

void FinalDemo::GeneratePerspectiveProjection(Object3D &object)
{
    const float depthFactor = 0.001;
    const int halftWidth = width / 2;
    const int halftHeight = height / 2;

    object.projectedPoints.clear();

    for (unsigned int i = 0, n = object.points.size(); i < n; i++)
    {
        Point3D p = object.points[i];
        float depth = (p.Z != 0.f) ? (p.Z * depthFactor + 1.f) : 1.f; //Depth can't be 0

        object.projectedPoints.push_back({((p.X - halftWidth) / depth) + halftWidth, ((p.Y - halftHeight) / depth) + halftHeight});
        //Move points to the origin, then apply depth by dividing and then move points back to where they were
    }
}

void FinalDemo::RenderObject(Object3D object)
{
    for (int i = 0, n = object.indexes.size(); i < n; i++)
    {
        Point2D indexPair = object.indexes[i];
        Point2D startPoint = object.projectedPoints[indexPair.X];
        Point2D endPoint = object.projectedPoints[indexPair.Y];

        RenderLine(startPoint.X, startPoint.Y, endPoint.X, endPoint.Y, object.colours[indexPair.X], object.colours[indexPair.Y], 2);
        //RenderDot(startPoint.X, startPoint.Y, Pixel(255), 4);
        //RenderDot(endPoint.X, endPoint.Y, Pixel(255), 4);
    }
}

void FinalDemo::EraseObject(Object3D object)
{
    for (int i = 0, n = object.indexes.size(); i < n; i++)
    {
        Point2D indexPair = object.indexes[i];
        Point2D startPoint = object.projectedPoints[indexPair.X];
        Point2D endPoint = object.projectedPoints[indexPair.Y];

        RenderLine(startPoint.X, startPoint.Y, endPoint.X, endPoint.Y, Pixel(0), 2);
    }
}

void FinalDemo::TranslateObject(Object3D &object, Point3D offset)
{
    for (unsigned int i = 0, n = object.points.size(); i < n; i++)
    {
        object.points[i] += offset;
    }
}

void FinalDemo::ApplyWaveTransformation(Object3D &object, float amplitude, float wavelength, float deltaTime)
{
    grid.colours.clear();
    for (float j = 0; j < vertexPerDepth; j++)
    {
        for (float i = 0; i < vertexPerWidth; i++)
        {
            int index = j * vertexPerWidth + i;
            float wave = sin((j + phase) / wavelength);

            grid.points[index].Y += amplitude * wave;
            //grid.colours.push_back(Pixel(0, 0, 125) + Pixel(255, 255, 125) * (1 - (wave + 1) * 0.5f));
            grid.colours.push_back(Pixel(255)); //((grid.points[j * vertexPerDepth + i].Z / 300.f) + 1.f) * 125));
        }
    }
}

float CalculateQuadrant(int posX, int posY, int halfGrid)
{
    const float quarterCircle = Fast::PI / 2.f;
    float quadrant;

    if (posX < halfGrid && posY < halfGrid)
    {
        quadrant = 0.f;
    }
    else if (posX >= halfGrid && posY < halfGrid)
    {
        quadrant = quarterCircle;
    }
    else if (posX >= halfGrid && posY >= halfGrid)
    {
        quadrant = Fast::PI;
    }
    else
    {
        quadrant = quarterCircle * 3.f;
    }

    return quadrant;
}

Point3D FinalDemo::GetPointInSphereFromPlane(const int posX, const int posY, const int gridSize, const float radius)
{
    const int halfGrid = gridSize / 2;

    const int firstQuarterPosX = (posX < gridSize / 2) ? posX : gridSize - posX - 1;
    const int firstQuarterPosY = (posY < gridSize / 2) ? posY : gridSize - posY - 1;

    const int ring = gridSize - 1 - firstQuarterPosX - firstQuarterPosY; //The numbers of rings goes from 1 to gridSize - 1
    const float radiusSign = (ring < halfGrid) ? -1.f : 1.f;

    //top && bottom
    if (ring == 1 || ring == gridSize - 1)
    {
        return Point3D(0.f, radius * radiusSign, 0.f);
    }
    //middle ones
    else
    {
        const int positiveRing = (ring < halfGrid) ? ring : gridSize - ring;
        const float perRingHeight = radius / float(halfGrid - 1);
        float height = perRingHeight * (positiveRing - 1) * radiusSign;

        if (ring == halfGrid)
        {
            height = 0.f;
        }

        const float sine = height / radius;
        const float circleRadius = radius * sqrt(1 - sine * sine); //circleRadius = radius * cos()

        const float quarterCircle = Fast::PI / 2.f;

        float quadrant = CalculateQuadrant(posX, posY, halfGrid);

        const int positiveFirstQuarterPosX = (ring <= halfGrid) ? firstQuarterPosX - (halfGrid - ring) : firstQuarterPosX;
        const float angle = ((positiveFirstQuarterPosX + 1) / float(positiveRing)) * quarterCircle + quadrant;

        Point3D p = Point3D(circleRadius * cos(angle), height, circleRadius * sin(angle));
        return p;
    }
}
