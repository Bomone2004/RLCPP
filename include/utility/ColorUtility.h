#pragma once
#include "raylib.h"

namespace Aiv_Color
{
    Color GetRandomColor()
    {
        Color color;

        color.r = GetRandomValue(10,255);
        color.g = GetRandomValue(10,255 - color.r);
        color.b = GetRandomValue(10,255 - color.g);
        color.a = 255;

        return color;
    }
}