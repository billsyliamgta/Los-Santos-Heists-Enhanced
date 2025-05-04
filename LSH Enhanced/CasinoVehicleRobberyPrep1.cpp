// Copyright (C) BillsyLiamGTA 2025-2026. All Rights Reserved.
// Part of Belle's Chop Shop - Prep Work for Access Card (The Podium Robbery)
// Last Updated: 24/04/2025, 22:41 PM GMT

#include "CasinoVehicleRobberyPrep1.h"

void Missions::CasinoVehicleRobberyPrep1::Update()
{
	HideApartmentExterior();
	CheckOnGuards();
	switch (Index)
	{
	case 0:
	{
		Init();
		Index = 1;
	}
	break;
	case 1:
	{
		if (!UI::DOES_BLIP_EXIST(EnterApartmentBlip))
		{
			EnterApartmentBlip = UI::ADD_BLIP_FOR_COORD(EnterApartmentAnimPosition().x, EnterApartmentAnimPosition().y, EnterApartmentAnimPosition().z);
			UI::SET_BLIP_SPRITE(EnterApartmentBlip, 1);
			UI::SET_BLIP_COLOUR(EnterApartmentBlip, 5);
		}
		else
		{
			std::string goToSub = "Go to ~y~" + GetApartmentName() + ".";
			UI::Screen::ShowSubtitle((char*)goToSub.c_str());

			if (GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false).x, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false).y, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false).z, EnterApartmentAnimPosition().x, EnterApartmentAnimPosition().y, EnterApartmentAnimPosition().z, false) < 3.0)
			{
				UI::REMOVE_BLIP(&EnterApartmentBlip);
				EnterApartmentBlip = 0;
				UI::CLEAR_PRINTS();
				UI::DISPLAY_HUD(false);
				UI::DISPLAY_RADAR(false);
				AUDIO::TRIGGER_MUSIC_EVENT("CH_SUSPENCE");
				PED::SET_PED_CAN_SWITCH_WEAPON(PLAYER::PLAYER_PED_ID(), false);
				WEAPON::SET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), joaat("WEAPON_UNARMED"), true);
				STREAMING::REQUEST_ANIM_DICT("anim@door_trans@hinge_l@");
				while (!STREAMING::HAS_ANIM_DICT_LOADED("anim@door_trans@hinge_l@")) WAIT(0);
				AUDIO::RELEASE_NAMED_SCRIPT_AUDIO_BANK("dlc_h4_Prep_FC_Sounds");
				AUDIO::REQUEST_SCRIPT_AUDIO_BANK("dlc_h4_Prep_FC_Sounds", false);
				Cam = CAM::CREATE_CAM("DEFAULT_ANIMATED_CAMERA", 0);
				SyncScene = PED::CREATE_SYNCHRONIZED_SCENE(EnterApartmentAnimPosition().x, EnterApartmentAnimPosition().y, EnterApartmentAnimPosition().z + 0.2f, 0, 0, EnterApartmentAnimHeading(), 2);
				AI::TASK_SYNCHRONIZED_SCENE(PLAYER::PLAYER_PED_ID(), SyncScene, "anim@door_trans@hinge_l@", "charge_player1", 4, -15, 3341, 16, 0x447a0000, 0);
				CAM::PLAY_SYNCHRONIZED_CAM_ANIM(Cam, SyncScene, "charge_cam_left", "anim@door_trans@hinge_l@");
				CAM::SET_CAM_ACTIVE(Cam, true);
				CAM::RENDER_SCRIPT_CAMS(true, false, 3000, false, false);
				CAM::SHAKE_CAM(Cam, "JOLT_SHAKE", 0.5f);
				AUDIO::PLAY_SOUND_FRONTEND(-1, "Barge_Door", "dlc_h4_Prep_FC_Sounds", false);
				STREAMING::REMOVE_ANIM_DICT("anim@door_trans@hinge_l@");
				while (PED::GET_SYNCHRONIZED_SCENE_PHASE(SyncScene) < 0.800f) WAIT(0);
				AUDIO::RELEASE_NAMED_SCRIPT_AUDIO_BANK("dlc_h4_Prep_FC_Sounds");
				if (!CAM::IS_SCREEN_FADING_OUT() && !CAM::IS_SCREEN_FADED_OUT())
				{
					CAM::DO_SCREEN_FADE_OUT(250);
				}

				while (CAM::IS_SCREEN_FADING_OUT()) WAIT(0);
				CAM::RENDER_SCRIPT_CAMS(false, false, 3000, false, false);
				CAM::DESTROY_CAM(Cam, true);
				Cam = 0;
				PED::_0xCD9CC7E200A52A6F(SyncScene);
				SyncScene = 0;
				LoadInteriors(false);
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), ApartmentSpawnPosition().x, ApartmentSpawnPosition().y, ApartmentSpawnPosition().z, false, false, false, false);
				ENTITY::SET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID(), ApartmentSpawnHeading() - 180.0f);
				// do stuff here
				WAIT(2000);
				UI::DISPLAY_HUD(true);
				UI::DISPLAY_RADAR(true);
				PED::SET_PED_CAN_SWITCH_WEAPON(PLAYER::PLAYER_PED_ID(), true);
				if (!CAM::IS_SCREEN_FADING_IN() && !CAM::IS_SCREEN_FADED_IN())
				{
					CAM::DO_SCREEN_FADE_IN(250);
				}
				Index = 2;
			}
		}
	}
	break;
	case 2:
	{
		UI::Screen::ShowSubtitle("Locate the valet.");

		if (ENTITY::DOES_ENTITY_EXIST(Valet))
		{
			if (INTERIOR::GET_ROOM_KEY_FROM_ENTITY(PLAYER::PLAYER_PED_ID()) == INTERIOR::GET_ROOM_KEY_FROM_ENTITY(Valet))
			{
				UI::Screen::ShowNotification("You located the Valet.");
				Index = 3;
			}
		}
	}
	break;
	case 3:
	{
		UI::Screen::ShowSubtitle("Intimidate the ~b~valet.");

		if (ENTITY::DOES_ENTITY_EXIST(Valet))
		{
			if (!UI::DOES_BLIP_EXIST(ValetBlip))
			{
				ValetBlip = UI::ADD_BLIP_FOR_ENTITY(Valet);
				UI::SET_BLIP_SPRITE(ValetBlip, 280);
				UI::SET_BLIP_COLOUR(ValetBlip, 3);
				UI::SET_BLIP_SCALE(ValetBlip, 0.7f);
				UI::BEGIN_TEXT_COMMAND_SET_BLIP_NAME("VRPS_BLIP_2");
				UI::END_TEXT_COMMAND_SET_BLIP_NAME(ValetBlip);
			}
			else
			{
				if (AI::GET_SCRIPT_TASK_STATUS(Valet, joaat("SCRIPT_TASK_HANDS_UP")) != 1)
				{
					AI::TASK_HANDS_UP(Valet, 5000, PLAYER::PLAYER_PED_ID(), -1, 0);
				}
				else if (AI::GET_SCRIPT_TASK_STATUS(Valet, joaat("SCRIPT_TASK_HANDS_UP")) == 1)
				{
					AI::UPDATE_TASK_HANDS_UP_DURATION(Valet, 5000); /* this needs to be updated otherwise it'll stop */
				}

				if (IntimidateValet >= 1.0f) /* at this point the intimidation is complete and we need to change the objective */
				{
					IntimidateValet = 1.0f;

					if (STREAMING::HAS_ANIM_DICT_LOADED("anim@mugging@victim@toss_ped@"))
					{
						if (!PED::IS_PED_RAGDOLL(Valet) && AI::GET_SCRIPT_TASK_STATUS(Valet, joaat("SCRIPT_TASK_HANDS_UP") == 1))
						{
							if (AI::GET_SCRIPT_TASK_STATUS(Valet, joaat("SCRIPT_TASK_PLAY_ANIM") != 1))
							{
								UI::REMOVE_BLIP(&ValetBlip);
								ValetBlip = 0;
								AUDIO::STOP_SCRIPTED_CONVERSATION(true);
								AUDIO::CREATE_NEW_SCRIPTED_CONVERSATION();
								AUDIO::ADD_PED_TO_CONVERSATION(0, Valet, "xm4_valet");
								AUDIO::ADD_LINE_TO_CONVERSATION(0, (Any*)"xm4r4_cxaa", (Any*)"xm4_valet", false, false, false, false, false, false, false, false, false, false);
								AUDIO::START_SCRIPT_CONVERSATION(UI::IS_SUBTITLE_PREFERENCE_SWITCHED_ON(), false, false, false);
								AI::TASK_PLAY_ANIM(Valet, "anim@mugging@victim@toss_ped@", "throw_object_left_pocket_male", 8.0f, -8.0f, -1, 0, 0.0f, false, false, false);
								STREAMING::REMOVE_ANIM_DICT("anim@mugging@victim@toss_ped@"); /* remove the anim dict so the game engine can clean it up when necessary */
								AUDIO::TRIGGER_MUSIC_EVENT("CH_GUNFIGHT");
								Index = 4;
							}
						}
					}
					else
					{
						STREAMING::REQUEST_ANIM_DICT("anim@mugging@victim@toss_ped@");
						while (!STREAMING::HAS_ANIM_DICT_LOADED("anim@mugging@victim@toss_ped@")) WAIT(0); /* request and wait on a loop while the anim dict loads because its needed for the next section */
					}
				}
			}
		}

		int entity;
		if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &entity)) /* this works fine so no need to change it */
		{
			if (entity == Valet && IntimidateValet <= 1.0f)
			{
				switch (ValetSpeechStage)
				{
				case 0:
				{
					AUDIO::STOP_SCRIPTED_CONVERSATION(true);
					AUDIO::CREATE_NEW_SCRIPTED_CONVERSATION();
					AUDIO::ADD_PED_TO_CONVERSATION(0, Valet, "xm4_valet");
					AUDIO::ADD_LINE_TO_CONVERSATION(0, (Any*)"xm4r4_cuaa", (Any*)"xm4_valet", false, false, false, false, false, false, false, false, false, false);
					AUDIO::START_SCRIPT_CONVERSATION(UI::IS_SUBTITLE_PREFERENCE_SWITCHED_ON(), false, false, false);
					ValetSpeechStage = 1;
				}
				break;

				case 1:
				{
					if (!AUDIO::IS_SCRIPTED_CONVERSATION_ONGOING())
					{
						ValetSpeechCooldownTimer = GAMEPLAY::GET_GAME_TIMER() + 3000;
						ValetSpeechStage = 2;
					}
				}
				break;

				case 3:
				{
					AUDIO::STOP_SCRIPTED_CONVERSATION(true);
					AUDIO::CREATE_NEW_SCRIPTED_CONVERSATION();
					AUDIO::ADD_PED_TO_CONVERSATION(0, Valet, "xm4_valet");
					AUDIO::ADD_LINE_TO_CONVERSATION(0, (Any*)"xm4r4_cvaa", (Any*)"xm4_valet", false, false, false, false, false, false, false, false, false, false);
					AUDIO::START_SCRIPT_CONVERSATION(UI::IS_SUBTITLE_PREFERENCE_SWITCHED_ON(), false, false, false);
					ValetSpeechStage = 4;
				}
				break;

				case 4:
				{
					if (!AUDIO::IS_SCRIPTED_CONVERSATION_ONGOING())
					{
						ValetSpeechCooldownTimer = GAMEPLAY::GET_GAME_TIMER() + 3000;
						ValetSpeechStage = 5;
					}
				}
				break;

				case 5:
				{
					AUDIO::STOP_SCRIPTED_CONVERSATION(true);
					AUDIO::CREATE_NEW_SCRIPTED_CONVERSATION();
					AUDIO::ADD_PED_TO_CONVERSATION(0, Valet, "xm4_valet");
					AUDIO::ADD_LINE_TO_CONVERSATION(0, (Any*)"xm4r4_cmaa", (Any*)"xm4_valet", false, false, false, false, false, false, false, false, false, false);
					AUDIO::START_SCRIPT_CONVERSATION(UI::IS_SUBTITLE_PREFERENCE_SWITCHED_ON(), false, false, false);
					ValetSpeechStage = -1;
				}
				break;
				}

				IntimidateValet += 0.001f;
			}
		}
	}
	break;
	case 4:
	{
		if (ENTITY::DOES_ENTITY_EXIST(Valet))
		{
			if (!ENTITY::IS_ENTITY_PLAYING_ANIM(Valet, "anim@mugging@victim@toss_ped@", "throw_object_left_pocket_male", 3) && AI::GET_SCRIPT_TASK_STATUS(Valet, joaat("SCRIPT_TASK_COWER") != 1) && !IsValetCowering_FLAG)
			{
				AI::TASK_COWER(Valet, -1);
				PED::SET_PED_KEEP_TASK(Valet, true);
				IsValetCowering_FLAG = true;
			}
		}

		if (ENTITY::DOES_ENTITY_EXIST(Safe) && ENTITY::DOES_ENTITY_EXIST(SafeDoor) && IsValetCowering_FLAG)
		{
			if (!UI::DOES_BLIP_EXIST(SafeBlip))
			{
				SafeBlip = UI::ADD_BLIP_FOR_ENTITY(Safe);
				UI::SET_BLIP_SPRITE(SafeBlip, 814);
				UI::SET_BLIP_COLOUR(SafeBlip, 2);
				UI::BEGIN_TEXT_COMMAND_SET_BLIP_NAME("VRPS_HUD_BLP_8");
				UI::END_TEXT_COMMAND_SET_BLIP_NAME(SafeBlip);
			}
			else
			{
				UI::Screen::ShowSubtitle("Steal the access card from the ~g~safe.");
				Vector3 arrowOffset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Safe, -0.210f, 0.0f, 0.910f);
				GRAPHICS::DRAW_MARKER(2, arrowOffset.x, arrowOffset.y, arrowOffset.z, 0.0f, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f, 0.24f, 0.24f, 0.24f, 144, 238, 144, 255, true, true, false, 0, 0, false, false);
				if (GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true).x, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true).y, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true).z, ENTITY::GET_ENTITY_COORDS(SafeDoor, false).x, ENTITY::GET_ENTITY_COORDS(SafeDoor, false).y, ENTITY::GET_ENTITY_COORDS(SafeDoor, false).z, false) < 1.0f)
				{
					UI::DISPLAY_HELP_TEXT_THIS_FRAME("VRPS_INTER_2", true);
					if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, 51))
					{
						UI::REMOVE_BLIP(&SafeBlip);
						SafeBlip = 0;
						OpenSafe();
						UI::Screen::ShowNotification("Access card collected.");
						Index = 5;
					}
				}
			}
		}
	}
	break;
	case 5:
	{
		if (!UI::DOES_BLIP_EXIST(ElevBlip))
		{
			ElevBlip = UI::ADD_BLIP_FOR_COORD(ElevatorCoronaPosition().x, ElevatorCoronaPosition().y, ElevatorCoronaPosition().z);
			UI::SET_BLIP_SPRITE(ElevBlip, 1);
			UI::SET_BLIP_COLOUR(ElevBlip, 5);
			ElevCheckpoint = GRAPHICS::CREATE_CHECKPOINT(47, ElevatorCoronaPosition().x, ElevatorCoronaPosition().y, ElevatorCoronaPosition().z, 0.0f, 0.0f, 0.0f, 1.0f, 240, 200, 80, 155, 0);
			GRAPHICS::SET_CHECKPOINT_CYLINDER_HEIGHT(ElevCheckpoint, 0.7f, 0.7f, 0.7f);
		}
		else
		{
			UI::Screen::ShowSubtitle("Take the ~y~elevator ~w~to the garage.");

			if (GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true).x, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true).y, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true).z, ElevatorCoronaPosition().x, ElevatorCoronaPosition().y, ElevatorCoronaPosition().z, false) < 3.0f)
			{
				UI::REMOVE_BLIP(&ElevBlip);
				ElevBlip = 0;
				GRAPHICS::DELETE_CHECKPOINT(ElevCheckpoint);
				ElevCheckpoint = 0;
				PED::SET_PED_CAN_SWITCH_WEAPON(PLAYER::PLAYER_PED_ID(), false);
				WEAPON::SET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), joaat("WEAPON_UNARMED"), true);
				ENTITY::RESET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID());
				int alpha = 255;
				while (ENTITY::GET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID()) > 4)
				{
					alpha -= 4;
					ENTITY::SET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID(), alpha, false);
					WAIT(0);
				}

				if (!CAM::IS_SCREEN_FADING_OUT() && !CAM::IS_SCREEN_FADED_OUT()) CAM::DO_SCREEN_FADE_OUT(500);
				while (CAM::IS_SCREEN_FADING_OUT()) WAIT(0);
				ENTITY::RESET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID());
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 237.876f, -1004.753f, -99.0f, false, false, false, false);
				ENTITY::SET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID(), 90.0f);
				WAIT(250);
				SetupGarage(false);
				IsAlerted_FLAG = true;
				WAIT(250);
				if (!CAM::IS_SCREEN_FADING_IN() && !CAM::IS_SCREEN_FADED_IN()) CAM::DO_SCREEN_FADE_IN(500);
				while (CAM::IS_SCREEN_FADING_IN()) WAIT(0);
				PED::SET_PED_CAN_SWITCH_WEAPON(PLAYER::PLAYER_PED_ID(), true);
				Index = 6;
			}
		}
	}
	break;
	case 6:
	{
		UI::Screen::ShowSubtitle("Take out the ~r~duggans.");

		for (auto ped : Guards)
		{
			if (ENTITY::DOES_ENTITY_EXIST(ped))
			{
				if (!ENTITY::IS_ENTITY_DEAD(ped))
				{
					return;
				}
			}
		}

		// if all the duggans are dead we move onto the next objective
		Index = 7;
	}
	break;
	case 7:
	{
		if (GarageVehicles.size() > 0)
		{
			for (auto vehicle : GarageVehicles)
			{
				if (ENTITY::GET_ENTITY_MODEL(vehicle) == joaat("boxville4"))
				{
					if (!UI::DOES_BLIP_EXIST(PostOpBlip))
					{
						PostOpBlip = UI::ADD_BLIP_FOR_ENTITY(vehicle);
						UI::SET_BLIP_SPRITE(PostOpBlip, 853);
						UI::SET_BLIP_COLOUR(PostOpBlip, 3);
					}
					else
					{
						UI::Screen::ShowSubtitle("Steal the ~b~Post OP Van.");

						if (PED::IS_PED_IN_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, false))
						{
							UI::Screen::ShowHelpTextThisFrame("Press ~INPUT_VEH_ACCELERATE~ to leave the Garage.", true);
							if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, 71))
							{
								UI::Screen::ClearHelpText();
							}
						}
					}
				}
			}
		}
	}
	break;
	}
}

