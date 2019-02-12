#include "ColourStampGradients.h"

const std::vector<ColourStamp> ColourStampGradients::FIRE = std::vector<ColourStamp>(
    {ColourStamp{0.0f, Pixel{0, 0, 0}},
     ColourStamp{0.02f, Pixel{0, 0, 0}},
     ColourStamp{0.1f, Pixel{255, 0, 0}},
     ColourStamp{0.2f, Pixel{255, 125, 0}},
     ColourStamp{0.4f, Pixel{255, 255, 0}},
     ColourStamp{0.5f, Pixel{255, 255, 255}},
     ColourStamp{1.0f, Pixel{255, 255, 255}}});

const std::vector<ColourStamp> ColourStampGradients::COOL = std::vector<ColourStamp>(
    {ColourStamp{0.0f, Pixel{0, 0, 0}},
     ColourStamp{0.02f, Pixel{0, 0, 0}},
     ColourStamp{0.1f, Pixel{123, 245, 231}},
     ColourStamp{0.2f, Pixel{0, 231, 45}},
     ColourStamp{0.4f, Pixel{234, 123, 231}},
     ColourStamp{0.5f, Pixel{231, 32, 126}},
     ColourStamp{1.0f, Pixel{236, 231, 54}}});

const std::vector<ColourStamp> ColourStampGradients::VINTAGE = std::vector<ColourStamp>(
    {ColourStamp{0.0f, Pixel{0, 0, 0}},
     ColourStamp{0.02f, Pixel{0, 0, 0}},
     ColourStamp{0.1f, Pixel{123, 123, 123}},
     ColourStamp{0.2f, Pixel{255, 255, 255}},
     ColourStamp{1.0f, Pixel{255, 255, 255}}});

const std::vector<ColourStamp> ColourStampGradients::RAINBOW = std::vector<ColourStamp>(
    {ColourStamp{0.0f, Pixel{255, 0, 0}},
     ColourStamp{0.16f, Pixel{255, 255, 0}},
     ColourStamp{0.33f, Pixel{0, 255, 0}},
     ColourStamp{0.5f, Pixel{0, 255, 255}},
     ColourStamp{0.66f, Pixel{0, 0, 255}},
     ColourStamp{0.83f, Pixel{255, 0, 255}},
     ColourStamp{1.0f, Pixel{255, 0, 0}}});

const std::vector<ColourStamp> ColourStampGradients::PLASMA = std::vector<ColourStamp>(
    {ColourStamp{0.0f, Pixel{0, 0, 0}},
     ColourStamp{0.1f, Pixel{0, 255, 0}},
     ColourStamp{0.2f, Pixel{255, 255, 0}},
     ColourStamp{0.5f, Pixel{255, 255, 255}},
     ColourStamp{1.0f, Pixel{255, 255, 255}}});