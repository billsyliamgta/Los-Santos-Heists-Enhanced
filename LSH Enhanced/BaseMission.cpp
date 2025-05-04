#pragma once

#include "BaseMission.h"
#include "script.h"
#include "Debug.h"

namespace Missions
{
	void BaseMission::Update()
	{
		// TODO - add respawn stuff here
	}

	void BaseMission::UpdateStats()
	{

	}

	void BaseMission::Init()
	{
		GAMEPLAY::SET_MISSION_FLAG(true);
		AUDIO::SET_AUDIO_FLAG("DisableFlightMusic", true);
		// AUDIO::SET_AUDIO_FLAG("EnableHeadsetBeep", true);
		AUDIO::SET_AUDIO_FLAG("WantedMusicDisabled", true);
		DEBUG::Debug::PrintToLog("Initialized Mission.");
	}

	void BaseMission::Dispose()
	{
		GAMEPLAY::SET_MISSION_FLAG(false);
		AUDIO::SET_AUDIO_FLAG("DisableFlightMusic", false);
		// AUDIO::SET_AUDIO_FLAG("EnableHeadsetBeep", false);
		AUDIO::SET_AUDIO_FLAG("WantedMusicDisabled", false);
		AUDIO::TRIGGER_MUSIC_EVENT("GTA_ONLINE_STOP_SCORE");

		if (UI::IS_HELP_MESSAGE_BEING_DISPLAYED()) 
		{
			UI::CLEAR_ALL_HELP_MESSAGES();
		}

		UI::CLEAR_BRIEF(); // clear the brief in the Pause Menu

		UI::DISPLAY_HUD(true);
		UI::DISPLAY_RADAR(true);

		PLAYER::SET_PLAYER_CONTROL(PLAYER::PLAYER_ID(), true, 0);
		PED::SET_PED_CAN_SWITCH_WEAPON(PLAYER::PLAYER_PED_ID(), true);

		CurrentMission = nullptr; // reset the mission's pointer to nullptr
		Index = 0;
		DEBUG::Debug::PrintToLog("Disposed Mission.");
	}

	/// <summary>
	/// Generates a one time jenkins hash
	/// </summary>
	/// <param name="string"></param>
	/// <returns></returns>
	unsigned int BaseMission::joaat(char* string)
	{
		return GAMEPLAY::GET_HASH_KEY(string);
	}
}