void Missions::CasinoVehicleRobberyPrep1::Init()
{
	BaseMission::Init();
	PLAYER::SET_MAX_WANTED_LEVEL(0);
	PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 0, false);
	PLAYER::SET_WANTED_LEVEL_MULTIPLIER(0.0f);
	AUDIO::TRIGGER_MUSIC_EVENT("CH_IDLE_START");
	ApartmentIndex = 2;
	UI::Scaleforms::MidsizedMessage midsizedMessage;
	midsizedMessage.Show("PREP WORK: ACCESS CARD", "Steal an access keycard from the Valet's apartment.", 2);
}

void Missions::CasinoVehicleRobberyPrep1::Dispose()
{
	BaseMission::Dispose();

	if (UI::DOES_BLIP_EXIST(EnterApartmentBlip))
	{
		UI::REMOVE_BLIP(&EnterApartmentBlip);
		EnterApartmentBlip = 0;
	}

	if (UI::DOES_BLIP_EXIST(SafeBlip))
	{
		UI::REMOVE_BLIP(&SafeBlip);
		SafeBlip = 0;
	}

	if (UI::DOES_BLIP_EXIST(ElevBlip))
	{
		UI::REMOVE_BLIP(&ElevBlip);
		ElevBlip = 0;
	}

	if (UI::DOES_BLIP_EXIST(PostOpBlip))
	{
		UI::REMOVE_BLIP(&PostOpBlip);
		PostOpBlip = 0;
	}

	if (ElevBlip != 0)
	{
		GRAPHICS::DELETE_CHECKPOINT(ElevBlip);
		ElevBlip = 0;
	}

	if (ENTITY::DOES_ENTITY_EXIST(Safe))
	{
		OBJECT::DELETE_OBJECT(&Safe);
		Safe = 0;
	}

	if (ENTITY::DOES_ENTITY_EXIST(SafeDoor))
	{
		OBJECT::DELETE_OBJECT(&SafeDoor);
		SafeDoor = 0;
	}

	if (ENTITY::DOES_ENTITY_EXIST(AccessCard))
	{
		OBJECT::DELETE_OBJECT(&AccessCard);
		AccessCard = 0;
	}

	if (AUDIO::REQUEST_SCRIPT_AUDIO_BANK("dlc_h4_Prep_FC_Sounds", false))
	{
		AUDIO::RELEASE_NAMED_SCRIPT_AUDIO_BANK("dlc_h4_Prep_FC_Sounds");
	}

	if (AUDIO::REQUEST_SCRIPT_AUDIO_BANK("DLC_HEIST3/ARCADE_GENERAL_02", false))
	{
		AUDIO::RELEASE_NAMED_SCRIPT_AUDIO_BANK("DLC_HEIST3/ARCADE_GENERAL_02");
	}

	if (AUDIO::REQUEST_SCRIPT_AUDIO_BANK("ALARM_BELL_01", false))
	{
		AUDIO::RELEASE_NAMED_SCRIPT_AUDIO_BANK("ALARM_BELL_01");
	}

	// Reset the flags/values
	IsValetCowering_FLAG = false;
	IsAlerted_FLAG = false;
	ValetSpeechStage = 0;
	ValetSpeechCooldownTimer = 0;

	if (!AUDIO::HAS_SOUND_FINISHED(AlarmSoundId) || AlarmSoundId != -1)
	{
		AUDIO::STOP_SOUND(AlarmSoundId);
		AUDIO::RELEASE_SOUND_ID(AlarmSoundId);
		AlarmSoundId = -1;
	}

	if (STREAMING::HAS_ANIM_DICT_LOADED("anim@door_trans@hinge_l@"))
	{
		STREAMING::REMOVE_ANIM_DICT("anim@door_trans@hinge_l@");
	}

	if (STREAMING::HAS_ANIM_DICT_LOADED("anim@mugging@victim@toss_ped@"))
	{
		STREAMING::REMOVE_ANIM_DICT("anim@mugging@victim@toss_ped@");
	}

	if (STREAMING::HAS_ANIM_DICT_LOADED("anim_heist@arcade_property@arcade_safe_open@male@"))
	{
		STREAMING::REMOVE_ANIM_DICT("anim_heist@arcade_property@arcade_safe_open@male@");
	}

	if (PED::IS_SYNCHRONIZED_SCENE_RUNNING(SyncScene))
	{
		PED::_0xCD9CC7E200A52A6F(SyncScene);
		SyncScene = 0;
	}

	LoadInteriors(true);
	SetupGarage(true);
}

