#pragma once

#include "script.h"

namespace UI::Scaleforms
{
    class MidsizedMessage
    {
    public:
        int Handle;

        void Load();

        void Dispose();

        void Show(char* title, char* description, int color);
    };
}