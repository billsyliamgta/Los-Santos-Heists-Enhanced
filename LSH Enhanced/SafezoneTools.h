#pragma once

#include <cmath>
#include <utility>
#include "Screen.h"
#include "script.h"

inline Extensions::PointF SafezoneBounds() {
    float t = GRAPHICS::GET_SAFE_ZONE_SIZE();
    double g = std::round(static_cast<double>(t) * 100) - 90;
    g = 10 - g;
    float screenw = UI::Screen::ScaledWidth();
    float screenh = UI::Screen::Height;
    float ratio = screenw / screenh;
    float wmp = ratio * 5.4f;
    return Extensions::PointF(static_cast<int>(std::round(g * wmp)), static_cast<int>(std::round(g * 5.4f)));
}

inline Extensions::SizeF ResolutionMaintainRatio()
{
    int screenw = UI::Screen::Resolution().Width;
    int screenh = UI::Screen::Resolution().Height;
    float ratio = static_cast<float>(screenw) / screenh;
    float width = 1080.0f * ratio;
    return Extensions::SizeF(width, 1080.0f);
}