std::string Missions::CasinoVehicleRobberyPrep1::GetApartmentName()
{
	switch (ApartmentIndex)
	{
	case 0:
	{
		return "Del Perro Heights";
	}
	case 1:
	{
		return "3 Alta Street Tower";
	}
	case 2:
	{
		return "Eclipse Towers";
	}
	}

	return "";
}

Extensions::Vector3 Missions::CasinoVehicleRobberyPrep1::EnterApartmentAnimPosition()
{
	switch (ApartmentIndex)
	{
	    case 0:
	    {
		     return { -1440.26f, -547.04f, 35.77f };
	    }
		case 1:
		{
			return { -263.461f, -970.5215f, 31.60709f };
		}
		case 2:
		{
			return { -778.3578f, 313.5395f, 86.14334f };
		}

		return { 0, 0, 0 };
	}
}

float Missions::CasinoVehicleRobberyPrep1::EnterApartmentAnimHeading()
{
	switch (ApartmentIndex)
	{
	case 0:
	{
		return 0;
	}
	case 1:
	{
		return 0.127631f;
	}
	case 2:
	{
		return 0;
	}
	}

	return 0;
}

void Missions::CasinoVehicleRobberyPrep1::HideApartmentExterior()
{
	switch (Index)
	{
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	{
		UI::_DISABLE_RADAR_THIS_FRAME();
		INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(joaat("hei_dt1_20_build2"));
		INTERIOR::_HIDE_MAP_OBJECT_THIS_FRAME(joaat("dt1_20_dt1_emissive_dt1_20"));
	}
	break;
	}
}

