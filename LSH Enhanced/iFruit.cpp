#include "iFruit.h"

void UI::Scaleforms::LoadScaleform()
{
   ScaleformHandle = GRAPHICS::REQUEST_SCALEFORM_MOVIE((char*)gfxMovie.ctr());
   while (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(ScaleformHandle)) WAIT(0);
}