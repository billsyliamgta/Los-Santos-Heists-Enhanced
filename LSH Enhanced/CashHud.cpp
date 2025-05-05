#include "CashHud.h"

void UI::Scaleforms::CashHud::Request()
{
	GRAPHICS::_REQUEST_HUD_SCALEFORM(HudComponent);
	while (!GRAPHICS::_HAS_HUD_SCALEFORM_LOADED(HudComponent))
	{
		WAIT(0);
	}

	GRAPHICS::_REQUEST_HUD_SCALEFORM(22);
	while (!GRAPHICS::_HAS_HUD_SCALEFORM_LOADED(22))
	{
		WAIT(0);
	}
}

void UI::Scaleforms::CashHud::Dispose()
{
	if (GRAPHICS::_HAS_HUD_SCALEFORM_LOADED((int)HudComponent))
	{
		GRAPHICS::_0xF44A5456AC3F4F97((int)HudComponent);
	}

	if (GRAPHICS::_HAS_HUD_SCALEFORM_LOADED(22))
	{
		GRAPHICS::_0xF44A5456AC3F4F97(22);
	}
}

void UI::Scaleforms::CashHud::Control()
{
	if (!UI::IS_RADAR_HIDDEN() && !UI::IS_RADAR_HIDDEN())
	{
		if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, 20))
		{
			// todo - add a timeout function
			Request();
			GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_FROM_HUD_COMPONENT((int)HudComponent, "SET_PLAYER_MP_CASH_WITH_STRING");
			std::string cashString = "~g~$" + std::to_string(Cash) + "~w~\n ~HC_GREENLIGHT~${Bank}~HUD_COLOUR_WHITE~";
			GRAPHICS::_BEGIN_TEXT_COMPONENT("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING((char*)cashString.c_str());
			GRAPHICS::_END_TEXT_COMPONENT();
			GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION();
			GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_FROM_HUD_COMPONENT((int)HudComponent, "SHOW");
			GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_BOOL(false);
			GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION();
			int start = GAMEPLAY::GET_GAME_TIMER();
			int time = 5000;
			while (GAMEPLAY::GET_GAME_TIMER() < start + time)
			{
				invoke<Void>(0x4F38DCA127DAAEA2, (int)HudComponent); /* SHOW_SCRIPTED_HUD_COMPONENT_THIS_FRAME */
				WAIT(0);
			}
			GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_FROM_HUD_COMPONENT((int)HudComponent, "HIDE");
			GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION();
			start = GAMEPLAY::GET_GAME_TIMER();
			time = 500;
			while (GAMEPLAY::GET_GAME_TIMER() < start + time)
			{
				invoke<Void>(0x4F38DCA127DAAEA2, (int)HudComponent);
				WAIT(0);
			}
			Dispose();
		}
		else if (PreviousCash != Cash || PreviousBank != Bank && !UI::IS_RADAR_HIDDEN() && !UI::IS_RADAR_HIDDEN() && UI::_0x2309595AD6145265() == 4294967295)
		{
			Request();
			GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_FROM_HUD_COMPONENT((int)HudComponent, "SET_PLAYER_CASH_CHANGE");
			GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(AddedCash);
			GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_BOOL(PreviousCash < Cash);
			GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION();
			PreviousCash = Cash;
			AddedCash = 0;
			PreviousBank = Bank;
			AddedBank = 0;
			GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_FROM_HUD_COMPONENT((int)HudComponent, "SHOW");
			GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_BOOL(false);
			GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION();
			int start = GAMEPLAY::GET_GAME_TIMER();
			int time = 1000;
			while (GAMEPLAY::GET_GAME_TIMER() < start + time)
			{
				invoke<Void>(0x4F38DCA127DAAEA2, (int)HudComponent);
				WAIT(0);
			}
			GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_FROM_HUD_COMPONENT((int)HudComponent, "HIDE");
			GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION();
			start = GAMEPLAY::GET_GAME_TIMER();
			time = 500;
			while (GAMEPLAY::GET_GAME_TIMER() < start + time)
			{
				invoke<Void>(0x4F38DCA127DAAEA2, (int)HudComponent);
				WAIT(0);
			}
			Dispose();
		}
	}

	if (Cash < 0)
	{
		SetCash(0);
	}

	if (Bank < 0)
	{
		SetBank(0);
	}
}