#include "Imp_Geometry.h"
#include "../../Utils/Fast.h"
#include "../FinalDemo.h"
#include <cmath>

void Imp_Geometry::InitGeometry(int width, int height, FinalDemo* engine)
{
    this->width = width;
    this->height = height;
    this->engine = engine;

    GenerateGrid(vertexPerWidth, vertexPerDepth, vertexDistance);
    GeneratePerspectiveProjection(grid);
    GenerateSphere(vertexPerWidth, 300.f);

    waveAmplitude = 50.f;
    position = Point3D(width / 2 - (vertexPerWidth * vertexDistance) / 2, height * 0.75f, -550);
}

void Imp_Geometry::CloseGeometry()
{
}

void Imp_Geometry::UpdateGeometry(float deltaTime, float accumulatedTime, float startTime)
{
    EraseObject(grid);
    ApplyObjectTransformations(deltaTime);
    GeneratePerspectiveProjection(grid);
    RenderObject(grid);
    UndoObjectTransformations(deltaTime);

	UpdateFadeIn(accumulatedTime, startTime, deltaTime);
	GenerateWaves(accumulatedTime, startTime, deltaTime);
	InterpolateToSphere(accumulatedTime, startTime);
	IncreasePhase(accumulatedTime, startTime, deltaTime);
	DecreaseSphereSize(accumulatedTime, startTime, deltaTime);
	IncreaseSphereSize(accumulatedTime, startTime, deltaTime);
}

void Imp_Geometry::UpdateFadeIn(float accumulatedTime, float startTime, float deltaTime)
{
	if (accumulatedTime > startTime + 2.0f && colourOpacityIn < 1.f)
	{
		colourOpacityIn += 0.2 * deltaTime;
	}
}

void Imp_Geometry::GenerateWaves(float accumulatedTime, float startTime, float deltaTime)
{
	if (accumulatedTime > startTime + 15.f && accumulatedTime < startTime + 20.f)
	{
		waveAmplitudeVelocity += 20 * deltaTime;
		waveAmplitude += waveAmplitudeVelocity * deltaTime;
		phaseVelocity += deltaTime * 5;
	}
	if (accumulatedTime > startTime + 20.f && accumulatedTime < startTime + 25.f)
	{
		waveAmplitudeVelocity -= 50 * deltaTime;
		waveAmplitude += waveAmplitudeVelocity * deltaTime;
		phaseVelocity -= deltaTime * 5;
	}
	if (accumulatedTime > startTime + 25.f && waveAmplitude > 0.f)
	{
		waveAmplitude -= 30 * deltaTime;
	}
}

void Imp_Geometry::InterpolateToSphere(float accumulatedTime, float startTime)
{
	if (accumulatedTime > startTime + 26.f && waveAmplitude <= 0.f)
	{
		float t = 0.f;
		if (t < 1.f)
		{
			t += 0.01;
		}

		Point3D position2(width / 2, height / 2, 0.f);

		position = position * (1.f - t) + position2 * t;

		for (int j = 0; j < vertexPerWidth; j++)
		{
			for (int i = 0; i < vertexPerWidth; i++)
			{
				grid.points[j * vertexPerWidth + i] =
					grid.points[j * vertexPerWidth + i] * (1.f - t) +
					sphere.points[j * vertexPerWidth + i] * t;
			}
		}
	}
}

void Imp_Geometry::IncreasePhase(float accumulatedTime, float startTime, float deltaTime)
{
	if (accumulatedTime > startTime + 40.f && accumulatedTime < startTime + 55.f)
	{
		phaseVelocity += deltaTime * 3;
	}
}

void Imp_Geometry::DecreaseSphereSize(float accumulatedTime, float startTime, float deltaTime)
{
	if (accumulatedTime > startTime + 50.f && accumulatedTime < startTime + 53.f)
	{
		static const std::vector<Point3D> pointsCopy(grid.points);
		static float factor = 1.f;
		factor -= 0.3 * deltaTime;

		for (unsigned int i = 0; i < grid.points.size(); i++)
		{
			grid.points[i] = Point3D(factor, factor, factor) * pointsCopy[i];
		}
	}

	if (accumulatedTime > startTime + 53.f && accumulatedTime < startTime + 55.f)
	{
		static const std::vector<Point3D> pointsCopy(grid.points);
		for (unsigned int i = 0; i < grid.points.size(); i++)
		{
			grid.points[i] = pointsCopy[i];
		}
	}
	if (accumulatedTime > startTime + 53.f && renderLines)
	{
		renderLines = false;
	}
}

