#include "Imp_Planes.h"
#include "../../Utils/Fast.h"
#include "../FinalDemo.h"
#include <cmath>

void Imp_Planes::InitPlanes(int width, int height, Pixel* pixels, FinalDemo* engine)
{
    this->width =  width;
    this->height = height;
    this->pixels = pixels;
    this->engine = engine;

    texWidth = 2000;
    texHeight = 2000;
    texture = new Pixel[texWidth * texHeight];

	InitialiseTexture();

    textureScale = 40.f;
    cameraAngle = -Fast::PI;
    cameraPosition.X = 1965;
    cameraPosition.Y = 2061;

	InitialiseWaypoints();
}

void Imp_Planes::ClosePlanes()
{
	delete[] texture;
}

void Imp_Planes::InitialiseTexture()
{
	Pixel *auxTexture = new Pixel[texWidth * texHeight];

	for (int i = 0, n = texWidth * texHeight; i < n; i++)
	{
		auxTexture[i] = Pixel(255);
	}

	engine->DrawCharactersOnMap(auxTexture, texWidth, Pixel(0), 10, 1900, "a cpu is so slow...", 1);
	engine->DrawCharactersOnMap(auxTexture, texWidth, Pixel(0), 1000, 1400, "a cpu is not for graphics...", 1);
	engine->DrawCharactersOnMap(auxTexture, texWidth, Pixel(0), 1500, 1000, "wait... am i dreaming?", 1);
	engine->DrawCharactersOnMap(auxTexture, texWidth, Pixel(0), 500, 800, "is this heaven?", 1);
	engine->DrawCharactersOnMap(auxTexture, texWidth, Pixel(0), 1500, 400, "can't be true...", 1);

	for (int j = 0; j < texHeight; j++)
	{
		const int finalHeight = j * texWidth;

		for (int i = 0; i < texWidth; i++)
		{
			texture[finalHeight + i] = auxTexture[finalHeight + (texWidth - i - 1)];
		}
	}

	delete[] auxTexture;
}

void Imp_Planes::InitialiseWaypoints()
{
	waypoints.push_back({ 1945, 2061, -Fast::PI, 40, 7 });
	waypoints.push_back({ 1940, 1954, -Fast::PI, 23, 1 });
	waypoints.push_back({ 1003, 1529, -3.7f, 40, 7 });
	waypoints.push_back({ 910, 1470, -Fast::PI, 25, 1 });
	waypoints.push_back({ 516, 1124, -4.f, 40, 7 });
	waypoints.push_back({ 446, 1080, -Fast::PI, 40, 1 });
	waypoints.push_back({ 1414, 693, -0.4f, 20, 3.5 });
	waypoints.push_back({ 1461, 850, -Fast::PI, 20, 3.5 });
	waypoints.push_back({ 1431, 800, -Fast::PI, 15, 0.5 });
	waypoints.push_back({ 543, 462, -4.07f, 48, 0.5 });
	waypoints.push_back({ 517, 442, -4.07f, 22, 5 });
	waypoints.push_back({ 525, 403, -4.7f, 3, 5 });
	waypoints.push_back({ 373, 405, -4.7, 0.1, 5 });
}

void Imp_Planes::UpdatePlanes(float deltaTime, float accumulatedTime, float startTime)
{
    if (!clearScreen)
    {
        clearScreen = true;
        engine->ClearScreen(Pixel(255));
    }

    UpdatePath(deltaTime);

    float cosine = cosf(cameraAngle);
    float sine = sinf(cameraAngle);

    for (int j = 1, nh = height / 2; j < nh; j++)
    {
        const int totalHeight = (j + nh) * width;
        const int totalHeight1 = (nh - j) * width;
        const float depth = j;

        for (int i = -width / 2, nw = width / 2; i < nw; i++)
        {
			if (ClearScreenCloseToHorizon(i, j, nw, totalHeight, totalHeight1, accumulatedTime, startTime))
			{
				continue;
			}
			
            Point2D projectedPoint(i / (float)depth, fieldOfView / (float)depth);
            projectedPoint *= textureScale;

            Point2D rotatedPoint(projectedPoint.X * cosine - projectedPoint.Y * sine,
                                 projectedPoint.X * sine + projectedPoint.Y * cosine);

			if (IsPointOutOfBounds(rotatedPoint))
			{
				continue;
			}

            Pixel colour = texture[(int(rotatedPoint.Y + cameraPosition.Y) % texHeight) * texWidth +
                                   int(rotatedPoint.X + cameraPosition.X) % texWidth];

            pixels[totalHeight + (i + nw)] = colour;
            pixels[totalHeight1 + (i + nw)] = colour;
        }
    }

    engine->ClearScreen(0, height / 2 - 1, width, height / 2 + 2, Pixel(0));
}

void Imp_Planes::UpdatePath(float deltaTime)
{
	if (waypoints.size() <= 1)
	{
		return;
	}

	float t = 0.f;
	static float accumulator = 0.f;

	accumulator += deltaTime;

	if (accumulator > waypoints.front().time)
	{
		accumulator = 0.f;
		waypoints.pop_front();
	}

	t = accumulator / waypoints.front().time;

	cameraPosition.X = (1.f - t) * waypoints[0].x + t * waypoints[1].x;
	cameraPosition.Y = (1.f - t) * waypoints[0].y + t * waypoints[1].y;
	cameraAngle = (1.f - t) * waypoints[0].ang + t * waypoints[1].ang;
	textureScale = (1.f - t) * waypoints[0].scale + t * waypoints[1].scale;
}

bool Imp_Planes::ClearScreenCloseToHorizon(int i, int j, int width, int totalHeight, int totalHeight1, float accumulatedTime, float startTime)
{
	if (j < 50 && accumulatedTime < startTime + 30.f)
	{
		pixels[totalHeight + (i + width)] = Pixel(255);
		pixels[totalHeight1 + (i + width)] = Pixel(255);
		return true;
	}
	return false;
}

bool Imp_Planes::IsPointOutOfBounds(Point2D &rotatedPoint)
{
	if (rotatedPoint.Y + cameraPosition.Y < 0 || rotatedPoint.Y + cameraPosition.Y > texHeight)
	{
		return true;
	}
	if (rotatedPoint.X + cameraPosition.X < 0 || rotatedPoint.X + cameraPosition.X > texWidth)
	{
		return true;
	}
	return false;
}