Extensions::Vector3 Missions::CasinoVehicleRobberyPrep1::InteriorPositions()
{
	switch (ApartmentIndex) {
	case 0:
	{
		return { -1468.021f, -529.9437f, 62.34918f };
	}
	case 1:
	{
		return { -282.3039f, -954.7815f, 85.30347f };
	}
	case 2:
	{
		return { -764.7226f, 319.1851f, 169.5963f };
	}
	}

	return { 0.0f, 0.0f, 0.0f };
}

Extensions::Vector3 Missions::CasinoVehicleRobberyPrep1::InteriorPropPositions(int index) {
	switch (index) {
	case 0:
	case 1: {
		switch (ApartmentIndex) {
		case 0:
			return { -1467.10f, -524.70f, 73.19f };
		case 1:
			return { -271.00f, -951.25f, 92.25f };
		case 2:
			return { -771.90f, 328.70f, 176.55f };
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
	return { 0.0f, 0.0f, 0.0f };
}

float Missions::CasinoVehicleRobberyPrep1::InteriorPropHeadings(int index) {
	switch (index) {
	case 0:
	case 1: {
		switch (ApartmentIndex) {
		case 0:
			return -55.0f;
		case 1:
			return 160.0f;
		case 2:
			return -90.0f;
		default:
			break;
		}
		break;
	}
    }
    return 0.0f;
}

Extensions::Vector3 Missions::CasinoVehicleRobberyPrep1::ValetSpawnPositions()
{
	switch (ApartmentIndex)
	{
	case 0:
	{
		return { -1457.390f, -552.226f, 72.879f };
	}
	case 1:
	{
		return { -288.200f, -963.860f, 91.108f };
	}
	case 2:
	{
		return { -761.211f, 315.596f, 170.596f };
	}
	}

	return { 0, 0, 0 };
}

float Missions::CasinoVehicleRobberyPrep1::ValetSpawnHeadings()
{
	switch (ApartmentIndex)
	{
	case 0:
	{
		return -25.0f;
	}
	case 1:
	{
		return -70.0f;
	}
	case 2:
	{
		return 50.0f;
	}
	}
}

void Missions::CasinoVehicleRobberyPrep1::SetupGuard(int ped)
{
	if (ENTITY::DOES_ENTITY_EXIST(ped))
	{
		PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, true);
		PED::SET_PED_SEEING_RANGE(ped, 4.0f);
		PED::SET_PED_HEARING_RANGE(ped, 50.0f);
		PED::SET_PED_VISUAL_FIELD_PERIPHERAL_RANGE(ped, 2.0f);
		PED::SET_PED_VISUAL_FIELD_CENTER_ANGLE(ped, 50.0f);
		PED::SET_PED_VISUAL_FIELD_MIN_ANGLE(ped, -90.0f);
		PED::SET_PED_VISUAL_FIELD_MAX_ANGLE(ped, 90.0f);
		PED::SET_PED_AS_ENEMY(ped, true);
		ENTITY::SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(ped, true);
		ENTITY::SET_ENTITY_IS_TARGET_PRIORITY(ped, 1, 0);

		int attachedBlip = UI::ADD_BLIP_FOR_ENTITY(ped);
		UI::SET_BLIP_SPRITE(attachedBlip, 270);
		UI::SET_BLIP_COLOUR(attachedBlip, 1); /* Red */
		UI::SET_BLIP_SCALE(attachedBlip, 0.7f);
		UI::SET_BLIP_AS_FRIENDLY(attachedBlip, false);
		UI::SET_BLIP_AS_SHORT_RANGE(attachedBlip, true);
		invoke<Void>(0x13127EC3665E8EE1, attachedBlip, true, 11); /* SET_BLIP_SHOW_CONE */

		invoke<Void>(0xBF0FD6E56C964FCB, ped, joaat("WEAPON_SMG"), 0, true, true); /* GIVE_WEAPON_TO_PED */
		WEAPON::SET_PED_INFINITE_AMMO(ped, true, joaat("WEAPON_SMG"));
		WEAPON::SET_PED_INFINITE_AMMO_CLIP(ped, true);
		PED::SET_PED_CONFIG_FLAG(ped, 38, true);
		PED::SET_PED_COMBAT_ATTRIBUTES(ped, 13, true);
		PED::SET_PED_COMBAT_ATTRIBUTES(ped, 39, true);
		PED::SET_PED_COMBAT_MOVEMENT(ped, 3);
		PED::SET_PED_ACCURACY(ped, 50);
		AI::TASK_START_SCENARIO_IN_PLACE(ped, "WORLD_HUMAN_GUARD_STAND", 0, false);
	}
}

void Missions::CasinoVehicleRobberyPrep1::CheckOnGuards()
{
	switch (Index)
	{
	case 6:
	case 7:
	{
		for (auto ped = Guards.begin(); ped != Guards.end(); ++ped)
		{
			if (ENTITY::DOES_ENTITY_EXIST(*ped))
			{
				int attachedBlip = UI::GET_BLIP_FROM_ENTITY(*ped);

				if (ENTITY::IS_ENTITY_DEAD(*ped))
				{
					if (UI::DOES_BLIP_EXIST(attachedBlip) && attachedBlip != 0)
					{
						UI::REMOVE_BLIP(&attachedBlip);
					}
				}

				if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(*ped, PLAYER::PLAYER_PED_ID()) || PED::IS_PED_IN_COMBAT(*ped, PLAYER::PLAYER_PED_ID()) || PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()) && !WEAPON::IS_PED_CURRENT_WEAPON_SILENCED(PLAYER::PLAYER_PED_ID()))
				{
					AUDIO::TRIGGER_MUSIC_EVENT("CH_GUNFIGHT");
					IsAlerted_FLAG = true;
				}

				if (IsAlerted_FLAG)
				{
					if (UI::DOES_BLIP_EXIST(attachedBlip) && attachedBlip != 0)
					{
						invoke<Void>(0x13127EC3665E8EE1, attachedBlip, false, 11); /* SET_BLIP_SHOW_CONE */
					}

					if (!ENTITY::IS_ENTITY_DEAD(*ped))
					{
						PED::SET_PED_RELATIONSHIP_GROUP_HASH(*ped, joaat("GOON"));
						PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5 /* Hate */, joaat("GOON"), PED::GET_PED_RELATIONSHIP_GROUP_HASH(PLAYER::PLAYER_PED_ID()));
						PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5 /* Hate */, PED::GET_PED_RELATIONSHIP_GROUP_HASH(PLAYER::PLAYER_PED_ID()), joaat("GOON"));
						
						if (AI::GET_SCRIPT_TASK_STATUS(*ped, joaat("SCRIPT_TASK_COMBAT_PED") != 1))
						{
							AI::TASK_COMBAT_PED(*ped, PLAYER::PLAYER_PED_ID(), 16, 0);
						}
					}

					if (AlarmSoundId == -1 && AUDIO::REQUEST_SCRIPT_AUDIO_BANK("ALARM_BELL_01", false))
					{
						AlarmSoundId = AUDIO::GET_SOUND_ID();
						AUDIO::PLAY_SOUND_FROM_COORD(AlarmSoundId, "Bell_01", 229.9559f, -981.7928f, -99.66071f, "ALARMS_SOUNDSET", false, 0, false);
					}
				}
			}
		}
	}
	break;
	}
}

