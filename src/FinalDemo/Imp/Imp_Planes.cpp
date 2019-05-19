#include "Imp_Includes.h"

void FinalDemo::InitPlanes()
{
    texWidth = 2000;
    texHeight = 2000;
    texture = new Pixel[texWidth * texHeight];

    DrawCharactersOnPlanesMap(texture, texWidth, Pixel(255), 10, 10, "asdfghjkln", 30);
    DrawCharactersOnPlanesMap(texture, texWidth, Pixel(255), 10, 200, "qwertyuiou", 30);
    DrawCharactersOnPlanesMap(texture, texWidth, Pixel(255), 10, 400, "eeeeeeeeee", 30);
    DrawCharactersOnPlanesMap(texture, texWidth, Pixel(255), 10, 600, "ssssssssss", 30);
    DrawCharactersOnPlanesMap(texture, texWidth, Pixel(255), 10, 800, "aaaaaaaaaa", 30);
    DrawCharactersOnPlanesMap(texture, texWidth, Pixel(255), 10, 1000, "cccccccccc", 30);
    DrawCharactersOnPlanesMap(texture, texWidth, Pixel(255), 10, 1200, "asdfghjkln", 30);
    DrawCharactersOnPlanesMap(texture, texWidth, Pixel(255), 10, 1400, "asdasffass", 30);
    DrawCharactersOnPlanesMap(texture, texWidth, Pixel(255), 10, 1600, "rewrewrewr", 30);
    DrawCharactersOnPlanesMap(texture, texWidth, Pixel(255), 10, 1800, "uityuyuyyu", 30);
}

void FinalDemo::ClosePlanes()
{
    delete [] texture;
}

void FinalDemo::UpdatePlanes(float deltaTime)
{
    static const int fieldOfView = 500;
    static float cameraAngle = 0.f;
    static float textureScale = 20.f;
    static Point2D cameraPosition;

    float cosine = cosf(cameraAngle);
    float sine = sinf(cameraAngle);

    for (int j = 0, nh = height / 2; j < nh; j++)
    {
        const int totalHeight = (j  + nh) * width;

        for (int i = -width / 2, nw = width / 2; i < nw; i++)
        {
            Point2D projectedPoint(i / (float)j, fieldOfView / (float)j);
            projectedPoint *= textureScale;

            Point2D rotatedPoint(projectedPoint.X * cosine - projectedPoint.Y * sine,
                                 projectedPoint.X * sine + projectedPoint.Y * cosine);

            Pixel colour = texture[Fast::Abs((int(rotatedPoint.Y + cameraPosition.Y) % texHeight) * texWidth +
                                             int(rotatedPoint.X + cameraPosition.X) % texWidth)];

            pixels[totalHeight + (i + nw)] = colour;
        }
    }
}

void FinalDemo::DrawCharactersOnPlanesMap(Pixel *map, int width, const Pixel &colour, int x, int y, const char *characters, int scale)
{
    std::string txt(characters);
    for (auto &c : txt)
    {
        c = toupper(c);
    }

    for (auto c : txt)
    {
        DrawCharacterOnPlanesMap(map, width, colour, x, y, c, scale);
        x += 6 * scale;
    }
}

void FinalDemo::DrawCharacterOnPlanesMap(Pixel *map, int width, const Pixel &colour, int x, int y, char character, int scale)
{
    if (character < 0 || character == ' ')
    {
        return;
    }

    const char *c = Characters::GetCharactersMap()[character];

    for (int i = x; i < x + 5 * scale; i++)
    {
        for (int j = y; j < y + 5 * scale; j++)
        {
            int offsetX = (i - x) / scale;
            int offsetY = (j - y) / scale;

            if (c[offsetY * 5 + offsetX] != ' ')
            {
                map[j * width + i] = colour;
            }
        }
    }
}