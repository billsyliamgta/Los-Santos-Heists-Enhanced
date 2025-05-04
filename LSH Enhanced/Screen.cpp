#pragma once

#include "Screen.h"
#include "script.h"
#include "string"
#include "Debug.h"

namespace UI
{
    #pragma region Fading

	bool Screen::IsFadingOut()
	{
		return CAM::IS_SCREEN_FADING_OUT();
	}

	bool Screen::IsFadedOut()
	{
		return CAM::IS_SCREEN_FADED_OUT();
	}

	bool Screen::IsFadingIn()
	{
		return CAM::IS_SCREEN_FADING_IN();
	}

	bool Screen::IsFadedIn()
	{
		return CAM::IS_SCREEN_FADED_IN();
	}

	void Screen::DoFadeOut(int time)
	{
		CAM::DO_SCREEN_FADE_OUT(time);
	}


	void Screen::DoFadeIn(int time)
	{
		CAM::DO_SCREEN_FADE_IN(time);
	}

    #pragma endregion

    #pragma region Effects

	void Screen::SetTimecycleModifer(std::string modiferName)
	{
		GRAPHICS::SET_TIMECYCLE_MODIFIER((char*)modiferName.c_str());
	}

	void Screen::SetTimecycleModiferStrength(float strength)
	{
		GRAPHICS::SET_TIMECYCLE_MODIFIER_STRENGTH(strength);
	}

	void Screen::EnableMoonCycleOverride(float strength)
	{
		invoke<Void>(0x2C328AF17210F009, strength); /* ENABLE_MOON_CYCLE_OVERRIDE */
	}

	void Screen::ClearTimecycleModifer()
	{
		GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
	}

    #pragma endregion

    #pragma region Text

	bool Screen::IsHelpTextBeingDisplayed()
	{
		return UI::IS_HELP_MESSAGE_BEING_DISPLAYED();
	}

	void Screen::ShowSubtitle(char* text, int duration)
	{
		_SET_TEXT_ENTRY_2("STRING");
		_ADD_TEXT_COMPONENT_STRING(text);
		_DRAW_SUBTITLE_TIMED(duration, true);
	}

	int Screen::ShowNotification(char* text, bool blink)
	{
		_SET_NOTIFICATION_TEXT_ENTRY("STRING");
		_ADD_TEXT_COMPONENT_STRING(text);
		return _DRAW_NOTIFICATION(blink, false);
	}

	void Screen::ShowHelpTextThisFrame(std::string helpText, bool beep)
	{
		ShowHelpText(helpText, 1, beep, false);
	}

	void Screen::ShowHelpText(std::string helpText, int duration, bool beep, bool looped)
	{
		UI::_SET_TEXT_COMPONENT_FORMAT("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING((char*)helpText.c_str());
		UI::_DISPLAY_HELP_TEXT_FROM_STRING_LABEL(0, looped, beep, duration);
	}

	void Screen::ClearHelpText()
	{
		UI::CLEAR_HELP(true);
	}

	void Screen::SendTextNotification(std::string avatar, std::string author, std::string title, std::string message)
	{
		int start = GAMEPLAY::GET_GAME_TIMER();
		int time = 2000;
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)avatar.c_str(), false);
		while (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)avatar.c_str()))
		{
			if (GAMEPLAY::GET_GAME_TIMER() > start + time)
			{
				DEBUG::Debug::PrintToLog("Timed out while loading streamed texture dict: " + avatar + ".");
				return;
			}
			WAIT(0);
		}
		AUDIO::PLAY_SOUND_FRONTEND(-1, "Text_Arrive_Tone", "Phone_SoundSet_Default", false);
		UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING((char*)message.c_str());
		UI::_SET_NOTIFICATION_MESSAGE((char*)avatar.c_str(), (char*)avatar.c_str(), true, 0, (char*)title.c_str(), (char*)author.c_str());
		GRAPHICS::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED((char*)avatar.c_str());
	}

    #pragma endregion

    #pragma region Minimap

	bool Screen::IsMinimapRendering()
	{
		return invoke<bool>(0xAF754F20EB5CD51A); /* IS_MINIMAP_RENDERING */
	}

	void Screen::DisplayHud(bool toggle)
	{
		UI::DISPLAY_HUD(toggle);
	}

	void Screen::DisplayRadar(bool toggle)
	{
		UI::DISPLAY_RADAR(toggle);
	}

	bool Screen::IsHudHidden()
	{
		return UI::IS_HUD_HIDDEN();
	}

	bool Screen::IsRadarHidden()
	{
		return UI::IS_RADAR_HIDDEN();
	}

    #pragma endregion

    #pragma region Fields/

	const float UI::Screen::Width = 1280;

	const float UI::Screen::Height = 720;

	float UI::Screen::AspectRatio()
	{
		return GRAPHICS::_GET_SCREEN_ASPECT_RATIO(false);
	}

	float UI::Screen::ScaledWidth()
	{
		return Height * AspectRatio();
	}

	Extensions::Size UI::Screen::Resolution()
	{
		int width, height;
		GRAPHICS::_GET_SCREEN_ACTIVE_RESOLUTION(&width, &height);
		return { width, height };
	}

    #pragma endregion
}