void Missions::CasinoVehicleRobberyPrep1::LoadInteriors(bool cleanup)
{
	if (cleanup)
	{
		if (ENTITY::DOES_ENTITY_EXIST(Valet))
		{
			PED::DELETE_PED(&Valet);
			Valet = 0;
		}

		if (ENTITY::DOES_ENTITY_EXIST(Safe))
		{
			OBJECT::DELETE_OBJECT(&Safe);
			Safe = 0;
		}

		if (ENTITY::DOES_ENTITY_EXIST(SafeDoor))
		{
			OBJECT::DELETE_OBJECT(&SafeDoor);
			SafeDoor = 0;
		}

		if (ENTITY::DOES_ENTITY_EXIST(AccessCard))
		{
			OBJECT::DELETE_OBJECT(&AccessCard);
			AccessCard = 0;
		}

		if (UI::DOES_BLIP_EXIST(SafeBlip))
		{
			UI::REMOVE_BLIP(&SafeBlip);
			SafeBlip = 0;
		}
	}
	else
	{
		int interiorId = INTERIOR::GET_INTERIOR_AT_COORDS(InteriorPositions().x, InteriorPositions().y, InteriorPositions().z);

		if (INTERIOR::IS_VALID_INTERIOR(interiorId))
		{
			if (INTERIOR::IS_INTERIOR_CAPPED(interiorId))
			{
				INTERIOR::CAP_INTERIOR(interiorId, false);
			}

			if (INTERIOR::IS_INTERIOR_DISABLED(interiorId))
			{
				INTERIOR::DISABLE_INTERIOR(interiorId, false);
			}
		}

		int interiorId2 = INTERIOR::GET_INTERIOR_AT_COORDS(229.9559f, -981.7928f, -99.66071f);

		if (INTERIOR::IS_VALID_INTERIOR(interiorId2))
		{
			if (INTERIOR::IS_INTERIOR_CAPPED(interiorId2))
			{
				INTERIOR::CAP_INTERIOR(interiorId2, false);
			}

			if (INTERIOR::IS_INTERIOR_DISABLED(interiorId2))
			{
				INTERIOR::DISABLE_INTERIOR(interiorId2, false);
			}
		}

		WAIT(500); // wait 5ms

		STREAMING::REQUEST_MODEL(joaat("S_M_Y_Casino_01"));
		while (!STREAMING::HAS_MODEL_LOADED(joaat("S_M_Y_Casino_01"))) WAIT(0);
		Valet = PED::CREATE_PED(26, joaat("S_M_Y_Casino_01"), ValetSpawnPositions().x, ValetSpawnPositions().y, ValetSpawnPositions().z, ValetSpawnHeadings(), false, true);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("S_M_Y_Casino_01"));
		if (ENTITY::DOES_ENTITY_EXIST(Valet))
		{
			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Valet, true);
			PED::SET_PED_CONFIG_FLAG(Valet, 281, true);
			PED::SET_PED_CONFIG_FLAG(Valet, 410, true);
			ENTITY::SET_ENTITY_MAX_HEALTH(Valet, 800);
			ENTITY::SET_ENTITY_HEALTH(Valet, 800);

			// ped comps for the valet seen outside the casino
			PED::SET_PED_COMPONENT_VARIATION(Valet, 0, 5, 1, 0);
			PED::SET_PED_COMPONENT_VARIATION(Valet, 1, 1, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(Valet, 2, 5, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(Valet, 3, 1, 1, 0);
			PED::SET_PED_COMPONENT_VARIATION(Valet, 4, 0, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(Valet, 6, 1, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(Valet, 7, 2, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(Valet, 8, 3, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(Valet, 10, 1, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(Valet, 11, 1, 1, 0);
		}

		STREAMING::REQUEST_MODEL(joaat("m23_2_prop_m32_arcade_safe_body"));
		while (!STREAMING::HAS_MODEL_LOADED(joaat("m23_2_prop_m32_arcade_safe_body"))) WAIT(0);
		Safe = OBJECT::CREATE_OBJECT(joaat("m23_2_prop_m32_arcade_safe_body"), InteriorPropPositions(0).x, InteriorPropPositions(0).y, InteriorPropPositions(0).z, false, true, false);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("m23_2_prop_m32_arcade_safe_body"));
		if (ENTITY::DOES_ENTITY_EXIST(Safe))
		{
			ENTITY::SET_ENTITY_HEADING(Safe, InteriorPropHeadings(0));
			ENTITY::FREEZE_ENTITY_POSITION(Safe, true);

			STREAMING::REQUEST_MODEL(joaat("m23_2_prop_m32_accesscard_01a"));
			while (!STREAMING::HAS_MODEL_LOADED(joaat("m23_2_prop_m32_accesscard_01a"))) WAIT(0);
			AccessCard = OBJECT::CREATE_OBJECT_NO_OFFSET(joaat("m23_2_prop_m32_accesscard_01a"), InteriorPropPositions(0).x, InteriorPropPositions(0).y, InteriorPropPositions(0).z, false, true, false);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("m23_2_prop_m32_accesscard_01a"));

			if (ENTITY::DOES_ENTITY_EXIST(AccessCard))
			{
				// this works perfectly so don't change it
				ENTITY::ATTACH_ENTITY_TO_ENTITY(AccessCard, Safe, -1, -0.25f, 0.25f, 0.03f, 0.0f, 0.0f, 0.0f, false, false, false, false, 2, true);
			}
		}

		STREAMING::REQUEST_MODEL(joaat("m23_2_prop_m32_arcade_safe_door"));
		while (!STREAMING::HAS_MODEL_LOADED(joaat("m23_2_prop_m32_arcade_safe_door"))) WAIT(0);
		SafeDoor = OBJECT::CREATE_OBJECT(joaat("m23_2_prop_m32_arcade_safe_door"), InteriorPropPositions(1).x, InteriorPropPositions(1).y, InteriorPropPositions(1).z + 0.035f, false, true, false);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("m23_2_prop_m32_arcade_safe_door"));
		if (ENTITY::DOES_ENTITY_EXIST(SafeDoor))
		{
			ENTITY::SET_ENTITY_HEADING(SafeDoor, InteriorPropHeadings(1));
			ENTITY::FREEZE_ENTITY_POSITION(SafeDoor, true);
		}
	}
}

Extensions::Vector3 Missions::CasinoVehicleRobberyPrep1::ApartmentSpawnPosition()
{
	switch (ApartmentIndex)
	{
	case 0:
	{
		return { -1454.095f, -537.876f, 74.044f };
	}
	case 1:
	{
		return { -280.01f, -942.05f, 92.0f };
	}
	case 2:
	{
		return { -778.98f, 317.18f, 177.22f };
	}

	return { 0, 0, 0 };
	}
}

float Missions::CasinoVehicleRobberyPrep1::ApartmentSpawnHeading()
{
	switch (ApartmentIndex)
	{
	case 0:
	{
		return -90.0f;
	}
	case 1:
	{
		return 160.0f;
	}
	case 2:
	{
		return 90.0f;
	}

	return 90.0f;
	}
}

void Missions::CasinoVehicleRobberyPrep1::OpenSafe()
{
	if (ENTITY::DOES_ENTITY_EXIST(Safe) && ENTITY::DOES_ENTITY_EXIST(SafeDoor))
	{
		PLAYER::SET_EVERYONE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), true);
		PED::SET_PED_CAN_SWITCH_WEAPON(PLAYER::PLAYER_PED_ID(), false);
		WEAPON::SET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), joaat("WEAPON_UNARMED"), true);
		AUDIO::RELEASE_NAMED_SCRIPT_AUDIO_BANK("DLC_HEIST3/ARCADE_GENERAL_02");
		AUDIO::REQUEST_SCRIPT_AUDIO_BANK("DLC_HEIST3/ARCADE_GENERAL_02", false);
		STREAMING::REQUEST_ANIM_DICT("anim_heist@arcade_property@arcade_safe_open@male@");
		while (!STREAMING::HAS_ANIM_DICT_LOADED("anim_heist@arcade_property@arcade_safe_open@male@")) WAIT(0);
		STREAMING::REQUEST_ANIM_DICT("anim@scripted@player@freemode@tun_prep_grab_midd_ig3@male@");
		while (!STREAMING::HAS_ANIM_DICT_LOADED("anim@scripted@player@freemode@tun_prep_grab_midd_ig3@male@")) WAIT(0);
		Vector3 offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(SafeDoor, 6.155f, 1.205f, -2.369f);
		float heading = ENTITY::GET_ENTITY_HEADING(SafeDoor) + 90.0f; // We add 90 degrees - ps this anim offset is weird ngl
		Vector3 offset2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(SafeDoor, -0.31f, -0.81f, 0.0f); // Slide to offset
		
		AI::TASK_PED_SLIDE_TO_COORD(PLAYER::PLAYER_PED_ID(), offset2.x, offset2.y, offset2.z, heading, 0.75f);
		while (AI::GET_SCRIPT_TASK_STATUS(PLAYER::PLAYER_PED_ID(), PLAYER::PLAYER_PED_ID()) == 0) WAIT(0);
		while (AI::GET_SCRIPT_TASK_STATUS(PLAYER::PLAYER_PED_ID(), PLAYER::PLAYER_PED_ID()) == 1) WAIT(0);

		SyncScene = PED::CREATE_SYNCHRONIZED_SCENE(offset.x, offset.y, offset.z, 0.0f, 0.0f, heading, 2);
		AI::TASK_SYNCHRONIZED_SCENE(PLAYER::PLAYER_PED_ID(), SyncScene, "anim_heist@arcade_property@arcade_safe_open@male@", "safe_open", 8.0f, -1.0f, 0, 0, 8.0f, 0);
		ENTITY::PLAY_SYNCHRONIZED_ENTITY_ANIM(SafeDoor, SyncScene, "safe_open_safedoor", "anim_heist@arcade_property@arcade_safe_open@male@", 8.0f, -1.0f, 0, 8.0f);
		PED::_0x2208438012482A1A(PLAYER::PLAYER_PED_ID(), true, true); /* FORCE_PED_AI_AND_ANIMATION_UPDATE */
		ENTITY::FORCE_ENTITY_AI_AND_ANIMATION_UPDATE(SafeDoor);
		while (PED::GET_SYNCHRONIZED_SCENE_PHASE(SyncScene) < 0.999f) WAIT(0);
		PED::_0xCD9CC7E200A52A6F(SyncScene); /* TAKE_OWNERSHIP_OF_SYNCHRONIZED_SCENE */
		SyncScene = 0;
		STREAMING::REMOVE_ANIM_DICT("anim_heist@arcade_property@arcade_safe_open@male@");
		AI::TASK_PLAY_ANIM(PLAYER::PLAYER_PED_ID(), "anim@scripted@player@freemode@tun_prep_grab_midd_ig3@male@", "tun_prep_grab_midd_ig3", 8.0f, -8.0f, -1, -0, 1.0f, true, true, true);
		if (ENTITY::DOES_ENTITY_EXIST(AccessCard))
		{
			OBJECT::DELETE_OBJECT(&AccessCard);
			AccessCard = 0;
		}
		AUDIO::PLAY_SOUND_FRONTEND(-1, "REMOTE_PLYR_CASH_COUNTER_COMPLETE", "DLC_HEISTS_GENERAL_FRONTEND_SOUNDS", false);
		AI::CLEAR_PED_TASKS(PLAYER::PLAYER_PED_ID());
		PLAYER::SET_EVERYONE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), false);
		PED::SET_PED_CAN_SWITCH_WEAPON(PLAYER::PLAYER_PED_ID(), true);
		AUDIO::RELEASE_NAMED_SCRIPT_AUDIO_BANK("DLC_HEIST3/ARCADE_GENERAL_02");
	}
}

