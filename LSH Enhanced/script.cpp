#include "script.h"
#include "keyboard.h"
#include <string>
#include "CasinoVehicleRobbery.h"
#include "ScaledText.h"
#include "RobberyCompleteShard.h"
#include "RobberyCompleteShardBlock.h"
#include "CasinoVehicleRobberyPrep1.h"
#include "Debug.h"
#include "Memory.h"
#include "Hooking.h"
#include "Hooking.Patterns.h"
#include "BelleGarageProperty.h"
#include "TimerBarBase.h"
#include "TimerBarPool.h"

PROPERTIES::BelleGarageProperty belleClubhouse;

UI::TimerBars::TimerBarPool _pool;

int main()
{
	while (true)
	{		
		switch (Index)
		{
		case 0:
		{
			DLC2::_LOAD_MP_DLC_MAPS();
			belleClubhouse.SetupIPL();
			belleClubhouse.SpawnProps(false);
			ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), belleClubhouse.interiorCoords.x, belleClubhouse.interiorCoords.y, belleClubhouse.interiorCoords.z, false, false, false, false);
			AUDIO::SET_AUDIO_FLAG("LoadMPData", true);
			DEBUG::Debug::PrintToLog("Loading MP Maps.");
			DEBUG::Debug::PrintToLog("Loading MP Audio Data.");
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
			_pool.Draw();
			UI::Screen::ShowHelpTextThisFrame("bruh", true);
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