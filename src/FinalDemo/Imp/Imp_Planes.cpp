#include "Imp_Includes.h"

struct waypoint
{
    float x, y, ang, scale, time;
};

std::deque<waypoint> waypoints;

void FinalDemo::InitPlanes()
{
    texWidth = 2000;
    texHeight = 2000;
    texture = new Pixel[texWidth * texHeight];
    Pixel *auxTexture = new Pixel[texWidth * texHeight];

    for (int i = 0, n = texWidth * texHeight; i < n; i++)
    {
        auxTexture[i] = Pixel(255);
    }

    DrawCharactersOnMap(auxTexture, texWidth, Pixel(0), 10, 1900, "a cpu is so slow...", 1);
    DrawCharactersOnMap(auxTexture, texWidth, Pixel(0), 1000, 1400, "a cpu is not for graphics...", 1);
    DrawCharactersOnMap(auxTexture, texWidth, Pixel(0), 1500, 1000, "wait... am i dreaming?", 1);
    DrawCharactersOnMap(auxTexture, texWidth, Pixel(0), 500, 800, "is this heaven?", 1);
    DrawCharactersOnMap(auxTexture, texWidth, Pixel(0), 1500, 400, "can't be true...", 1);

    for (int j = 0; j < texHeight; j++)
    {
        const int finalHeight = j * texWidth;

        for (int i = 0; i < texWidth; i++)
        {
            texture[finalHeight + i] = auxTexture[finalHeight + (texWidth - i - 1)];
        }
    }

    delete[] auxTexture;

    textureScale = 40.f;
    cameraAngle = -Fast::PI;
    cameraPosition.X = 1965;
    cameraPosition.Y = 2061;

    waypoints.push_back({1945, 2061, -Fast::PI, 40, 7});
    waypoints.push_back({1940, 1954, -Fast::PI, 23, 1});
    waypoints.push_back({1003, 1529, -3.7f, 40, 7});
    waypoints.push_back({910, 1470, -Fast::PI, 25, 1});
    waypoints.push_back({516, 1124, -4.f, 40, 7});
    waypoints.push_back({446, 1080, -Fast::PI, 40, 1});
    waypoints.push_back({1414, 693, -0.4f, 20, 3.5});
    waypoints.push_back({1461, 850, -Fast::PI, 20, 3.5});
    waypoints.push_back({1431, 800, -Fast::PI, 15, 0.5});
    waypoints.push_back({543, 462, -4.07f, 48, 0.5});
    waypoints.push_back({517, 442, -4.07f, 22, 5});
    waypoints.push_back({525, 403, -4.7f, 3, 5});
    waypoints.push_back({373, 405, -4.7, 0.1, 5});
}

void FinalDemo::ClosePlanes()
{
    delete[] texture;
}

void FinalDemo::UpdatePlanes(float deltaTime)
{
    static bool clearScreen = false;

    if (!clearScreen)
    {
        clearScreen = true;
        ClearScreen(Pixel(255));
    }

    UpdatePath(deltaTime);

    static const int fieldOfView = 500;

    float cosine = cosf(cameraAngle);
    float sine = sinf(cameraAngle);

    for (int j = 1, nh = height / 2; j < nh; j++)
    {
        const int totalHeight = (j + nh) * width;
        const int totalHeight1 = (nh - j) * width;
        const float depth = j;

        for (int i = -width / 2, nw = width / 2; i < nw; i++)
        {
            if (j < 50 && accumulatedTime < START_PLANES + 30.f)
            {
                pixels[totalHeight + (i + nw)] = Pixel(255);
                pixels[totalHeight1 + (i + nw)] = Pixel(255);
                continue;
            }

            Point2D projectedPoint(i / (float)depth, fieldOfView / (float)depth);
            projectedPoint *= textureScale;

            Point2D rotatedPoint(projectedPoint.X * cosine - projectedPoint.Y * sine,
                                 projectedPoint.X * sine + projectedPoint.Y * cosine);

            if (rotatedPoint.Y + cameraPosition.Y < 0 || rotatedPoint.Y + cameraPosition.Y > texHeight)
            {
                continue;
            }
            if (rotatedPoint.X + cameraPosition.X < 0 || rotatedPoint.X + cameraPosition.X > texWidth)
            {
                continue;
            }

            Pixel colour = texture[(int(rotatedPoint.Y + cameraPosition.Y) % texHeight) * texWidth +
                                   int(rotatedPoint.X + cameraPosition.X) % texWidth];

            pixels[totalHeight + (i + nw)] = colour;
            pixels[totalHeight1 + (i + nw)] = colour;
        }
    }

    ClearScreen(0, height / 2 - 1, width, height / 2 + 2, Pixel(0));
}

void FinalDemo::UpdatePath(float deltaTime)
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

void FinalDemo::DrawCharactersOnMap(Pixel *map, int width, const Pixel &colour, int x, int y, const char *characters, int scale)
{
    std::string txt(characters);
    for (auto &c : txt)
    {
        c = toupper(c);
    }

    for (auto c : txt)
    {
        DrawCharacterOnMap(map, width, colour, x, y, c, scale);
        x += 6 * scale;
    }
}

void FinalDemo::DrawCharacterOnMap(Pixel *map, int width, const Pixel &colour, int x, int y, char character, int scale)
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