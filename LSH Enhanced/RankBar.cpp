#include "RankBar.h"

void UI::Scaleforms::RankBar::Control()
{
	if (!UI::IS_RADAR_HIDDEN() && !UI::IS_RADAR_HIDDEN() || PreviousXP != CurrentXP)
	{
		if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, 20))
		{
			XPStartLimit = CalculateXP(PlayerLevel - 1);
			XPEndLimit = CalculateXP(PlayerLevel);
			GRAPHICS::_REQUEST_HUD_SCALEFORM((int)BarId);
			while (!GRAPHICS::_HAS_HUD_SCALEFORM_LOADED((int)BarId)) WAIT(0);
			SetColor(116, 123);
			GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_FROM_HUD_COMPONENT((int)BarId, "OVERRIDE_ANIMATION_SPEED");
			GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(2000);
			GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION();
			GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_FROM_HUD_COMPONENT((int)BarId, "OVERRIDE_ONSCREEN_DURATION");
			GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(6000);
			GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION();
			BeforeDraw();
			PreviousXP = CurrentXP;
		}

		// Rank up segment
		if (CurrentXP >= XPEndLimit && !UI::IS_RADAR_HIDDEN() && !UI::IS_RADAR_HIDDEN())
		{
			XPStartLimit = CalculateXP(PlayerLevel - 1);
			XPEndLimit = CalculateXP(PlayerLevel);
			GRAPHICS::_REQUEST_HUD_SCALEFORM((int)BarId);
			while (!GRAPHICS::_HAS_HUD_SCALEFORM_LOADED((int)BarId)) WAIT(0);
			AUDIO::SET_AUDIO_FLAG("LoadMPData", true);
			while (!AUDIO::_0x544810ED9DB6BBE6()) WAIT(0); // Make sure multiplayer audio data is loaded before continuing
			SetOverrideParams(2000, 6000);
			SetColor(116, 123);
			BeforeDraw();
			PlayerLevel++;
			AUDIO::PLAY_SOUND_FRONTEND(-1, "MP_RANK_UP", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
			SetOverrideParams(2000, 6000);
			SetColor(116, 123);
			SetRankScores(XPStartLimit, XPEndLimit, PreviousXP, CurrentXP, PlayerLevel, PlayerLevel + 1);
			ResetMovie();
			XPStartLimit = CalculateXP(PlayerLevel - 1);
			XPEndLimit = CalculateXP(PlayerLevel);
			SetColor(116, 123);
			SetRankScores(XPStartLimit, XPEndLimit, PreviousXP, CurrentXP, PlayerLevel, PlayerLevel + 1);
		}
	}

	if (!UI::IS_SCRIPTED_HUD_COMPONENT_ACTIVE((int)BarId) && GRAPHICS::_HAS_HUD_SCALEFORM_LOADED((int)BarId))
	{
		GRAPHICS::_0xF44A5456AC3F4F97((int)BarId); /* REMOVE_SCALEFORM_SCRIPT_HUD_MOVIE */
	}
}

void UI::Scaleforms::RankBar::SetColor(int primaryColor, int secordaryColor)
{
	if (GRAPHICS::_HAS_HUD_SCALEFORM_LOADED((int)BarId))
	{
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_FROM_HUD_COMPONENT((int)BarId, "SET_COLOUR");
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(primaryColor);
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(secordaryColor);
		GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION();
	}
}

void UI::Scaleforms::RankBar::StayOnScreen()
{
	if (GRAPHICS::_HAS_HUD_SCALEFORM_LOADED((int)BarId))
	{
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_FROM_HUD_COMPONENT((int)BarId, "STAY_ON_SCREEN");
		GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION();
	}
}

void UI::Scaleforms::RankBar::ResetMovie()
{
	if (GRAPHICS::_HAS_HUD_SCALEFORM_LOADED((int)BarId))
	{
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_FROM_HUD_COMPONENT((int)BarId, "RESET_MOVIE");
		GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION();
	}
}

void UI::Scaleforms::RankBar::SetRankScores(int xpStartLimit, int xpEndLimit, int previousXP, int currentXP, int playerLevel, int rankNext)
{
	if (GRAPHICS::_HAS_HUD_SCALEFORM_LOADED((int)BarId))
	{
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_FROM_HUD_COMPONENT((int)BarId, "SET_RANK_SCORES");
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(xpStartLimit);
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(xpEndLimit);
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(previousXP);
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(currentXP);
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(playerLevel);
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(100);
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(rankNext);
		GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION();
	}
}

void UI::Scaleforms::RankBar::SetOverrideParams(int speed, int duration)
{
	if (GRAPHICS::_HAS_HUD_SCALEFORM_LOADED((int)BarId))
	{
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_FROM_HUD_COMPONENT((int)BarId, "OVERRIDE_ANIMATION_SPEED");
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(speed);
		GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION();
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_FROM_HUD_COMPONENT((int)BarId, "OVERRIDE_ONSCREEN_DURATION");
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(duration);
		GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION();
	}
}