#pragma once

#include "RobberyCompleteShard.h"
#include "Debug.h"

void UI::Scaleforms::RobberyCompleteShard::Load()
{
	int start = GAMEPLAY::GET_GAME_TIMER();
	int time = 2000;
	Handle = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_BIG_MESSAGE_FREEMODE");
	DEBUG::Debug::PrintToLog("Requesting GFX: MP_BIG_MESSAGE_FREEMODE.");
	while (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(Handle))
	{
		if (GAMEPLAY::GET_GAME_TIMER() > start + time)
		{
			DEBUG::Debug::PrintToLog("Timed out while loading GFX: MP_BIG_MESSAGE_FREEMODE.");
			return;
		}
		WAIT(0);
	}
	DEBUG::Debug::PrintToLog("Successfully loaded GFX: MP_BIG_MESSAGE_FREEMODE.");
}

void UI::Scaleforms::RobberyCompleteShard::Dispose()
{
	if (GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(Handle))
	{
		GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&Handle);
		Handle = 0;
		DEBUG::Debug::PrintToLog("Successfully disposed GFX: MP_BIG_MESSAGE_FREEMODE.");
	}
}

float UI::Scaleforms::RobberyCompleteShard::func_14607(float fParam0)
{
	return fParam0 * 0.0009259259f;
}

float UI::Scaleforms::RobberyCompleteShard::func_14613(float fParam0)
{
	return fParam0 * 0.0013888889f;
}

float UI::Scaleforms::RobberyCompleteShard::func_14612()
{
	float result = 1;
	if (GAMEPLAY::IS_PC_VERSION())
	{

	}
	return result;
}

