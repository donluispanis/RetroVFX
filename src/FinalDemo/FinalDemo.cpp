#include "FinalDemo.h"
#include "../ClassicDemoTemplate/WindowManager/IWindowManager.h"
#include "../Utils/Fast.h"
#include <climits>
#include <cmath>

#include <stdio.h>
#include <math.h>
#define NUM_SECONDS   (4)
#define SAMPLE_RATE   (44100)

typedef struct
{
    float left_phase;
    float right_phase;
}
paTestData;

/* This routine will be called by the PortAudio engine when audio is needed.
** It may called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
static int patestCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
    /* Cast data passed through stream to our structure. */
    paTestData *data = (paTestData*)userData;
    float *out = (float*)outputBuffer;
    unsigned int i;
    (void) inputBuffer; /* Prevent unused variable warning. */

    for( i=0; i<framesPerBuffer; i++ )
    {
        *out++ = data->left_phase;  /* left */
        *out++ = data->right_phase;  /* right */
        /* Generate simple sawtooth phaser that ranges between -1.0 and 1.0. */
        data->left_phase += 0.001f;
        /* When signal reaches top, drop back down. */
        if( data->left_phase >= 1.0f ) data->left_phase -= 2.0f;
        /* higher pitch so we can distinguish left and right. */
        data->right_phase += 0.003f;
        if( data->right_phase >= 1.0f ) data->right_phase -= 2.0f;
    }
    return 0;
}

/*******************************************************************/
static paTestData data;


bool FinalDemo::Init()
{
    windowManager = GetWindowManager();
    windowManager->SetFramerateToShow(true);
    pixels = windowManager->GetScreenPixels();
    width = windowManager->GetWidth();
    height = windowManager->GetHeight();

    GenerateGrid(vertexPerWidth, vertexPerDepth, vertexDistance);
    GeneratePerspectiveProjection(grid);

    printf("PortAudio Test: output sawtooth wave.\n");
    /* Initialize our data for use by callback. */
    data.left_phase = data.right_phase = 0.0;
    /* Initialize library before making any other calls. */
    int err = Pa_Initialize();
    if( err != paNoError ) printf("shit1\n");

    /* Open an audio I/O stream. */
    err = Pa_OpenDefaultStream( &stream,
                                0,          /* no input channels */
                                2,          /* stereo output */
                                paFloat32,  /* 32 bit floating point output */
                                SAMPLE_RATE,
                                256,        /* frames per buffer */
                                patestCallback,
                                &data );
    if( err != paNoError ) printf("shit2\n");

    err = Pa_StartStream( stream );
    if( err != paNoError ) printf("shit3\n");

    return true;
}

bool FinalDemo::Destroy()
{
    int err = Pa_StopStream( stream );
    if( err != paNoError ) printf("shit4\n");
    err = Pa_CloseStream( stream );
    if( err != paNoError ) printf("shit5\n");
    Pa_Terminate();
    printf("Test finished.\n");
    return true;
}

bool FinalDemo::Update(float deltaTime)
{
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
    TranslateObject(grid, Point3D(width/2 - (vertexPerWidth * vertexDistance) / 2, height * 0.75f,-550));
    ApplyWaveTransformation(grid, 100, 4, deltaTime);
}

void FinalDemo::UndoObjectTransformations(float deltaTime)
{
    ApplyWaveTransformation(grid, -100, 4, deltaTime);
    TranslateObject(grid, Point3D(-width/2 + (vertexPerWidth * vertexDistance) / 2, -height * 0.75f,+550));
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
        if(i < size - vertexPerWidth)
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
            grid.colours.push_back(Pixel(0,0,125) + Pixel(255, 255, 125) * (1 - (wave + 1) * 0.5f));

        }
    }
}