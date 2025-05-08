#include "iFruit.h"

void UI::Scaleforms::LoadScaleform()
{
   int start = GAMEPLAY::GET_GAME_TIMER();
   int time = 4000;
   ScaleformMovieHandle = GRAPHICS::REQUEST_SCALEFORM_MOVIE((char*)gfxMovie.ctr());
   while (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(ScaleformMovieHandle))
   {
       if (GAMEPLAY::GET_GAME_TIMER() > start + time)
       {
           std::string errorS = "ERROR: Timed out while loading Scaleform Movie: " + gfxMovie;
           throw new std::runtime_error(errorS);
       }
       WAIT(0);
   }
}