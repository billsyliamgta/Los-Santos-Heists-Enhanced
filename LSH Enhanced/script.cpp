#include "script.h"
#include "RankBar.h"
#include "CashHud.h"
#include "Debug.h"

UI::Scaleforms::RankBar RankBar;

UI::Scaleforms::CashHud CashHud;

int main()
{
	while (true)
	{		
		switch (Index)
		{
		case 0:
		{
			DLC2::_LOAD_MP_DLC_MAPS();
			AUDIO::SET_AUDIO_FLAG("LoadMPData", true);
			DEBUG::Debug::PrintToLog("Loading MP Maps.");
			DEBUG::Debug::PrintToLog("Loading MP Audio Data.");
			DEBUG::Debug::PrintToLog("Rank Bar initialized.");
			DEBUG::Debug::PrintToLog("Cash Hud initialized.");
			DEBUG::Debug::PrintToLog(DLC2::IS_DLC_PRESENT(GAMEPLAY::GET_HASH_KEY("mpheist")) ? "Found mpheist DLC pack." : "mpheist DLC pack could not be found. Please verify your game files.");
			DEBUG::Debug::PrintToLog(DLC2::IS_DLC_PRESENT(GAMEPLAY::GET_HASH_KEY("mpheist3")) ? "Found mpheist3 DLC pack." : "mpheist3 DLC pack could not be found. Please verify your game files.");
			DEBUG::Debug::PrintToLog(DLC2::IS_DLC_PRESENT(GAMEPLAY::GET_HASH_KEY("mpheist4")) ? "Found mpheist4 DLC pack." : "mpheist4 DLC pack could not be found. Please verify your game files.");
			DEBUG::Debug::PrintToLog(DLC2::IS_DLC_PRESENT(GAMEPLAY::GET_HASH_KEY("mpchristmas3")) ? "Found mpchristmas3 DLC pack." : "mpchristmas3 DLC pack could not be found. Please verify your game files.");
			DEBUG::Debug::PrintToLog(DLC2::IS_DLC_PRESENT(GAMEPLAY::GET_HASH_KEY("mp2023_02")) ? "Found mp2023_02 DLC pack." : "mp2023_02 DLC pack could not be found. Please verify your game files.");
			DEBUG::Debug::PrintToLog(DLC2::IS_DLC_PRESENT(GAMEPLAY::GET_HASH_KEY("lsh_gen9")) ? "Found lsh_gen9 DLC pack." : "lsh_gen9 DLC pack could not be found. You may encounter issues so please check your installation or start fresh.");
			DEBUG::Debug::PrintToLog("Success loaded.");
			Index = 1;
		}
		break;
		case 1:
		{
			GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("cellphone_controller");
			GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("cellphone_flashhand");
			RankBar.Control();
			CashHud.Control();
		}
		break;
		}

		WAIT(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}