void UI::Scaleforms::RobberyCompleteShard::Show()
{
	AUDIO::RELEASE_NAMED_SCRIPT_AUDIO_BANK("HUD_123_GO");
	AUDIO::REQUEST_SCRIPT_AUDIO_BANK("HUD_321_GO", false);
	WAIT(500);
	AUDIO::PLAY_SOUND_FRONTEND(-1, "WINNER", "CELEBRATION_SOUNDSET", true);
	GRAPHICS::_START_SCREEN_EFFECT("SuccessNeutral", 1000, false);
	Load();
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(Handle, "SHOW_MISSION_PASSED_MESSAGE");
	GRAPHICS::_BEGIN_TEXT_COMPONENT("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((char*)Title.c_str());
	GRAPHICS::_END_TEXT_COMPONENT();
	GRAPHICS::_BEGIN_TEXT_COMPONENT("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((char*)Subtitle.c_str());
	GRAPHICS::_END_TEXT_COMPONENT();
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(100);
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_BOOL(true);
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(Blocks.size() - 1);
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_BOOL(false);
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(2);
	GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION();
	int start = GAMEPLAY::GET_GAME_TIMER();
	int time = 1000;
	while (GAMEPLAY::GET_GAME_TIMER() < start + time)
	{
		GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(Handle, 255, 255, 255, 255, 0);
		WAIT(0);
	}
	start = GAMEPLAY::GET_GAME_TIMER();
	time = 400;
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(Handle, "TRANSITION_UP");
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_FLOAT(0.15f);
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_BOOL(true);
	GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION();
	while (GAMEPLAY::GET_GAME_TIMER() < start + time)
	{
		GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(Handle, 255, 255, 255, 255, 0);
		WAIT(0);
	}
	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(Handle, "ROLL_DOWN_BACKGROUND");
	GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION();
	int alpha = 0;
    start = GAMEPLAY::GET_GAME_TIMER();
	time = 9000;
	while (GAMEPLAY::GET_GAME_TIMER() < start + time)
	{
		if (alpha < 255)
		{
			alpha += 5;
		}
		GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(Handle, 255, 255, 255, 255, 0);
        #pragma region Top Divider

		fVar1 = 0.3f * func_14612();
		fVar1 -= func_14613(6);
		fVar1 += func_14613(30) - func_14613(4);
		GRAPHICS::DRAW_RECT(0.5f, fVar1 - (func_14613(1.5f) - 0.0013888889f), 0.3f, func_14607(1), 255, 255, 255, alpha);

        #pragma endregion

		if (Blocks.size() > 0)
		{
			float num2 = 2;
			for (auto& block : Blocks)
			{
				block.Draw(alpha, num2);
				num2 += 12;
			}
		}

        #pragma region Bottom Divider
		
		fVar1 += func_14613(0.6f);
		switch (Blocks.size() - 1)
		{
		case 0:
			fVar1 += func_14613(29.7f);
			break;
		case 1:
			fVar1 += func_14613(53.460003f);
			break;
		case 2:
			fVar1 += func_14613(77.22f);
			break;
		case 3:
			fVar1 += func_14613(100.98f);
			break;
		case 4:
			fVar1 += func_14613(124.740005f);
			break;
		case 5:
			fVar1 += func_14613(148.5f);
			break;
		case 6:
			fVar1 += func_14613(172.26001f);
			break;
		case 7:
			fVar1 += func_14613(196.01999f);
			break;
		case 8:
			fVar1 += func_14613(219.78001f);
			break;
		case 9:
			fVar1 += func_14613(243.54f);
			break;
		case 10:
			fVar1 += func_14613(267.30002f);
			break;
		case 11:
			fVar1 += func_14613(291.06f);
			break;
		case 12:
			fVar1 += func_14613(314.82f);
			break;
		case 13:
			fVar1 += func_14613(338.58f);
			break;
		case 14:
			fVar1 += func_14613(362.34f);
			break;
		case 15:
			fVar1 += func_14613(386.10004f);
			break;
		}
		GRAPHICS::DRAW_RECT(0.5f, fVar1 + func_14613(1), 0.3f, func_14607(1), 255, 255, 255, alpha);

        #pragma endregion

        #pragma region Bottom Label

		fVar1 = 0.3f * func_14612();
		fVar1 -= func_14613(6);
		fVar1 += func_14613(30) - func_14613(4);
		fVar9 = 0.30500004f;
		fVar10 = 0.693f;
		fVar20 = fVar9;
		fVar20 = fVar9 + 0.119f / func_14612() / 2.5f;

		UI::SET_TEXT_COLOUR(255, 255, 255, alpha);
		UI::SET_TEXT_WRAP(fVar20, fVar21);
		UI::SET_TEXT_JUSTIFICATION(0);
		UI::SET_TEXT_SCALE(1, 0.4f);
		UI::SET_TEXT_CENTRE(false);
		UI::SET_TEXT_FONT(0);
		UI::_SET_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING((char*)BottomLabel.c_str());
		float num = fVar1 + func_14613(44);
		switch (Blocks.size() - 1)
		{
		case 0:
			num = fVar1 + func_14613(37.4f);
			break;
		case 1:
			num = fVar1 + func_14613(59.84f);
			break;
		case 2:
			num = fVar1 + func_14613(82.28001f);
			break;
		case 3:
			num = fVar1 + func_14613(108.46001f);
			break;
		case 4:
			num = fVar1 + func_14613(130.90001f);
			break;
		case 5:
			num = fVar1 + func_14613(157.08f);
			break;
		case 6:
			num = fVar1 + func_14613(179.52002f);
			break;
		case 7:
			num = fVar1 + func_14613(205.70001f);
			break;
		case 8:
			num = fVar1 + func_14613(228.14f);
			break;
		case 9:
			num = fVar1 + func_14613(250.58f);
			break;
		case 10:
			num = fVar1 + func_14613(276.76f);
			break;
		case 11:
			num = fVar1 + func_14613(299.2f);
			break;
		case 12:
			num = fVar1 + func_14613(325.38f);
			break;
		case 13:
			num = fVar1 + func_14613(351.56f);
			break;
		case 14:
			num = fVar1 + func_14613(370.26f);
			break;
		case 15:
			num = fVar1 + func_14613(388.96002f);
			break;
		}
		UI::_DRAW_TEXT(0.45f, num);
		fVar21 = 0.5f;
		fVar21 += 0.143f;
		fVar22 = fVar21;
		fVar22 -= 0.286f;
		UI::SET_TEXT_COLOUR(255, 255, 255, alpha);
		UI::SET_TEXT_WRAP(fVar20, fVar21);
		UI::SET_TEXT_JUSTIFICATION(0);
		UI::SET_TEXT_SCALE(1, 0.4f);
		UI::SET_TEXT_CENTRE(false);
		UI::SET_TEXT_FONT(0);
		UI::_SET_TEXT_ENTRY("ESDOLLA");
		UI::ADD_TEXT_COMPONENT_INTEGER(BottomValue);
		UI::_0x0E4C749FF9DE9CC4(BottomValue, true);
		UI::_DRAW_TEXT(0.55f, num);
        #pragma endregion

		WAIT(0);
	}
	Dispose();
	AUDIO::RELEASE_NAMED_SCRIPT_AUDIO_BANK("HUD_123_GO");
	GRAPHICS::_STOP_SCREEN_EFFECT("SuccessNeutral");
}