void Imp_Geometry::IncreaseSphereSize(float accumulatedTime, float startTime, float deltaTime)
{
	if (accumulatedTime > startTime + 55.f && accumulatedTime < startTime + 60.f)
	{
		static const std::vector<Point3D> pointsCopy(grid.points);
		static float factor = 1.f;
		if (accumulatedTime < startTime + 56.f)
		{
			factor += 20 * deltaTime;
		}
		else if (accumulatedTime < startTime + 58.5f)
		{
			factor += deltaTime * 2;
		}
		else
		{
			factor -= 7.5f * deltaTime;
		}

		for (unsigned int i = 0; i < grid.points.size(); i++)
		{
			grid.points[i] = Point3D(factor, factor, factor) * pointsCopy[i];
		}

		phaseVelocity -= deltaTime * 5;
	}
	if (accumulatedTime > startTime + 70.f && colourOpacityOut > 0.f)
	{
		colourOpacityOut -= 0.3 * deltaTime;
	}
	else if (colourOpacityOut < 0.f)
	{
		colourOpacityOut = 0.f;
	}
}

void Imp_Geometry::ApplyObjectTransformations(float deltaTime)
{
    phase += 1 * deltaTime * phaseVelocity;

    TranslateObject(grid, position);
    ApplyWaveTransformation(grid, waveAmplitude, 1.5, deltaTime);
}

void Imp_Geometry::UndoObjectTransformations(float deltaTime)
{
    ApplyWaveTransformation(grid, -waveAmplitude, 1.5, deltaTime);
    TranslateObject(grid, -position);
}

void Imp_Geometry::GenerateGrid(int vertexPerWidth, int vertexPerDepth, float vertexDistance)
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
        }
        if (i < size - vertexPerWidth)
        {
            grid.indexes.emplace_back(Point2D{i, i + vertexPerWidth});
        }
    }
}

void Imp_Geometry::GenerateSphere(int gridSize, float radius)
{
    for (int j = 0; j < gridSize; j++)
    {
        for (int i = 0; i < gridSize; i++)
        {
            sphere.points.push_back(GetPointInSphereFromPlane(i, j, vertexPerWidth, radius));
        }
    }
}

void Imp_Geometry::GeneratePerspectiveProjection(Object3D &object)
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

void Imp_Geometry::RenderObject(Object3D object)
{
    for (int i = 0, n = object.indexes.size(); i < n; i++)
    {
        Point2D indexPair = object.indexes[i];
        Point2D startPoint = object.projectedPoints[indexPair.X];
        Point2D endPoint = object.projectedPoints[indexPair.Y];

        if (renderLines)
        {
            engine->RenderLine(startPoint.X, startPoint.Y, endPoint.X, endPoint.Y, object.colours[indexPair.X], object.colours[indexPair.Y], 2);
        }
        else
        {
            engine->RenderDot(startPoint.X, startPoint.Y, object.colours[indexPair.X] * colourOpacityOut, 2);
            engine->RenderDot(endPoint.X, endPoint.Y, object.colours[indexPair.Y] * colourOpacityOut, 2);
        }
        
    }
}

void Imp_Geometry::EraseObject(Object3D object)
{
    for (int i = 0, n = object.indexes.size(); i < n; i++)
    {
        Point2D indexPair = object.indexes[i];
        Point2D startPoint = object.projectedPoints[indexPair.X];
        Point2D endPoint = object.projectedPoints[indexPair.Y];

        engine->RenderLine(startPoint.X, startPoint.Y, endPoint.X, endPoint.Y, Pixel(0), 2);
    }
}

void Imp_Geometry::TranslateObject(Object3D &object, Point3D offset)
{
    for (unsigned int i = 0, n = object.points.size(); i < n; i++)
    {
        object.points[i] += offset;
    }
}

void Imp_Geometry::ApplyWaveTransformation(Object3D &object, float amplitude, float wavelength, float deltaTime)
{
    grid.colours.clear();
    for (float j = 0; j < vertexPerDepth; j++)
    {
        for (float i = 0; i < vertexPerWidth; i++)
        {
            int index = j * vertexPerWidth + i;
            float wave = sin((j + phase) / wavelength);

            if(wavelength == 0.f)
            {
                wave = 0.f;
            }

            grid.points[index].Y += amplitude * wave;
            grid.colours.push_back((Pixel(0, 0, 125) + Pixel(255, 255, 125) * (1 - (wave + 1) * 0.5f)) * colourOpacityIn);
        }
    }
}

Point3D Imp_Geometry::GetPointInSphereFromPlane(const int posX, const int posY, const int gridSize, const float radius)
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

float Imp_Geometry::CalculateQuadrant(int posX, int posY, int halfGrid)
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