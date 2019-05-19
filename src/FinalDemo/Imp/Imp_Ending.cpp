#include "Imp_Includes.h"

void FinalDemo::InitEnding()
{
    start = {-200.f, height / 2 - 1.f};
    end = {width + 200.f, height / 2 - 1.f};
}

void FinalDemo::CloseEnding()
{
}

void FinalDemo::UpdateEnding(float deltaTime)
{
    if (Fast::Abs(start.X - end.X) > 3.f)
    {
        RenderLine(start.X, start.Y, end.X, end.Y, Pixel(255), 4);

        static float rotation = 0.f;
        rotation += deltaTime * Fast::PI * 0.00025;

        start = start - Point2D(width / 2, height / 2);
        end = end - Point2D(width / 2, height / 2);
        start.X = start.X * cos(rotation) - start.Y * sin(rotation);
        start.Y = start.Y * cos(rotation) + start.X * sin(rotation);
        end.X = end.X * cos(rotation) - end.Y * sin(rotation);
        end.Y = end.Y * cos(rotation) + end.X * sin(rotation);
        start = start + Point2D(width / 2, height / 2);
        end = end + Point2D(width / 2, height / 2);

        RenderLine(start.X, start.Y, end.X, end.Y, Pixel(0), 4);
    }
    else
    {
        static const int halfWidth = width / 2;
        static float advance = 0.f;

        if (advance < halfWidth + 5)
        {
            ClearScreen(halfWidth - advance, 0, halfWidth, height, Pixel(0));
            ClearScreen(halfWidth, 0, halfWidth + advance, height, Pixel(0));
            advance += 128 * deltaTime;
        }
        else
        {
            static float opacity = 0.f;

            if(opacity > 1.f)
            {
                opacity = 1.f;
            }

            RenderText("Developed by", 280, 235, 10, Pixel(255) * opacity);
            RenderText("Luis gonzalez aracil", 40, 335, 10, Pixel(255) * opacity);
            RenderText("(c) 2018", 400, 435, 10, Pixel(255) * opacity);
            opacity += 0.5 * deltaTime;
        }
    }
}