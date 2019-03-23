#include "FinalDemo.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"
#include "../Utils/Fast.h"
#include <climits>
#include <cmath>

#include <stdio.h>
#include <math.h>

/* This routine will be called by the PortAudio engine when audio is needed.
** It may called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
static int audioCallback(const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo *timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void *userData)
{
    float *out = (float *)outputBuffer;
    static long int currentCount = 0;
    for (unsigned long i = 0; i < framesPerBuffer; i++)
    {
        currentCount++;
        static float old = 0;
        float now = (Fast::Rand() / float(ULONG_MAX)) * 2 - 1;
        float used = now * 0.025 + old * 0.975; //low pass :D

        *out++ = GetSineWaveValue(440, 44100, currentCount) * 0.5; //used;  /* left */
        *out++ = 0;                                                    //used;  /* right */

        old = used;
    }
    return 0;
}

float GetSquaredWaveValue(int frequency, int sampleRate, long int currentCount)
{
    int steps = sampleRate / frequency;
    if (currentCount % steps < steps * 0.5)
    {
        return 1.f;
    }
    return -1.f;
}

float GetSawtoothWaveValue(int frequency, int sampleRate, long int currentCount)
{
    int steps = sampleRate / frequency;
    float percentage = currentCount % steps / float(steps);
    return percentage * 2 - 1.f;
}

float GetTriangleWaveValue(int frequency, int sampleRate, long int currentCount)
{
    int steps = sampleRate / frequency;
    float percentage = currentCount % steps / float(steps);
    if (percentage < 0.5f)
    {
        return percentage * 4 - 2.f;
    }
    return (1 - percentage) * 4 - 2.f;
}

float GetSineWaveValue(int frequency, int sampleRate, long int currentCount)
{
    int steps = sampleRate / frequency;
    float percentage = currentCount % steps / float(steps);
    return sin(2 * Fast::PI * percentage);
}

bool FinalDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    GenerateGrid(vertexPerWidth, vertexPerDepth, vertexDistance);
    GeneratePerspectiveProjection(grid);

    InitAudio();

    return true;
}

bool FinalDemo::Destroy()
{
    CloseAudio();

    return true;
}

void FinalDemo::InitAudio()
{
    Pa_Initialize();
    Pa_OpenDefaultStream(&stream, INPUT_CHANNELS, OUTPUT_CHANNELS, paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER, audioCallback, 0);
    Pa_StartStream(stream);
}

void FinalDemo::CloseAudio()
{
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
}

bool FinalDemo::Update(float deltaTime)
{
    /** Fire 
    ClearScreen(Pixel(0));
    for (int i = width * (height - 1); i >= 0; i--)
    {
        int sum = width + i;
        sum = screenMapping[i] = (screenMapping[sum + 1] + screenMapping[sum] + screenMapping[sum - 1]) / (3.03 + fireIntensity) + (Fast::Rand() % 4 == 0 ? 2 : 0);
        pixels[i] = colourMap[sum];
    }**/

    /** Geometry
    **/
    EraseObject(grid);
    ApplyObjectTransformations(deltaTime);
    GeneratePerspectiveProjection(grid);
    RenderObject(grid);
    UndoObjectTransformations(deltaTime);
    return true;
}

void FinalDemo::ApplyObjectTransformations(float deltaTime)
{
    phase += 1 * deltaTime;
    TranslateObject(grid, Point3D(width / 2 - (vertexPerWidth * vertexDistance) / 2, height * 0.75f, -550));
    ApplyWaveTransformation(grid, 100, 1.5, deltaTime);
}

void FinalDemo::UndoObjectTransformations(float deltaTime)
{
    ApplyWaveTransformation(grid, -100, 1.5, deltaTime);
    TranslateObject(grid, Point3D(-width / 2 + (vertexPerWidth * vertexDistance) / 2, -height * 0.75f, +550));
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

    //Insert indexes for far to close, so we don't have problems when painting
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
            grid.colours.push_back(Pixel(0, 0, 125) + Pixel(255, 255, 125) * (1 - (wave + 1) * 0.5f));
        }
    }
}