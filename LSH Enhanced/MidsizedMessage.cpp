#pragma once

#include <stdio.h>
#include <vector>
#include <string>
#include <typeinfo>
#include "script.h"
#include "MidsizedMessage.h"
#include "Debug.h"

namespace UI::Scaleforms
{
	void MidsizedMessage::Load()
	{
		int start = GAMEPLAY::GET_GAME_TIMER();
		int time = 2000;
		Handle = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MIDSIZED_MESSAGE");
		DEBUG::Debug::PrintToLog("Requesting GFX: MIDSIZED_MESSAGE.");
		while (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(Handle))
		{
			if (GAMEPLAY::GET_GAME_TIMER() > start + time)
			{
				DEBUG::Debug::PrintToLog("Timed out while loading GFX: MIDSIZED_MESSAGE.");
				return;
			}
			WAIT(0);
		}
		DEBUG::Debug::PrintToLog("Successfully loaded GFX: MIDSIZED_MESSAGE.");
	}

	void MidsizedMessage::Dispose()
	{
		if (GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(Handle))
		{
			GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&Handle);
			Handle = 0;
			DEBUG::Debug::PrintToLog("Successfully disposed GFX: MIDSIZED_MESSAGE.");
		}
	}

	void MidsizedMessage::Show(char* title, char* description, int color)
	{
		Load();

		// make sure MP audio data is loaded
		if (invoke<bool>(0x544810ED9DB6BBE6)) /* HAS_LOADED_MP_DATA_SET */
		{

		}

		AUDIO::PLAY_SOUND_FRONTEND(-1, "Shard_Appear", "GTAO_FM_Events_Soundset", false);
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(Handle, "SHOW_SHARD_MIDSIZED_MESSAGE");
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_STRING(title);
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_STRING(description);
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(color);
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_BOOL(false);
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_BOOL(true);
		GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION();
		int start = GAMEPLAY::GET_GAME_TIMER();
		int time = 8000;
		while (GAMEPLAY::GET_GAME_TIMER() < start + time)
		{
			GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(Handle, 255, 255, 255, 255, 0);
			WAIT(0);
		}
		AUDIO::PLAY_SOUND_FRONTEND(-1, "Shard_Disappear", "GTAO_FM_Events_Soundset", false);
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(Handle, "SHARD_ANIM_OUT");
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(0);
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_FLOAT(0.5f);
		GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION();
		start = GAMEPLAY::GET_GAME_TIMER();
		time = 500;
		while (GAMEPLAY::GET_GAME_TIMER() < start + time)
		{
			GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(Handle, 255, 255, 255, 255, 0);
			WAIT(0);
		}
		Dispose();
	}
}