Extensions::Vector3 Missions::CasinoVehicleRobberyPrep1::ElevatorCoronaPosition()
{
	switch (ApartmentIndex)
	{
	case 0:
	{
		return { -1452.318f, -540.545f, 73.030f };
	}
	case 1:
	{
		return { -272.10f, -940.30f, 91.51f };
	}
	case 2:
	{
		return { -781.82f, 323.80f, 175.80f };
	}
	}
}

void Missions::CasinoVehicleRobberyPrep1::SetupGarage(bool cleanup)
{
	if (cleanup)
	{
		if (GarageVehicles.size() > 0)
		{
			for (auto vehicle : GarageVehicles)
			{
				if (ENTITY::DOES_ENTITY_EXIST(vehicle))
				{
					if (ENTITY::IS_ENTITY_A_VEHICLE(vehicle))
					{
						VEHICLE::DELETE_VEHICLE(&vehicle);
					}
				}
			}

			GarageVehicles.clear();
		}

		if (Guards.size() > 0)
		{
			for (auto ped : Guards)
			{
				if (ENTITY::DOES_ENTITY_EXIST(ped))
				{
					if (ENTITY::IS_ENTITY_A_PED(ped))
					{
						PED::DELETE_PED(&ped);
					}
				}
			}

			Guards.clear();
		}
	}
	else
	{
		int vehicle, vehicle2, vehicle3, vehicle4, vehicle5, vehicle6, vehicle7, vehicle8, vehicle9, vehicle10;

		STREAMING::REQUEST_MODEL(joaat("buffalo2"));
		while (!STREAMING::HAS_MODEL_LOADED(joaat("buffalo2"))) WAIT(0);
		vehicle = VEHICLE::CREATE_VEHICLE(joaat("buffalo2"), 233.2209f, -1000.450f, -99.3779f, 93.0f, false, true);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("buffalo2"));
		if (ENTITY::DOES_ENTITY_EXIST(vehicle))
		{
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(vehicle, 2);
			invoke<Void>(0x260BE8F09E326A20, vehicle, 0.0f, -1, true); /* BRING_VEHICLE_TO_HALT */
			GarageVehicles.push_back(vehicle);
		}

		STREAMING::REQUEST_MODEL(joaat("tenf2"));
		while (!STREAMING::HAS_MODEL_LOADED(joaat("tenf2"))) WAIT(0);
		vehicle2 = VEHICLE::CREATE_VEHICLE(joaat("tenf2"), 233.0905f, -995.3500f, -99.6447f, 93.0f, false, true);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("tenf2"));
		if (ENTITY::DOES_ENTITY_EXIST(vehicle2))
		{
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(vehicle2, 2);
			invoke<Void>(0x260BE8F09E326A20, vehicle2, 0.0f, -1, true);
			GarageVehicles.push_back(vehicle2);
		}

		STREAMING::REQUEST_MODEL(joaat("brioso3"));
		while (!STREAMING::HAS_MODEL_LOADED(joaat("brioso3"))) WAIT(0);
		vehicle3 = VEHICLE::CREATE_VEHICLE(joaat("brioso3"), 233.0960f, -990.9000f, -99.6764f, 93.0f, false, true);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("brioso3"));
		if (ENTITY::DOES_ENTITY_EXIST(vehicle3))
		{
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(vehicle3, 2);
			invoke<Void>(0x260BE8F09E326A20, vehicle3, 0.0f, -1, true);
			GarageVehicles.push_back(vehicle3);
		}

		STREAMING::REQUEST_MODEL(joaat("asea"));
		while (!STREAMING::HAS_MODEL_LOADED(joaat("asea"))) WAIT(0);
		vehicle4 = VEHICLE::CREATE_VEHICLE(joaat("asea"), 233.0454f, -986.9224f, -99.4338f, 93.0f, false, true);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("asea"));
		if (ENTITY::DOES_ENTITY_EXIST(vehicle4))
		{
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(vehicle4, 2);
			invoke<Void>(0x260BE8F09E326A20, vehicle4, 0.0f, -1, true);
			GarageVehicles.push_back(vehicle4);
		}

		STREAMING::REQUEST_MODEL(joaat("baller5"));
		while (!STREAMING::HAS_MODEL_LOADED(joaat("baller5"))) WAIT(0);
		vehicle5 = VEHICLE::CREATE_VEHICLE(joaat("baller5"), 232.9861f, -982.3032f, -99.0825f, 93.0f, false, true);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("baller5"));
		if (ENTITY::DOES_ENTITY_EXIST(vehicle5))
		{
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(vehicle5, 2);
			invoke<Void>(0x260BE8F09E326A20, vehicle5, 0.0f, -1, true);
			GarageVehicles.push_back(vehicle5);
		}

		STREAMING::REQUEST_MODEL(joaat("kanjosj"));
		while (!STREAMING::HAS_MODEL_LOADED(joaat("kanjosj"))) WAIT(0);
		vehicle6 = VEHICLE::CREATE_VEHICLE(joaat("kanjosj"), 224.4626f, -1000.037f, -99.6869f, -93.0f, false, true);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("kanjosj"));
		if (ENTITY::DOES_ENTITY_EXIST(vehicle6))
		{
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(vehicle6, 2);
			invoke<Void>(0x260BE8F09E326A20, vehicle6, 0.0f, -1, true);
			GarageVehicles.push_back(vehicle6);
		}

		STREAMING::REQUEST_MODEL(joaat("jb700"));
		while (!STREAMING::HAS_MODEL_LOADED(joaat("jb700"))) WAIT(0);
		vehicle7 = VEHICLE::CREATE_VEHICLE(joaat("jb700"), 224.6429f, -995.2674f, -99.4569f, -93.0f, false, true);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("jb700"));
		if (ENTITY::DOES_ENTITY_EXIST(vehicle7))
		{
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(vehicle7, 2);
			invoke<Void>(0x260BE8F09E326A20, vehicle7, 0.0f, -1, true);
			GarageVehicles.push_back(vehicle7);
		}

		STREAMING::REQUEST_MODEL(joaat("btype2"));
		while (!STREAMING::HAS_MODEL_LOADED(joaat("btype2"))) WAIT(0);
		vehicle8 = VEHICLE::CREATE_VEHICLE(joaat("btype2"), 224.5486f, -990.7986f, -99.6809f, -93.0f, false, true);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("btype2"));
		if (ENTITY::DOES_ENTITY_EXIST(vehicle8))
		{
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(vehicle8, 2);
			invoke<Void>(0x260BE8F09E326A20, vehicle8, 0.0f, -1, true);
			GarageVehicles.push_back(vehicle8);
		}

		STREAMING::REQUEST_MODEL(joaat("boxville4"));
		while (!STREAMING::HAS_MODEL_LOADED(joaat("boxville4"))) WAIT(0);
		vehicle9 = VEHICLE::CREATE_VEHICLE(joaat("boxville4"), 224.5974f, -986.8073f, -99.1003f, -93.0f, false, true);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("boxville4"));
		if (ENTITY::DOES_ENTITY_EXIST(vehicle9))
		{
			// VEHICLE::SET_VEHICLE_DOORS_LOCKED(vehicle9, 2);
			invoke<Void>(0x260BE8F09E326A20, vehicle9, 0.0f, -1, true);
			GarageVehicles.push_back(vehicle9);
		}

		STREAMING::REQUEST_MODEL(joaat("banshee3"));
		while (!STREAMING::HAS_MODEL_LOADED(joaat("banshee3"))) WAIT(0);
		vehicle10 = VEHICLE::CREATE_VEHICLE(joaat("banshee3"), 224.6300f, -982.2000f, -99.4410f, -93.0f, false, true);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("banshee3"));
		if (ENTITY::DOES_ENTITY_EXIST(vehicle10))
		{
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(vehicle10, 2);
			invoke<Void>(0x260BE8F09E326A20, vehicle10, 0.0f, -1, true);
			GarageVehicles.push_back(vehicle10);
		}

		int guard, guard2, guard3, guard4, guard5;

		STREAMING::REQUEST_MODEL(joaat("S_M_Y_WestSec_01"));
		while (!STREAMING::HAS_MODEL_LOADED(joaat("S_M_Y_WestSec_01"))) WAIT(0);
		guard = PED::CREATE_PED(26, joaat("S_M_Y_WestSec_01"), 224.1553f, -984.4158f, -99.0040f, -180.0f, false, true);
		Guards.push_back(guard);
		guard2 = PED::CREATE_PED(26, joaat("S_M_Y_WestSec_01"), 220.1553f, -984.4158f, -99.0040f, -180.0f, false, true);
		Guards.push_back(guard2);
		guard3 = PED::CREATE_PED(26, joaat("S_M_Y_WestSec_01"), 225.0182f, -979.5560f, -99.0040f, -180.0f, false, true);
		Guards.push_back(guard3);
		guard4 = PED::CREATE_PED(26, joaat("S_M_Y_WestSec_01"), 230.1145f, -988.9550f, -99.0040f, -180.0f, false, true);
		Guards.push_back(guard4);
		guard5 = PED::CREATE_PED(26, joaat("S_M_Y_WestSec_01"), 229.1145f, -988.9550f, -99.0040f, 180.0f, false, true);
		Guards.push_back(guard5);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("S_M_Y_WestSec_01"));

		for (auto ped : Guards)
		{
			if (ENTITY::DOES_ENTITY_EXIST(ped))
			{
				SetupGuard(ped);
			}
		}
	}
}