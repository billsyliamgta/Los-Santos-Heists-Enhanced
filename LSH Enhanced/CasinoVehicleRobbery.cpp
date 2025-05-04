#pragma once

#include "CasinoVehicleRobbery.h"
#include "script.h"
#include "MidsizedMessage.h"
#include "Screen.h"
#include "script.h"
#include "string"
#include "RobberyCompleteShard.h"
#include "RobberyCompleteShardBlock.h"
#include "Debug.h"

namespace Missions
{
	void CasinoVehicleRobbery::Update()
	{
		BaseMission::Update();
		FailConditions();
		CheckOnGuards();
		TrackVehicleDamage();
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
			if (ENTITY::DOES_ENTITY_EXIST(Boxville))
			{
				if (!PED::IS_PED_IN_VEHICLE(PLAYER::PLAYER_PED_ID(), Boxville, true))
				{
					if (UI::DOES_BLIP_EXIST(BoxvilleBlip))
					{
						if (UI::GET_BLIP_ALPHA(BoxvilleBlip) != 255)
						{
							UI::SET_BLIP_ALPHA(BoxvilleBlip, 255);
						}
					}

					if (UI::DOES_BLIP_EXIST(ParkBoxvilleBlip))
					{
						if (UI::GET_BLIP_ALPHA(ParkBoxvilleBlip) != 0)
						{
							UI::SET_BLIP_ALPHA(ParkBoxvilleBlip, 0);
						}

						if (ScriptBlipRoute_FLAG)
						{
							UI::SET_BLIP_ROUTE(ParkBoxvilleBlip, false);
							ScriptBlipRoute_FLAG = false;
						}
					}

					UI::Screen::ShowSubtitle("Enter the back of the ~b~Post OP Van.");

					if (AI::GET_SCRIPT_TASK_STATUS(BellePed, joaat("SCRIPT_TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE")) == 1)
					{
						AI::TASK_VEHICLE_PARK(BellePed, Boxville, ENTITY::GET_ENTITY_COORDS(Boxville, false).x, ENTITY::GET_ENTITY_COORDS(Boxville, false).y, ENTITY::GET_ENTITY_COORDS(Boxville, false).z, ENTITY::GET_ENTITY_HEADING(Boxville), 1 /* Park Forward */, 20.0f, true);
					}

					if (GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true).x, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true).y, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true).z, ENTITY::GET_ENTITY_COORDS(Boxville, false).x, ENTITY::GET_ENTITY_COORDS(Boxville, false).y, ENTITY::GET_ENTITY_COORDS(Boxville, false).z, false) < 10.0f)
					{
						if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, 23))
						{
							AI::TASK_ENTER_VEHICLE(PLAYER::PLAYER_PED_ID(), Boxville, -1, 1, 1.0f, 0, 0);
						}
					}
				}
				else
				{
					if (UI::DOES_BLIP_EXIST(BoxvilleBlip))
					{
						if (UI::GET_BLIP_ALPHA(BoxvilleBlip) != 0)
						{
							UI::SET_BLIP_ALPHA(BoxvilleBlip, 0);
						}
					}

					if (!UI::DOES_BLIP_EXIST(ParkBoxvilleBlip))
					{
						ParkBoxvilleBlip = UI::ADD_BLIP_FOR_COORD(860.0482f, 19.10682f, 78.94351f);
						UI::SET_BLIP_SPRITE(ParkBoxvilleBlip, 1);
						UI::SET_BLIP_COLOUR(ParkBoxvilleBlip, 5);
						ParkBoxvilleCheckpoint = GRAPHICS::CREATE_CHECKPOINT(47, 860.0f, 19.1f, 78.0f, 0.0f, 0.0f, 0.0f, 1.0f, 240, 200, 80, 155, 0);
						GRAPHICS::SET_CHECKPOINT_CYLINDER_HEIGHT(ParkBoxvilleCheckpoint, 0.7f, 0.7f, 0.7f);
					}
					else
					{
						if (UI::GET_BLIP_ALPHA(ParkBoxvilleBlip) != 255)
						{
							UI::SET_BLIP_ALPHA(ParkBoxvilleBlip, 255);
						}

						if (!ScriptBlipRoute_FLAG)
						{
							UI::SET_BLIP_ROUTE(ParkBoxvilleBlip, true);
							ScriptBlipRoute_FLAG = true;
						}

						GRAPHICS::SET_CHECKPOINT_RGBA(ParkBoxvilleCheckpoint, 240, 200, 80, 155);
					}

					if (AI::GET_SCRIPT_TASK_STATUS(BellePed, joaat("SCRIPT_TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE")) != 1)
					{
						AI::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(BellePed, Boxville, 975.0f, 6.6365f, 80.0609f, 100.0f, 0x400C0025, -1.0f);
					}

					UI::Screen::ShowSubtitle("Wait for ~b~Belle ~w~to drive to the ~y~Casino.");

					if (GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(ENTITY::GET_ENTITY_COORDS(Boxville, false).x, ENTITY::GET_ENTITY_COORDS(Boxville, false).y, ENTITY::GET_ENTITY_COORDS(Boxville, false).z, 860.0f, 19.1f, 78.0f, false) < 3.0f)
					{
						if (ParkBoxvilleCheckpoint != 0)
						{
							AUDIO::PLAY_SOUND_FRONTEND(-1, "CHECKPOINT_PERFECT", "HUD_MINI_GAME_SOUNDSET", false);
							GRAPHICS::DELETE_CHECKPOINT(ParkBoxvilleCheckpoint);
							ParkBoxvilleCheckpoint = 0;
						}

						VEHICLE::_TASK_BRING_VEHICLE_TO_HALT(Boxville, 4.0f, -1, 0);
						while (invoke<bool>(0xC69BB1D832A710EF)) WAIT(0); /* If the vehicle is being brought to a halt */

						CAM::DO_SCREEN_FADE_OUT(250);
						while (CAM::IS_SCREEN_FADING_OUT()) WAIT(0);

						AUDIO::LOAD_STREAM("Resupply-Repairman-Van", "DLC_Biker_Delivery_Sounds");
						AUDIO::PLAY_STREAM_FRONTEND();
						while (AUDIO::IS_STREAM_PLAYING()) WAIT(0);

						if (UI::DOES_BLIP_EXIST(ParkBoxvilleBlip))
						{
							UI::REMOVE_BLIP(&ParkBoxvilleBlip);
							ParkBoxvilleBlip = 0;
						}

						if (ENTITY::DOES_ENTITY_EXIST(Boxville))
						{
							VEHICLE::DELETE_VEHICLE(&Boxville);
							Boxville = 0;
						}

						if (UI::DOES_BLIP_EXIST(BelleBlip))
						{
							UI::REMOVE_BLIP(&BelleBlip);
							BelleBlip = 0;
						}

						if (ENTITY::DOES_ENTITY_EXIST(BellePed))
						{
							PED::DELETE_PED(&BellePed);
							BellePed = 0;
						}

						LoadInteriors(false, false);
						SpawnHotelGuards(false);
						WAIT(250);
						JumpOutCrate();
						UI::Screen::SendTextNotification("char_belle", "Belle", "Podium Robbery", "Cuh you in? Cool, now get to that elevator shaft asap - btw you stink of horse shit.");
						Index = 2;
					}
				}
				if (ENTITY::DOES_ENTITY_EXIST(BellePed))
				{
					if (UI::DOES_BLIP_EXIST(BelleBlip))
					{
						if (!PED::IS_PED_IN_VEHICLE(BellePed, Boxville, true))
						{
							if (UI::GET_BLIP_ALPHA(BelleBlip) != 255)
							{
								UI::SET_BLIP_ALPHA(BelleBlip, 255);
							}
						}
						else
						{
							if (UI::GET_BLIP_ALPHA(BelleBlip) != 0)
							{
								UI::SET_BLIP_ALPHA(BelleBlip, 0);
							}
						}
					}
				}
			}
		}
		break;
		case 2:
		{
			Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			Vector3 hatchCoords = ENTITY::GET_ENTITY_COORDS(LiftShaftHatch, false);

			if (PlayerLocatedHatch_FLAG)
			{
				UI::Screen::ShowSubtitle("Open the ~g~elevator hatch.");

				if (GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(playerCoords.x, playerCoords.y, playerCoords.z, hatchCoords.x, hatchCoords.y, hatchCoords.z, false) < 2)
				{
					UI::DISPLAY_HELP_TEXT_THIS_FRAME("VRPC_INTR_3" /* GXT: Press ~INPUT_CONTEXT~ to open the elevator hatch. */, true);
					if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, 51))
					{
						UI::DISPLAY_HUD(false);
						UI::DISPLAY_RADAR(false);
						SpawnHotelGuards(true);

						if (UI::DOES_BLIP_EXIST(LiftShaftBlip))
						{
							UI::REMOVE_BLIP(&LiftShaftBlip);
							LiftShaftBlip = 0;
						}

						CUTSCENE::REQUEST_CUTSCENE("xm4_rob_cas_mcs1", 8);
						while (!CUTSCENE::HAS_THIS_CUTSCENE_LOADED("xm4_rob_cas_mcs1"))
						{
							WAIT(0);
						}

						int drawables[12];
						int textures[12];
						for (int i = 0; i < 12; i++)
						{
							drawables[i] = PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(), i);
							textures[i] = PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(), i);
						}

						CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(PLAYER::PLAYER_PED_ID(), (Any*)"MP_1", 0, 0, 0x40);

						CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"MP_2", 3, 0, 0x40);
						CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"Player_Pulley_2", 3, 0, 0x40);
						CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"Rope_Tie_2", 3, 0, 0x40);
						CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"Player_Rope_2", 3, 0, 0x40);

						CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"MP_3", 3, 0, 0x40);
						CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"Player_Pulley_3", 3, 0, 0x40);
						CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"Rope_Tie_3", 3, 0, 0x40);
						CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"Player_Rope_3", 3, 0, 0x40);

						CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"MP_4", 3, 0, 0x40);
						CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"Player_Pulley_4", 3, 0, 0x40);
						CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"Rope_Tie_4", 3, 0, 0x40);
						CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"Player_Rope_4", 3, 0, 0x40);

						if (ENTITY::DOES_ENTITY_EXIST(LiftShaft))
						{
							ENTITY::SET_ENTITY_VISIBLE(LiftShaft, false, false);
						}

						if (ENTITY::DOES_ENTITY_EXIST(LiftShaftHatch))
						{
							ENTITY::SET_ENTITY_VISIBLE(LiftShaftHatch, false, false);
						}

						CUTSCENE::START_CUTSCENE(8);
						WAIT(500);
						for (int i = 0; i < 12; i++)
						{
							PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i, drawables[i], textures[i], 0);
						}

						while (!CUTSCENE::IS_CUTSCENE_PLAYING())
						{
							WAIT(0);
						}

						while (CUTSCENE::GET_CUTSCENE_TIME() < CUTSCENE::GET_CUTSCENE_TOTAL_DURATION() - 250)
						{
							CONTROLS::DISABLE_CONTROL_ACTION(0, 18 /* INPUT_SKIP_CUTSCENE */, true);
							WAIT(0);
						}

						if (ENTITY::DOES_ENTITY_EXIST(LiftShaft))
						{
							OBJECT::DELETE_OBJECT(&LiftShaft);
							LiftShaft = 0;
						}

						if (ENTITY::DOES_ENTITY_EXIST(LiftShaftHatch))
						{
							OBJECT::DELETE_OBJECT(&LiftShaftHatch);
							LiftShaftHatch = 0;
						}

						func_6767(0);
						if (!CAM::IS_SCREEN_FADING_OUT() && !CAM::IS_SCREEN_FADED_OUT())
						{
							CAM::DO_SCREEN_FADE_OUT(250);
						}

						while (CAM::IS_SCREEN_FADING_OUT())
						{
							WAIT(0);
						}

						CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
						CUTSCENE::REMOVE_CUTSCENE();
						WAIT(500);
						CUTSCENE::REQUEST_CUTSCENE("xm4_rob_cas_mcs2", 8);
						while (!CUTSCENE::HAS_THIS_CUTSCENE_LOADED("xm4_rob_cas_mcs2"))
						{
							WAIT(0);
						}
						Index = 3;
					}
				}
			}
			else
			{
				UI::Screen::ShowSubtitle("Locate the elevator hatch.");

				if (GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(playerCoords.x, playerCoords.y, playerCoords.z, hatchCoords.x, hatchCoords.y, hatchCoords.z, false) < 2)
				{
					if (UI::DOES_BLIP_EXIST(LiftShaftBlip))
					{
						UI::SET_BLIP_ALPHA(LiftShaftBlip, 255);
					}
					UI::Screen::SendTextNotification("char_belle", "Belle", "Podium Robbery", "There it is. Get your rappelling equipment ready and get down that shaft! (get it, no?)");
					PlayerLocatedHatch_FLAG = true;
				}
			}
		}
		break;
		case 3:
		{
			if (!CAM::DOES_CAM_EXIST(RappelCam))
			{
				RappelCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_CAMERA", 823.1989f, -2204.03f, 29.88204f, -76.443f, -0.1192f, 90.0f, 30.0f, true, 2);
				CAM::ATTACH_CAM_TO_ENTITY(RappelCam, PLAYER::PLAYER_PED_ID(), 0.1772f, -1.044f, 4.12f, true);
				CAM::RENDER_SCRIPT_CAMS(true, false, 3000, true, false);
			}

			RappelControl();
			UI::Screen::ShowSubtitle("Rappel down the elevator shaft.");
		}
		break;
		case 4:
		{
			if (!ENTITY::DOES_ENTITY_EXIST(Keypad))
			{
				Keypad = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(824.6399f, -2210.142f, -48.74001f, 2.0f, joaat("prop_ld_keypad_01b"), false, false, false);
				if (Keypad != 0)
				{
					// we need to adjust the Z position because if not the animation task will look weird
					ENTITY::SET_ENTITY_COORDS(Keypad, 824.6399f, -2210.142f, -48.70001f, false, false, false, false);
				}
			}
			else if (!UI::DOES_BLIP_EXIST(KeypadBlip))
			{
				KeypadBlip = UI::ADD_BLIP_FOR_ENTITY(Keypad);
				UI::SET_BLIP_SPRITE(KeypadBlip, 619);
				UI::SET_BLIP_COLOUR(KeypadBlip, 2);
				int start = GAMEPLAY::GET_GAME_TIMER();
				int time = 8000;
				DisplayHelpTimer = start + time;
			}
			else
			{
				if (GAMEPLAY::GET_GAME_TIMER() < DisplayHelpTimer)
				{
					UI::DISPLAY_HELP_TEXT_THIS_FRAME("VRPC_HLP_3" /* GXT: Access the keypad ~HUD_COLOUR_GREEN~~BLIP_KEYPAD~~s~ and insert the key card to open the doors to the Casino's storage facility. */, false);
				}
				Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
				Vector3 keypadCoords = ENTITY::GET_ENTITY_COORDS(Keypad, false);

				if (GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(playerCoords.x, playerCoords.y, playerCoords.z, keypadCoords.x, keypadCoords.y, keypadCoords.z, false) < 0.9f)
				{
					UI::Screen::ShowHelpTextThisFrame("Press ~INPUT_CONTEXT~ to open the storage facility doors.", false);
					if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, 51))
					{
						if (UI::DOES_BLIP_EXIST(KeypadBlip))
						{
							UI::REMOVE_BLIP(&KeypadBlip);
							KeypadBlip = 0;
						}
						InsertAccessKeycard(Keypad);
						if (ENTITY::DOES_ENTITY_EXIST(RobberyVehicle))
						{
							if (invoke<bool>(0xC69BB1D832A710EF, RobberyVehicle))
							{
								invoke<Void>(0x7C06330BFDDA182E, RobberyVehicle);
							}
						}
						Index = 5;
					}
				}
				UI::Screen::ShowSubtitle("Open the storage facility ~g~door.");
			}
		}
		break;
		case 5:
		{
			OpenRollerDoor();
			if (IsFirstRollerdoorFullyUp_FLAG)
			{
				Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
				Vector3 keypadCoords = ENTITY::GET_ENTITY_COORDS(Keypad2, false);

				if (GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(playerCoords.x, playerCoords.y, playerCoords.z, keypadCoords.x, keypadCoords.y, keypadCoords.z, false) < 0.9f)
				{
					UI::Screen::ShowHelpTextThisFrame("Press ~INPUT_CONTEXT~ to disable the security measures.", false);
					if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, 51))
					{
						if (UI::DOES_BLIP_EXIST(KeypadBlip))
						{
							UI::REMOVE_BLIP(&KeypadBlip);
							KeypadBlip = 0;
						}
						InsertAccessKeycard(Keypad2);
						Index = 6;
					}
				}
				// best to make this a loop because if i do a while loop it'll leave the mission in 'limbo' while it opens
				UI::Screen::ShowSubtitle("Disable the security measures.");
			}
			else
			{
				UI::Screen::ShowSubtitle("Wait for the storage facility ~g~door ~w~to open.");
			}
		}
		break;
		case 6:
		{
			ShutRollerDoor2(true);
			if (ENTITY::DOES_ENTITY_EXIST(RobberyVehicle))
			{
				Vector3 robberyVehicleCoords = ENTITY::GET_ENTITY_COORDS(RobberyVehicle, false);

				if (FIRE::IS_ENTITY_ON_FIRE(RobberyVehicle))
				{
					FIRE::STOP_ENTITY_FIRE(RobberyVehicle);
				}

				if (!UI::DOES_BLIP_EXIST(RobberyVehicleBlip))
				{
					RobberyVehicleBlip = UI::ADD_BLIP_FOR_ENTITY(RobberyVehicle);
					UI::SET_BLIP_SPRITE(RobberyVehicleBlip, 726);
					UI::SET_BLIP_COLOUR(RobberyVehicleBlip, 3);
					UI::BEGIN_TEXT_COMMAND_SET_BLIP_NAME("openwheel1");
					UI::END_TEXT_COMMAND_SET_BLIP_NAME(RobberyVehicleBlip);
				}
				else if (!UI::DOES_BLIP_EXIST(EscapeCasinoBlip))
				{
					EscapeCasinoBlip = UI::ADD_BLIP_FOR_COORD(957.60f, -2335.90f, -50.0f);
					UI::SET_BLIP_SPRITE(EscapeCasinoBlip, 1);
					UI::SET_BLIP_COLOUR(EscapeCasinoBlip, 5);
					EscapeCasinoCheckpoint = GRAPHICS::CREATE_CHECKPOINT(47, 957.60f, -2335.90f, -50.0f, 0.0f, 0.0f, 0.0f, 1.0f, 240, 200, 80, 155, 0);
					GRAPHICS::SET_CHECKPOINT_CYLINDER_HEIGHT(EscapeCasinoCheckpoint, 0.7f, 0.7f, 0.7f);
				}
				else
				{
					if (!PED::IS_PED_IN_VEHICLE(PLAYER::PLAYER_PED_ID(), RobberyVehicle, false))
					{
						if (UI::GET_BLIP_ALPHA(RobberyVehicleBlip) != 255)
						{
							UI::SET_BLIP_ALPHA(RobberyVehicleBlip, 255);
						}

						if (UI::GET_BLIP_ALPHA(EscapeCasinoBlip) != 0)
						{
							UI::SET_BLIP_ALPHA(EscapeCasinoBlip, 0);
						}

						UI::Screen::ShowSubtitle("Enter the ~b~BR8.");
					}
					else
					{
						if (UI::GET_BLIP_ALPHA(RobberyVehicleBlip) != 0)
						{
							UI::SET_BLIP_ALPHA(RobberyVehicleBlip, 0);
						}

						if (UI::GET_BLIP_ALPHA(EscapeCasinoBlip) != 255)
						{
							UI::SET_BLIP_ALPHA(EscapeCasinoBlip, 255);
						}

						if (GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(robberyVehicleCoords.x, robberyVehicleCoords.y, robberyVehicleCoords.z, 957.60f, -2335.90f, -50.0f, false) < 4.0f)
						{
							UI::REMOVE_BLIP(&EscapeCasinoBlip);
							EscapeCasinoBlip = 0;
							GRAPHICS::DELETE_CHECKPOINT(EscapeCasinoCheckpoint);
							EscapeCasinoCheckpoint = 0;
							invoke<Void>(0x260BE8F09E326A20, RobberyVehicle, 0.5f, -1, true);
							while (!invoke<bool>(0xC69BB1D832A710EF, RobberyVehicle))
							{
								WAIT(0);
							}
							if (!CAM::IS_SCREEN_FADED_OUT() && !CAM::IS_SCREEN_FADING_OUT())
							{
								CAM::DO_SCREEN_FADE_OUT(250);
							}
							while (CAM::IS_SCREEN_FADING_OUT())
							{
								WAIT(0);
							}
							LoadInteriors(true, false);
							invoke<bool>(0x7C06330BFDDA182E, RobberyVehicle);
							ENTITY::SET_ENTITY_COORDS(RobberyVehicle, 1000.265f, -55.743f, 74.150f, false, false, false, false);
							ENTITY::SET_ENTITY_HEADING(RobberyVehicle, 120.0f);
							if (!PED::IS_PED_IN_VEHICLE(PLAYER::PLAYER_PED_ID(), RobberyVehicle, false))
							{
								PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), RobberyVehicle, -1);
							}
							WAIT(2000);
							VEHICLE::SET_VEHICLE_FORWARD_SPEED(RobberyVehicle, 15.0f);
							PLAYER::SET_MAX_WANTED_LEVEL(5);
							GAMEPLAY::SET_FAKE_WANTED_LEVEL(0);
							PLAYER::SET_WANTED_LEVEL_MULTIPLIER(1.0f);
							PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 3, true);
							if (!CAM::IS_SCREEN_FADED_IN() && !CAM::IS_SCREEN_FADING_IN())
							{
								CAM::DO_SCREEN_FADE_IN(250);
							}
							while (CAM::IS_SCREEN_FADING_IN())
							{
								WAIT(0);
							}
							UI::Screen::SendTextNotification("char_belle", "Belle", "Podium Robbery", "Sick. Now, the LSPD are gonna be all over your ass so get rollin.");
							Index = 7;
						}

						UI::Screen::ShowSubtitle("Escape the ~y~Casino.");
					}
					GRAPHICS::SET_CHECKPOINT_RGBA(EscapeCasinoCheckpoint, 240, 200, 80, UI::GET_BLIP_ALPHA(EscapeCasinoBlip));
				}
			}
		}
		break;
		case 7:
		{
			if (ENTITY::DOES_ENTITY_EXIST(RobberyVehicle))
			{
				Vector3 robberyVehicleCoords = ENTITY::GET_ENTITY_COORDS(RobberyVehicle, false);

				if (!UI::DOES_BLIP_EXIST(DeliverBlip))
				{
					DeliverBlip = UI::ADD_BLIP_FOR_COORD(-1468.0f, -927.0f, 9.10f);
					UI::SET_BLIP_SPRITE(DeliverBlip, 1);
					UI::SET_BLIP_COLOUR(DeliverBlip, 5);
					DeliverCheckpoint = GRAPHICS::CREATE_CHECKPOINT(47, -1468.0f, -927.0f, 9.10f, 0.0f, 0.0f, 0.0f, 2.0f, 240, 200, 80, 155, 0);
					GRAPHICS::SET_CHECKPOINT_CYLINDER_HEIGHT(DeliverCheckpoint, 0.7f, 0.7f, 0.7f);
				}
				else
				{
					if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) > 0)
					{
						if (UI::GET_BLIP_ALPHA(DeliverBlip) != 0)
						{
							UI::SET_BLIP_ALPHA(DeliverBlip, 0);
						}

						if (ScriptBlipRoute_FLAG)
						{
							UI::SET_BLIP_ROUTE(DeliverBlip, false);
							ScriptBlipRoute_FLAG = false;
						}

						UI::Screen::ShowSubtitle("Lose the Cops.");
					}
					else
					{
						if (UI::GET_BLIP_ALPHA(DeliverBlip) != 255)
						{
							UI::SET_BLIP_ALPHA(DeliverBlip, 255);
						}

						if (!ScriptBlipRoute_FLAG)
						{
							UI::SET_BLIP_ROUTE(DeliverBlip, true);
							ScriptBlipRoute_FLAG = true;
						}

						if (GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(robberyVehicleCoords.x, robberyVehicleCoords.y, robberyVehicleCoords.z, -1468.0f, -927.0f, 9.10f, false) < 4.0f)
						{
							UI::REMOVE_BLIP(&DeliverBlip);
							DeliverBlip = 0;
							GRAPHICS::DELETE_CHECKPOINT(DeliverCheckpoint);
							DeliverCheckpoint = 0;
							invoke<Void>(0x260BE8F09E326A20, RobberyVehicle, 0.5f, -1, true);
							while (!invoke<bool>(0xC69BB1D832A710EF, RobberyVehicle))
							{
								WAIT(0);
							}
							if (!CAM::IS_SCREEN_FADED_OUT() && !CAM::IS_SCREEN_FADING_OUT())
							{
								CAM::DO_SCREEN_FADE_OUT(250);
							}
							while (CAM::IS_SCREEN_FADING_OUT())
							{
								WAIT(0);
							}

							if (ENTITY::DOES_ENTITY_EXIST(RobberyVehicle))
							{
								if (ENTITY::IS_ENTITY_A_VEHICLE(RobberyVehicle))
								{
									VEHICLE::DELETE_VEHICLE(&RobberyVehicle);
									RobberyVehicle = 0;
								}
								else
								{

								}
							}

							ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), -1469.280f, -928.500f, 10.1f, false, false, false, false);
							ENTITY::SET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID(), -40.0f);
							WAIT(2000);
							UI::DISPLAY_HUD(false);
							UI::DISPLAY_RADAR(false);
							if (!CAM::IS_SCREEN_FADED_IN() && !CAM::IS_SCREEN_FADING_IN())
							{
								CAM::DO_SCREEN_FADE_IN(250);
							}

							invoke<Void>(0x477D5D63E63ECA5D, PLAYER::PLAYER_ID(), 1.0f, 2000, 1.0f, 1, 0); /* SIMULATE_PLAYER_INPUT_GAIT */
							CAM::SET_GAMEPLAY_CAM_RELATIVE_HEADING(0.0f);

							int vehicleValue = 1350000;
							int belleCut = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(150000, 200000);
							int damageCost = VehicleDamageValue;
							int hardModeBonus = IsHardMode_FLAG ? 75000 : 0;
							int totalCashEarned = vehicleValue - belleCut - damageCost + hardModeBonus;

							UI::Scaleforms::RobberyCompleteShard robberyCompleteShard = UI::Scaleforms::RobberyCompleteShard("~w~ROBBERY COMPLETE", "Belle's Podium", "Total Cash Earned:", totalCashEarned);
							robberyCompleteShard.Blocks.push_back(UI::Scaleforms::RobberyCompleteShardBlock("Vehicle Value:", vehicleValue));
							robberyCompleteShard.Blocks.push_back(UI::Scaleforms::RobberyCompleteShardBlock("Belle's Cut:", belleCut));
							robberyCompleteShard.Blocks.push_back(UI::Scaleforms::RobberyCompleteShardBlock("Damages Cost:", damageCost));
							robberyCompleteShard.Blocks.push_back(UI::Scaleforms::RobberyCompleteShardBlock("Hard Mode Bonus:", hardModeBonus));
							robberyCompleteShard.Show();
							Dispose();
							UI::DISPLAY_HUD(true);
							UI::DISPLAY_RADAR(true);
							Index = -1;
						}

						UI::Screen::ShowSubtitle("Deliver the ~b~BR8 ~w~to ~y~Belle's Clubhouse.");
					}

					GRAPHICS::SET_CHECKPOINT_RGBA(DeliverCheckpoint, 240, 200, 80, UI::GET_BLIP_ALPHA(DeliverBlip));
				}
			}
		}
		break;
		}
	}

	void CasinoVehicleRobbery::Init()
	{
		BaseMission::Init();
		PLAYER::SET_MAX_WANTED_LEVEL(0);
		PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 0, false);
		PLAYER::SET_WANTED_LEVEL_MULTIPLIER(0.0f);
		GAMEPLAY::SET_WEATHER_TYPE_NOW("EXTRASUNNY");
		TIME::SET_CLOCK_TIME(19, 30, 0);
		TIME::PAUSE_CLOCK(true);
		AUDIO::TRIGGER_MUSIC_EVENT("MP242_SUSPENSE_START");
	
		STREAMING::REQUEST_MODEL(joaat("boxville4"));
		while (!STREAMING::HAS_MODEL_LOADED(joaat("boxville4")))
		{
			WAIT(0);
		}
		Boxville = VEHICLE::CREATE_VEHICLE(joaat("boxville4"), -1459.800f, -924.872f, 10.0f, -140.0f, false, true);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("boxville4"));
		if (ENTITY::DOES_ENTITY_EXIST(Boxville))
		{
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(Boxville, 3);
			VEHICLE::SET_PED_TARGETTABLE_VEHICLE_DESTROY(Boxville, 3, 0); /* SET_VEHICLE_INDIVIDUAL_DOORS_LOCKED */
			invoke<Void>(0xBAA045B4E42F3C06, Boxville, 100.0f); /* SET_VEHICLE_MAX_SPEED */
			BoxvilleBlip = UI::ADD_BLIP_FOR_ENTITY(Boxville);
			UI::SET_BLIP_SPRITE(BoxvilleBlip, 853);
			UI::SET_BLIP_COLOUR(BoxvilleBlip, 3);
		}

		if (UI::DOES_TEXT_LABEL_EXIST("BOXVILLE"))
		{
			UI::BEGIN_TEXT_COMMAND_SET_BLIP_NAME("BOXVILLE");
			UI::END_TEXT_COMMAND_SET_BLIP_NAME(BoxvilleBlip);
		}

		STREAMING::REQUEST_MODEL(joaat("mp_f_freemode_01"));
		while (!STREAMING::HAS_MODEL_LOADED(joaat("mp_f_freemode_01")))
		{
			WAIT(0);
		}

		BellePed = PED::CREATE_PED(26, joaat("mp_f_freemode_01"), -1459.800f, -924.872f, 10.0f, 140.0f, false, true);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("mp_f_freemode_01"));
		if (ENTITY::DOES_ENTITY_EXIST(BellePed))
		{
			PED::SET_PED_COMPONENT_VARIATION(BellePed, 2, 53, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(BellePed, 4, 43, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(BellePed, 6, 83, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(BellePed, 8, 52, 0, 0);
			PED::SET_PED_COMPONENT_VARIATION(BellePed, 11, 379, 0, 0);

			BelleBlip = UI::ADD_BLIP_FOR_ENTITY(BellePed);
			UI::SET_BLIP_SPRITE(BelleBlip, 280);
			UI::SET_BLIP_COLOUR(BelleBlip, 2 /* Blue */);
			UI::SET_BLIP_AS_FRIENDLY(BelleBlip, true);
			UI::BEGIN_TEXT_COMMAND_SET_BLIP_NAME("STRING");
			UI::_ADD_TEXT_COMPONENT_STRING("Belle");
			UI::END_TEXT_COMMAND_SET_BLIP_NAME(BelleBlip);

			if (ENTITY::DOES_ENTITY_EXIST(Boxville))
			{
				PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(BellePed, true);
				PED::SET_PED_CAN_BE_DRAGGED_OUT(BellePed, true);
				PED::SET_PED_CAN_BE_TARGETTED(BellePed, false);
				PED::SET_PED_INTO_VEHICLE(BellePed, Boxville, -1);
			}
		}

		UI::Scaleforms::MidsizedMessage midsizedMessage;
		midsizedMessage.Show("BELLE'S PODIUM ROBBERY", "Target: DR8", 2);
	}

	void CasinoVehicleRobbery::LoadInteriors(bool cleanup, bool removeRobberyVehicle)
	{
		if (cleanup)
		{
			StopAllAlarms(); // stops all the casino alarms used during the heist

			if (STREAMING::IS_IPL_ACTIVE("M23_2_DLC_INT_casinobase"))
			{
				STREAMING::REMOVE_IPL("M23_2_DLC_INT_casinobase");
			}

			if (ENTITY::DOES_ENTITY_EXIST(LiftShaft))
			{
				OBJECT::DELETE_OBJECT(&LiftShaft);
				LiftShaft = 0;
			}

			if (ENTITY::DOES_ENTITY_EXIST(LiftShaftHatch))
			{
				OBJECT::DELETE_OBJECT(&LiftShaftHatch);
				LiftShaftHatch = 0;
			}

			if (ENTITY::DOES_ENTITY_EXIST(Keypad))
			{
				OBJECT::DELETE_OBJECT(&Keypad);
				Keypad = 0;
			}

			if (ENTITY::DOES_ENTITY_EXIST(Keypad2))
			{
				OBJECT::DELETE_OBJECT(&Keypad2);
				Keypad2 = 0;
			}

			if (removeRobberyVehicle)
			{
				if (ENTITY::DOES_ENTITY_EXIST(RobberyVehicle))
				{
					VEHICLE::DELETE_VEHICLE(&RobberyVehicle);
					RobberyVehicle = 0;
				}
			}

			if (ENTITY::DOES_ENTITY_EXIST(CoveredVehicleProp))
			{
				OBJECT::DELETE_OBJECT(&CoveredVehicleProp);
				CoveredVehicleProp = 0;
			}

			if (ENTITY::DOES_ENTITY_EXIST(CoveredVehicleProp2))
			{
				OBJECT::DELETE_OBJECT(&CoveredVehicleProp2);
				CoveredVehicleProp2 = 0;
			}

			if (ENTITY::DOES_ENTITY_EXIST(CoveredVehicleProp3))
			{
				OBJECT::DELETE_OBJECT(&CoveredVehicleProp3);
				CoveredVehicleProp3 = 0;
			}

			if (ENTITY::DOES_ENTITY_EXIST(CoveredVehicleProp4))
			{
				OBJECT::DELETE_OBJECT(&CoveredVehicleProp4);
				CoveredVehicleProp4 = 0;
			}

			if (ENTITY::DOES_ENTITY_EXIST(CoveredVehicleProp5))
			{
				OBJECT::DELETE_OBJECT(&CoveredVehicleProp5);
				CoveredVehicleProp5 = 0;
			}

			if (ENTITY::DOES_ENTITY_EXIST(CoveredVehicleProp6))
			{
				OBJECT::DELETE_OBJECT(&CoveredVehicleProp6);
				CoveredVehicleProp6 = 0;
			}

			if (ENTITY::DOES_ENTITY_EXIST(PodiumGarageConcreteBlock))
			{
				OBJECT::DELETE_OBJECT(&PodiumGarageConcreteBlock);
				PodiumGarageConcreteBlock = 0;
			}

			if (ENTITY::DOES_ENTITY_EXIST(PodiumGarageConcreteBlock2))
			{
				OBJECT::DELETE_OBJECT(&PodiumGarageConcreteBlock2);
				PodiumGarageConcreteBlock2 = 0;
			}

			if (ENTITY::DOES_ENTITY_EXIST(PodiumGarageConcreteBlock3))
			{
				OBJECT::DELETE_OBJECT(&PodiumGarageConcreteBlock3);
				PodiumGarageConcreteBlock3 = 0;
			}

			SpawnHotelGuards(true);
			SpawnPodiumGarageGuards(true);
		}
		else
		{
			int interiorId = INTERIOR::GET_INTERIOR_AT_COORDS(2504.400, -257.200, -39.100);
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

				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 2523.766f, -288.5936f, -40.12293f, false, false, false, false);
				INTERIOR::FORCE_ROOM_FOR_ENTITY(PLAYER::PLAYER_PED_ID(), INTERIOR::GET_INTERIOR_FROM_ENTITY(PLAYER::PLAYER_PED_ID()), INTERIOR::GET_ROOM_KEY_FROM_ENTITY(PLAYER::PLAYER_PED_ID()));
			}

			int interiorId2 = INTERIOR::GET_INTERIOR_AT_COORDS_WITH_TYPE(858.0, -2275.0, -50.0, "M23_2_DLC_INT_casinobase");
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
			
			STREAMING::REQUEST_MODEL(joaat("m23_2_prop_m32_liftshaft_01a"));
			while (!STREAMING::HAS_MODEL_LOADED(joaat("m23_2_prop_m32_liftshaft_01a")))
			{
				WAIT(0);
			}

			LiftShaft = OBJECT::CREATE_OBJECT_NO_OFFSET(joaat("m23_2_prop_m32_liftshaft_01a"), 2493.93f, -267.42f, -40.19f, false, true, false);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("m23_2_prop_m32_liftshaft_01a"));
			if (ENTITY::DOES_ENTITY_EXIST(LiftShaft))
			{
				ENTITY::FREEZE_ENTITY_POSITION(LiftShaft, true);
				LiftShaftBlip = UI::ADD_BLIP_FOR_ENTITY(LiftShaft);
				UI::SET_BLIP_SPRITE(LiftShaftBlip, 1);
				UI::SET_BLIP_COLOUR(LiftShaftBlip, 2);
				UI::BEGIN_TEXT_COMMAND_SET_BLIP_NAME("STRING");
				UI::_ADD_TEXT_COMPONENT_STRING("Lift Shaft");
				UI::END_TEXT_COMMAND_SET_BLIP_NAME(LiftShaftBlip);
				UI::SET_BLIP_ALPHA(LiftShaftBlip, 0);
			}

			STREAMING::REQUEST_MODEL(joaat("m23_2_prop_m32_shaftdoor_01a"));
			while (!STREAMING::HAS_MODEL_LOADED(joaat("m23_2_prop_m32_shaftdoor_01a")))
			{
				WAIT(0);
			}

			LiftShaftHatch = OBJECT::CREATE_OBJECT_NO_OFFSET(joaat("m23_2_prop_m32_shaftdoor_01a"), 2493.92f, -267.39f, -38.80f, false, true, false);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("m23_2_prop_m32_shaftdoor_01a"));
			if (ENTITY::DOES_ENTITY_EXIST(LiftShaftHatch))
			{
				ENTITY::FREEZE_ENTITY_POSITION(LiftShaftHatch, true);
			}

			STREAMING::REQUEST_MODEL(joaat("openwheel1"));
			while (!STREAMING::HAS_MODEL_LOADED(joaat("openwheel1")))
			{
				WAIT(0);
			}

			STREAMING::REQUEST_MODEL(joaat("prop_ld_keypad_01b"));
			while (!STREAMING::HAS_MODEL_LOADED(joaat("prop_ld_keypad_01b")))
			{
				WAIT(0);
			}

			Keypad2 = OBJECT::CREATE_OBJECT_NO_OFFSET(joaat("prop_ld_keypad_01b"), 824.900f, -2247.121f, -48.70001f, false, true, false);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("prop_ld_keypad_01b"));
			if (ENTITY::DOES_ENTITY_EXIST(Keypad2))
			{
				ENTITY::SET_ENTITY_HEADING(Keypad2, 180.0f);
				ENTITY::FREEZE_ENTITY_POSITION(Keypad2, true);
			}

			RobberyVehicle = VEHICLE::CREATE_VEHICLE(joaat("openwheel1"), 837.847f, -2226.515f, -49.755f, 90.0f, false, true);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("openwheel1"));
			if (ENTITY::DOES_ENTITY_EXIST(RobberyVehicle))
			{
				if (VEHICLE::GET_VEHICLE_LIVERY_COUNT(RobberyVehicle) > 0)
				{
					VEHICLE::SET_VEHICLE_LIVERY(RobberyVehicle, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, VEHICLE::GET_VEHICLE_LIVERY_COUNT(RobberyVehicle) - 1));
				}
				
				VEHICLE::_TASK_BRING_VEHICLE_TO_HALT(RobberyVehicle, 0.0f, -1, 0);
			}

			STREAMING::REQUEST_MODEL(joaat("imp_prop_covered_vehicle_01a"));
			while (!STREAMING::HAS_MODEL_LOADED(joaat("imp_prop_covered_vehicle_01a")))
			{
				WAIT(0);
			}

			CoveredVehicleProp = OBJECT::CREATE_OBJECT(joaat("imp_prop_covered_vehicle_01a"), 837.38f, -2216.89f, -50.0f, false, true, false);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("imp_prop_covered_vehicle_01a"));

			if (ENTITY::DOES_ENTITY_EXIST(CoveredVehicleProp))
			{
				ENTITY::SET_ENTITY_HEADING(CoveredVehicleProp, 135.0f);
				ENTITY::FREEZE_ENTITY_POSITION(CoveredVehicleProp, true);
			}

			STREAMING::REQUEST_MODEL(joaat("imp_prop_covered_vehicle_02a"));
			while (!STREAMING::HAS_MODEL_LOADED(joaat("imp_prop_covered_vehicle_02a")))
			{
				WAIT(0);
			}

			CoveredVehicleProp2 = OBJECT::CREATE_OBJECT(joaat("imp_prop_covered_vehicle_02a"), 837.40f, -2241.50f, -50.0f, false, true, false);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("imp_prop_covered_vehicle_02a"));

			if (ENTITY::DOES_ENTITY_EXIST(CoveredVehicleProp2))
			{
				ENTITY::SET_ENTITY_HEADING(CoveredVehicleProp2, 45.0f);
				ENTITY::FREEZE_ENTITY_POSITION(CoveredVehicleProp2, true);
			}

			STREAMING::REQUEST_MODEL(joaat("imp_prop_covered_vehicle_03a"));
			while (!STREAMING::HAS_MODEL_LOADED(joaat("imp_prop_covered_vehicle_03a")))
			{
				WAIT(0);
			}

			CoveredVehicleProp3 = OBJECT::CREATE_OBJECT(joaat("imp_prop_covered_vehicle_03a"), 819.94, -2219.12f, -50.0f, false, true, false);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("imp_prop_covered_vehicle_03a"));

			if (ENTITY::DOES_ENTITY_EXIST(CoveredVehicleProp3))
			{
				ENTITY::SET_ENTITY_HEADING(CoveredVehicleProp3, 90.0f);
				ENTITY::FREEZE_ENTITY_POSITION(CoveredVehicleProp3, true);
			}

			STREAMING::REQUEST_MODEL(joaat("imp_prop_covered_vehicle_04a"));
			while (!STREAMING::HAS_MODEL_LOADED(joaat("imp_prop_covered_vehicle_04a")))
			{
				WAIT(0);
			}

			CoveredVehicleProp4 = OBJECT::CREATE_OBJECT(joaat("imp_prop_covered_vehicle_04a"), 8820.33f, -2230.0f, -50.0f, false, true, false);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("imp_prop_covered_vehicle_04a"));

			if (ENTITY::DOES_ENTITY_EXIST(CoveredVehicleProp4))
			{
				ENTITY::SET_ENTITY_HEADING(CoveredVehicleProp4, -135.0f);
				ENTITY::FREEZE_ENTITY_POSITION(CoveredVehicleProp4, true);
			}

			STREAMING::REQUEST_MODEL(joaat("imp_prop_covered_vehicle_05a"));
			while (!STREAMING::HAS_MODEL_LOADED(joaat("imp_prop_covered_vehicle_05a")))
			{
				WAIT(0);
			}

			CoveredVehicleProp5 = OBJECT::CREATE_OBJECT(joaat("imp_prop_covered_vehicle_05a"), 820.0f, -2238.85f, -50.0f, false, true, false);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("imp_prop_covered_vehicle_05a"));

			if (ENTITY::DOES_ENTITY_EXIST(CoveredVehicleProp5))
			{
				ENTITY::SET_ENTITY_HEADING(CoveredVehicleProp5, -90.0f);
				ENTITY::FREEZE_ENTITY_POSITION(CoveredVehicleProp5, true);
			}

			STREAMING::REQUEST_MODEL(joaat("imp_prop_covered_vehicle_05a"));
			while (!STREAMING::HAS_MODEL_LOADED(joaat("imp_prop_covered_vehicle_05a")))
			{
				WAIT(0);
			}

			CoveredVehicleProp6 = OBJECT::CREATE_OBJECT(joaat("imp_prop_covered_vehicle_06a"), 820.15f, -2244.40f, -50.0f, false, true, false);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("imp_prop_covered_vehicle_06a"));

			if (ENTITY::DOES_ENTITY_EXIST(CoveredVehicleProp6))
			{
				ENTITY::SET_ENTITY_HEADING(CoveredVehicleProp6, -90.0f);
				ENTITY::FREEZE_ENTITY_POSITION(CoveredVehicleProp6, true);
			}

			STREAMING::REQUEST_MODEL(joaat("prop_conc_blocks01c"));
			while (!STREAMING::HAS_MODEL_LOADED(joaat("prop_conc_blocks01c")))
			{
				WAIT(0);
			}

			PodiumGarageConcreteBlock = OBJECT::CREATE_OBJECT(joaat("prop_conc_blocks01c"), 832.0f, -2221.60f, -50.0f, false, true, false);

			if (ENTITY::DOES_ENTITY_EXIST(PodiumGarageConcreteBlock))
			{
				ENTITY::SET_ENTITY_HEADING(PodiumGarageConcreteBlock, 0.0f);
				ENTITY::FREEZE_ENTITY_POSITION(PodiumGarageConcreteBlock, true);
			}

			PodiumGarageConcreteBlock2 = OBJECT::CREATE_OBJECT(joaat("prop_conc_blocks01c"), 832.80f, -2237.0f, -50.0f, false, true, false);

			if (ENTITY::DOES_ENTITY_EXIST(PodiumGarageConcreteBlock2))
			{
				ENTITY::SET_ENTITY_HEADING(PodiumGarageConcreteBlock2, 0.0f);
				ENTITY::FREEZE_ENTITY_POSITION(PodiumGarageConcreteBlock2, true);
			}

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("prop_conc_blocks01c"));

			STREAMING::REQUEST_MODEL(joaat("prop_conc_blocks01b"));
			while (!STREAMING::HAS_MODEL_LOADED(joaat("prop_conc_blocks01b")))
			{
				WAIT(0);
			}

			PodiumGarageConcreteBlock3 = OBJECT::CREATE_OBJECT(joaat("prop_conc_blocks01b"), 825.30f, -2237.0f, -50.0f, false, true, false);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("prop_conc_blocks01b"));

			if (ENTITY::DOES_ENTITY_EXIST(PodiumGarageConcreteBlock3))
			{
				ENTITY::SET_ENTITY_HEADING(PodiumGarageConcreteBlock3, 0.0f);
				ENTITY::FREEZE_ENTITY_POSITION(PodiumGarageConcreteBlock3, true);
			}

			func_6767(1);
		}
	}

	void CasinoVehicleRobbery::JumpOutCrate()
	{
		AUDIO::RELEASE_NAMED_SCRIPT_AUDIO_BANK("DLC_23_2/DLC_23_2_XM4_CBR6");
		AUDIO::REQUEST_SCRIPT_AUDIO_BANK("DLC_23_2/DLC_23_2_XM4_CBR6", false);
		STREAMING::REQUEST_MODEL(joaat("xm3_prop_xm3_crate_01a"));
		while (!STREAMING::HAS_MODEL_LOADED(joaat("xm3_prop_xm3_crate_01a")))
		{
			WAIT(0);
		}

		GAMEPLAY::CLEAR_AREA_OF_OBJECTS(2526.20f, -289.83f, -40.12f, 3.0f, 0);
		Crate = OBJECT::CREATE_OBJECT_NO_OFFSET(joaat("xm3_prop_xm3_crate_01a"), 2526.20f, -289.83f, -40.12f, false, true, false);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(joaat("xm3_prop_xm3_crate_01a"));
		if (ENTITY::DOES_ENTITY_EXIST(Crate))
		{
			ENTITY::SET_ENTITY_HEADING(Crate, -90.0f);
		}

		STREAMING::REQUEST_ANIM_DICT("ANIM@SCRIPTED@CBR6@IG1_CLIMB_OUT_BOX@MALE@");
		while (!STREAMING::HAS_ANIM_DICT_LOADED("ANIM@SCRIPTED@CBR6@IG1_CLIMB_OUT_BOX@MALE@"))
		{
			WAIT(0);
		}

		CAM::SET_GAMEPLAY_CAM_RELATIVE_HEADING(0.0f);
		Vector3 Var4 = ENTITY::GET_ENTITY_COORDS(Crate, false);
		Vector3 Var7 = ENTITY::GET_ENTITY_ROTATION(Crate, 2);
		ENTITY::FREEZE_ENTITY_POSITION(Crate, true);
		ENTITY::SET_ENTITY_COLLISION(Crate, false, false);
		CrateCam = CAM::CREATE_CAM("DEFAULT_ANIMATED_CAMERA", true);
		CAM::SET_CAM_FOV(CrateCam, 40.0f);
		CAM::SHAKE_CAM(CrateCam, "HARD_SHAKE", 0.3f);
		CAM::SET_CAM_ACTIVE(CrateCam, true);

		AI::TASK_PLAY_ANIM_ADVANCED(PLAYER::PLAYER_PED_ID(), "ANIM@SCRIPTED@CBR6@IG1_CLIMB_OUT_BOX@MALE@", "ACTION", Var4.x, Var4.y, Var4.z, Var7.x, Var7.y, Var7.z, 1000.0f, -2.0f, -1, 1183240, 0.0f, 2, 8192);
		ENTITY::PLAY_ENTITY_ANIM(Crate, "ACTION_CRATE", "ANIM@SCRIPTED@CBR6@IG1_CLIMB_OUT_BOX@MALE@", 1000.0f, false, true, false, 0.0f, 131072);
		CAM::PLAY_CAM_ANIM(CrateCam, "ACTION_CAM", "ANIM@SCRIPTED@CBR6@IG1_CLIMB_OUT_BOX@MALE@", Var4.x, Var4.y, Var4.z, Var7.x, Var7.y, Var7.z, false, 2);
		CAM::RENDER_SCRIPT_CAMS(true, false, 3000, true, false);
		ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, false);

		if (CAM::IS_SCREEN_FADED_OUT() || CAM::IS_SCREEN_FADING_OUT())
		{
			CAM::DO_SCREEN_FADE_IN(500);
		}

		while (ENTITY::GET_ENTITY_ANIM_CURRENT_TIME(PLAYER::PLAYER_PED_ID(), "ANIM@SCRIPTED@CBR6@IG1_CLIMB_OUT_BOX@MALE@", "ACTION") < 0.805f)
		{
			UI::HIDE_HUD_AND_RADAR_THIS_FRAME();
			WAIT(0);
		}

		CAM::RENDER_SCRIPT_CAMS(false, true, 1500, true, false);
		ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), false);
		ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), true, false);
		ENTITY::SET_ENTITY_COLLISION(Crate, true, false);
		AUDIO::RELEASE_NAMED_SCRIPT_AUDIO_BANK("DLC_23_2/DLC_23_2_XM4_CBR6");
		STREAMING::REMOVE_ANIM_DICT("ANIM@SCRIPTED@CBR6@IG1_CLIMB_OUT_BOX@MALE@");
		if (CAM::DOES_CAM_EXIST(CrateCam))
		{
			CAM::DESTROY_CAM(CrateCam, true);
		}
		UI::UNLOCK_MINIMAP_ANGLE();
		UI::UNLOCK_MINIMAP_POSITION();
	}

	void CasinoVehicleRobbery::SpawnHotelGuards(bool cleanup)
	{
		if (cleanup)
		{
			for (auto ped = HotelGuards.begin(); ped != HotelGuards.end(); ++ped)
			{
				if (ENTITY::DOES_ENTITY_EXIST(*ped))
				{
					int attachedBlip = UI::GET_BLIP_FROM_ENTITY(*ped);
					if (UI::DOES_BLIP_EXIST(attachedBlip) && attachedBlip != 0)
					{
						UI::REMOVE_BLIP(&attachedBlip);
					}

					PED::DELETE_PED(&*ped);
				}
			}

			HotelGuards.clear();
			AI::DELETE_PATROL_ROUTE("miss_Guard01");
			AI::DELETE_PATROL_ROUTE("miss_Guard02");
			AI::DELETE_PATROL_ROUTE("miss_Guard03");
		}
		else
		{
			STREAMING::REQUEST_MODEL(3200789669);
			while (!STREAMING::HAS_MODEL_LOADED(3200789669))
			{
				WAIT(0);
			}

			int guard = PED::CREATE_PED(26, 3200789669, 2488.135f, -257.705f, -39.123f, 180.0f, false, true);

			if (ENTITY::DOES_ENTITY_EXIST(guard))
			{
				SetupGuard(guard);

				AI::OPEN_PATROL_ROUTE("miss_Guard01");
				AI::ADD_PATROL_ROUTE_NODE(1, "WORLD_HUMAN_GUARD_STAND", 2488.135f, -257.705f, -39.123f, 0.0f, 0.0f, 180.0f, 3000);
				AI::ADD_PATROL_ROUTE_NODE(2, "WORLD_HUMAN_GUARD_STAND", 2488.135f, -289.605f, -39.123f, 0.0f, 0.0f, -180.0f, 3000);
				AI::ADD_PATROL_ROUTE_LINK(1, 2);
				AI::ADD_PATROL_ROUTE_LINK(2, 1);
				AI::CLOSE_PATROL_ROUTE();
				AI::CREATE_PATROL_ROUTE();
				AI::TASK_PATROL(guard, "miss_Guard01", 0, false, false);

				HotelGuards.push_back(guard);
			}

			int guard2 = PED::CREATE_PED(26, 3200789669, 2523.677f, -261.375f, -39.123f, -180.0f, false, true);

			if (ENTITY::DOES_ENTITY_EXIST(guard2))
			{
				SetupGuard(guard2);

				AI::OPEN_PATROL_ROUTE("miss_Guard02");
				AI::ADD_PATROL_ROUTE_NODE(1, "WORLD_HUMAN_GUARD_STAND", 2523.677f, -261.375f, -39.123f, 0.0f, 0.0f, -180.0f, 3000);
				AI::ADD_PATROL_ROUTE_NODE(2, "WORLD_HUMAN_GUARD_STAND", 2502.384f, -270.267f, -39.123f, 0.0f, 0.0f, 95.0f, 3000);
				AI::ADD_PATROL_ROUTE_LINK(1, 2);
				AI::ADD_PATROL_ROUTE_LINK(2, 1);
				AI::CLOSE_PATROL_ROUTE();
				AI::CREATE_PATROL_ROUTE();
				AI::TASK_PATROL(guard2, "miss_Guard02", 0, false, false);

				HotelGuards.push_back(guard2);
			}

			int guard3 = PED::CREATE_PED(26, 3200789669, 2520.549f, -257.684f, -39.123, 90.0f, false, true);

			if (ENTITY::DOES_ENTITY_EXIST(guard3))
			{
				SetupGuard(guard3);

				AI::OPEN_PATROL_ROUTE("miss_Guard03");
				AI::ADD_PATROL_ROUTE_NODE(1, "WORLD_HUMAN_GUARD_STAND", 2520.549f, -257.684f, -39.123, 0.0f, 0.0f, -90.0f, 3000);
				AI::ADD_PATROL_ROUTE_NODE(2, "WORLD_HUMAN_GUARD_STAND", 2503.871f, -233.894f, -39.123, 0.0f, 0.0f, 0.0f, 3000);
				AI::ADD_PATROL_ROUTE_LINK(1, 2);
				AI::ADD_PATROL_ROUTE_LINK(2, 1);
				AI::CLOSE_PATROL_ROUTE();
				AI::CREATE_PATROL_ROUTE();
				AI::TASK_PATROL(guard3, "miss_Guard03", 0, false, false);

				HotelGuards.push_back(guard3);
			}

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(3200789669);
		}
	}

	void CasinoVehicleRobbery::SpawnPodiumGarageGuards(bool cleanup)
	{
		if (cleanup)
		{
			for (auto ped = PodiumGarageGuards.begin(); ped != PodiumGarageGuards.end(); ++ped)
			{
				if (ENTITY::DOES_ENTITY_EXIST(*ped))
				{
					int attachedBlip = UI::GET_BLIP_FROM_ENTITY(*ped);
					if (UI::DOES_BLIP_EXIST(attachedBlip) && attachedBlip != 0)
					{
						UI::REMOVE_BLIP(&attachedBlip);
					}

					PED::DELETE_PED(&*ped);
				}
			}

			PodiumGarageGuards.clear();
			AI::DELETE_PATROL_ROUTE("miss_Guard01");
			AI::DELETE_PATROL_ROUTE("miss_Guard02");
			AI::DELETE_PATROL_ROUTE("miss_Guard03");
			AI::DELETE_PATROL_ROUTE("miss_Guard04");
			AI::DELETE_PATROL_ROUTE("miss_Guard05");
		}
		else
		{
			STREAMING::REQUEST_MODEL(3200789669);
			while (!STREAMING::HAS_MODEL_LOADED(3200789669))
			{
				WAIT(0);
			}

			int guard, guard2, guard3, guard4, guard5, guard6, guard7, guard8;

			guard = PED::CREATE_PED(26, 3200789669, 829.472f, -2214.622f, -48.998f, -180.0f, false, true);

			if (ENTITY::DOES_ENTITY_EXIST(guard))
			{
				SetupGuard(guard);

				AI::OPEN_PATROL_ROUTE("miss_Guard01");
				AI::ADD_PATROL_ROUTE_NODE(1, "WORLD_HUMAN_GUARD_STAND", 829.472f, -2214.622f, -48.998f, 0.0f, 0.0f, -180.0f, 3000);
				AI::ADD_PATROL_ROUTE_NODE(2, "WORLD_HUMAN_GUARD_STAND", 829.472f, -2255.600f, -48.998f, 0.0f, 0.0f, -180.0f, 3000);
				AI::ADD_PATROL_ROUTE_LINK(1, 2);
				AI::ADD_PATROL_ROUTE_LINK(2, 1);
				AI::CLOSE_PATROL_ROUTE();
				AI::CREATE_PATROL_ROUTE();
				AI::TASK_PATROL(guard, "miss_Guard01", 0, false, false);

				PodiumGarageGuards.push_back(guard);
			}

			guard2 = PED::CREATE_PED(26, 3200789669, 826.198f, -2253.835f, -48.998f, -0.0f, false, true);

			if (ENTITY::DOES_ENTITY_EXIST(guard2))
			{
				SetupGuard(guard2);

				AI::OPEN_PATROL_ROUTE("miss_Guard02");
				AI::ADD_PATROL_ROUTE_NODE(1, "WORLD_HUMAN_GUARD_STAND", 829.472f, -2214.622f, -48.998f, 0.0f, 0.0f, -180.0f, 3000);
				AI::ADD_PATROL_ROUTE_NODE(2, "WORLD_HUMAN_GUARD_STAND", 826.777f, -2220.429f, -48.998f, 0.0f, 0.0f, -0.0f, 3000);
				AI::ADD_PATROL_ROUTE_LINK(1, 2);
				AI::ADD_PATROL_ROUTE_LINK(2, 1);
				AI::CLOSE_PATROL_ROUTE();
				AI::CREATE_PATROL_ROUTE();
				AI::TASK_PATROL(guard2, "miss_Guard02", 0, false, false);

				PodiumGarageGuards.push_back(guard2);
			}

			guard3 = PED::CREATE_PED(26, 3200789669, 817.0f, -2221.500f, -48.998f, -90.0f, false, true);

			if (ENTITY::DOES_ENTITY_EXIST(guard3))
			{
				SetupGuard(guard3);

				AI::OPEN_PATROL_ROUTE("miss_Guard03");
				AI::ADD_PATROL_ROUTE_NODE(1, "WORLD_HUMAN_GUARD_STAND", 817.0f, -2221.500f, -48.998f, 0.0f, 0.0f, -90.0f, 3000);
				AI::ADD_PATROL_ROUTE_NODE(2, "WORLD_HUMAN_GUARD_STAND", 837.384f, -2223.570f, -48.998f, 0.0f, 0.0f, -50.0f, 3000);
				AI::ADD_PATROL_ROUTE_LINK(1, 2);
				AI::ADD_PATROL_ROUTE_LINK(2, 1);
				AI::CLOSE_PATROL_ROUTE();
				AI::CREATE_PATROL_ROUTE();
				AI::TASK_PATROL(guard3, "miss_Guard03", 0, false, false);

				PodiumGarageGuards.push_back(guard3);
			}

			guard4 = PED::CREATE_PED(26, 3200789669, 837.484f, -2229.101f, -48.998f, 0.0f, false, true);

			if (ENTITY::DOES_ENTITY_EXIST(guard4))
			{
				SetupGuard(guard4);

				AI::OPEN_PATROL_ROUTE("miss_Guard04");
				AI::ADD_PATROL_ROUTE_NODE(1, "WORLD_HUMAN_GUARD_STAND", 837.484f, -2229.101f, -48.998f, 0.0f, 0.0f, 0.0f, 3000);
				AI::ADD_PATROL_ROUTE_NODE(2, "WORLD_HUMAN_GUARD_STAND", 819.498f, -2236.211f, -48.998f, 0.0f, 0.0f, 180.0f, 3000);
				AI::ADD_PATROL_ROUTE_LINK(1, 2);
				AI::ADD_PATROL_ROUTE_LINK(2, 1);
				AI::CLOSE_PATROL_ROUTE();
				AI::CREATE_PATROL_ROUTE();
				AI::TASK_PATROL(guard4, "miss_Guard04", 0, false, false);

				PodiumGarageGuards.push_back(guard4);
			}

			guard5 = PED::CREATE_PED(26, 3200789669, 835.900f, -2213.602f, -48.998f, 117.0f, false, true);

			if (ENTITY::DOES_ENTITY_EXIST(guard5))
			{
				SetupGuard(guard5);

				AI::OPEN_PATROL_ROUTE("miss_Guard05");
				AI::ADD_PATROL_ROUTE_NODE(1, "WORLD_HUMAN_GUARD_STAND", 835.900f, -2213.602f, -48.998f, 0.0f, 0.0f, 117.0f, 3000);
				AI::ADD_PATROL_ROUTE_NODE(2, "WORLD_HUMAN_GUARD_STAND", 824.817f, -2245.933f, -48.998f, 0.0f, 0.0f, 168.895f, 3000);
				AI::ADD_PATROL_ROUTE_LINK(1, 2);
				AI::ADD_PATROL_ROUTE_LINK(2, 1);
				AI::CLOSE_PATROL_ROUTE();
				AI::CREATE_PATROL_ROUTE();
				AI::TASK_PATROL(guard5, "miss_Guard05", 0, false, false);

				PodiumGarageGuards.push_back(guard5);
			}

			guard6 = PED::CREATE_PED(26, 3200789669, 833.095f, -2245.855f, -48.998f, -0.0f, false, true);

			if (ENTITY::DOES_ENTITY_EXIST(guard6))
			{
				SetupGuard(guard6);

				AI::TASK_USE_MOBILE_PHONE(guard6, -1);

				PodiumGarageGuards.push_back(guard6);
			}

			guard7 = PED::CREATE_PED(26, 3200789669, 832.449f, -2229.624f, -48.998f, -0.0f, false, true);

			if (ENTITY::DOES_ENTITY_EXIST(guard7))
			{
				SetupGuard(guard7);

				AI::TASK_START_SCENARIO_IN_PLACE(guard7, "WORLD_HUMAN_AA_COFFEE", 0, true);

				PodiumGarageGuards.push_back(guard7);
			}

			guard8 = PED::CREATE_PED(26, 3200789669, 830.232f, -2228.900f, -48.998f, -130.0f, false, true);

			if (ENTITY::DOES_ENTITY_EXIST(guard8))
			{
				SetupGuard(guard8);

				AI::TASK_START_SCENARIO_IN_PLACE(guard8, "WORLD_HUMAN_AA_COFFEE", 0, true);

				PodiumGarageGuards.push_back(guard8);
			}
		}

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(3200789669);
	}

	void CasinoVehicleRobbery::func_6767(bool bParam0)//Position - 0x1F2701
	{
		if (bParam0)
		{
			ENTITY::CREATE_MODEL_HIDE(2543.5105f, -248.7282f, -61.3736f, 15.0f, joaat("prop_bin_08open"), false);
			ENTITY::CREATE_MODEL_HIDE(2543.5105f, -248.7282f, -61.3736f, 15.0f, joaat("prop_bin_08a"), false);
			ENTITY::CREATE_MODEL_HIDE(2543.5105f, -248.7282f, -61.3736f, 15.0f, joaat("prop_rub_binbag_sd_01"), false);
			ENTITY::CREATE_MODEL_HIDE(2543.5105f, -248.7282f, -61.3736f, 15.0f, joaat("prop_rub_binbag_03b"), false);
			ENTITY::CREATE_MODEL_HIDE(2543.5105f, -248.7282f, -61.3736f, 15.0f, joaat("prop_rub_binbag_01b"), false);
			ENTITY::CREATE_MODEL_HIDE(828.663f, -2210.613f, -46.829f, 10.0f, joaat("m23_2_prop_m32_rollerdoor_podium"), false);
			ENTITY::CREATE_MODEL_HIDE(828.663f, -2257.905f, -46.829f, 10.0f, joaat("m23_2_prop_m32_rollerdoor_main"), false);
			ENTITY::CREATE_MODEL_HIDE(862.517f, -2272.807f, -50.004f, 5.0f, joaat("m23_2_prop_m32_lobay_gate01"), false);
			ENTITY::CREATE_MODEL_HIDE(2492.9385f, -270.0593f, -40.12289f, 5.0f, joaat("ch_prop_ch_room_trolly_01a"), false);
			ENTITY::CREATE_MODEL_HIDE(2492.9385f, -270.0593f, -40.12289f, 5.0f, joaat("v_ind_ss_clothrack"), false);
			ENTITY::CREATE_MODEL_HIDE(2492.9385f, -270.0593f, -40.12289f, 5.0f, joaat("v_corp_banktrolley"), false);
		}
		else
		{
			ENTITY::REMOVE_MODEL_HIDE(2543.5105f, -248.7282f, -61.3736f, 15.0f, joaat("prop_bin_08open"), false);
			ENTITY::REMOVE_MODEL_HIDE(2543.5105f, -248.7282f, -61.3736f, 15.0f, joaat("prop_bin_08a"), false);
			ENTITY::REMOVE_MODEL_HIDE(2543.5105f, -248.7282f, -61.3736f, 15.0f, joaat("prop_rub_binbag_sd_01"), false);
			ENTITY::REMOVE_MODEL_HIDE(2543.5105f, -248.7282f, -61.3736f, 15.0f, joaat("prop_rub_binbag_03b"), false);
			ENTITY::REMOVE_MODEL_HIDE(2543.5105f, -248.7282f, -61.3736f, 15.0f, joaat("prop_rub_binbag_01b"), false);
			ENTITY::REMOVE_MODEL_HIDE(828.663f, -2210.613f, -46.829f, 10.0f, joaat("m23_2_prop_m32_rollerdoor_podium"), false);
			ENTITY::REMOVE_MODEL_HIDE(828.663f, -2257.905f, -46.829f, 10.0f, joaat("m23_2_prop_m32_rollerdoor_main"), false);
			ENTITY::REMOVE_MODEL_HIDE(862.517f, -2272.807f, -50.004f, 5.0f, joaat("m23_2_prop_m32_lobay_gate01"), false);
			ENTITY::REMOVE_MODEL_HIDE(2492.9385f, -270.0593f, -40.12289f, 5.0f, joaat("ch_prop_ch_room_trolly_01a"), false);
			ENTITY::REMOVE_MODEL_HIDE(2492.9385f, -270.0593f, -40.12289f, 5.0f, joaat("v_ind_ss_clothrack"), false);
			ENTITY::REMOVE_MODEL_HIDE(2492.9385f, -270.0593f, -40.12289f, 5.0f, joaat("v_corp_banktrolley"), false);
		}
	}

	int func_6922(int iParam0)//Position - 0x1F5CCF
	{
		int iVar0;

		iVar0 = 8;
		if (iVar0 == 32)
		{
			return iParam0;
		}
		return (7 - iParam0);
	}

	int func_7247(int iParam0)//Position - 0x216874
	{
		return func_6922(iParam0);
	}

	float func_7250(float fParam0)//Position - 0x216917
	{
		return (fParam0 * 0.017453292f);
	}

	void CasinoVehicleRobbery::func_7251(int iParam0)//Position - 0x216927
	{
		if (Rope != iParam0)
		{
			Rope = iParam0;
		}
	}

	void CasinoVehicleRobbery::RappelControl()
	{
		Var1 = { 820.565f, -2204.8052f, 30.954f };
		Var4 = { 821.3242f, -2204.8052f, 25.38204f };
		fVar7 = -47.741f;
		fVar8 = 78;
		fVar9 = 90;
		Var10 = { 90, 0, 90 };
		Var13 = { Var1 };
		if (!ROPE::DOES_ROPE_EXIST(&(Rope)))
		{
			ROPE::ROPE_LOAD_TEXTURES();
			if (ROPE::ROPE_ARE_TEXTURES_LOADED())
			{
				Rope = ROPE::ADD_ROPE(Var1.x, Var1.y, Var1.z, Var10.x, Var10.y, Var10.z, fVar8, 7, fVar8, fVar8, 0.5f, false, false, true, 10.0f, false, 0);
				invoke<Void>(0xA1AE736541B0FCA3, &(Rope), true);
			}
			ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), Var4.x, Var4.y, Var4.z, true, false, false, true);
			ENTITY::SET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID(), fVar9);
		}
		if (ROPE::DOES_ROPE_EXIST(&(Rope)))
		{
			if (AI::GET_SCRIPT_TASK_STATUS(PLAYER::PLAYER_PED_ID(), joaat("SCRIPT_TASK_RAPPEL_DOWN_WALL")) != 1 && AI::GET_SCRIPT_TASK_STATUS(PLAYER::PLAYER_PED_ID(), joaat("SCRIPT_TASK_RAPPEL_DOWN_WALL")) != 0)
			{
				if (!ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()))
				{
					invoke<Void>(0x82f4a39274853e9d, PLAYER::PLAYER_PED_ID(), Var1.x, Var1.y, Var1.z, Var1.x, Var1.y, Var1.z, fVar7, Rope, "clipset@anim_heist@hs3f@ig1_rappel@male", 1, func_7250(fVar9));
					PED::_0x2208438012482A1A(PLAYER::PLAYER_PED_ID(), true, true);
					ROPE::PIN_ROPE_VERTEX(Rope, (ROPE::GET_ROPE_VERTEX_COUNT(Rope) - 1), Var13.x, Var13.y, Var13.z);
					ROPE::_0xDC57A637A20006ED(Rope, 0);
					PED::_0x2208438012482A1A(Rope, false, false);
				}
			}
		}
		if (AI::GET_SCRIPT_TASK_STATUS(PLAYER::PLAYER_PED_ID(), joaat("SCRIPT_TASK_RAPPEL_DOWN_WALL")) == 1)
		{
			if (CAM::IS_SCREEN_FADED_OUT())
			{
				WAIT(2000);
				CAM::DO_SCREEN_FADE_IN(250);
				int start = GAMEPLAY::GET_GAME_TIMER();
				int time = 8000;
				DisplayHelpTimer = start + time;
			}
			else
			{
				if (GAMEPLAY::GET_GAME_TIMER() < DisplayHelpTimer)
				{
					UI::DISPLAY_HELP_TEXT_THIS_FRAME("VRPC_HLP_2" /* GXT: Hold ~INPUT_MOVE_DOWN_ONLY~ to rappel down.~n~Press ~INPUT_RAPPEL_JUMP~ to perform a short jump.~n~Press ~INPUT_RAPPEL_LONG_JUMP~ to perform a long jump. */, true);
				}
			}
			UI::_0x25F87B30C382FCA7(); /* THEFEED_HIDE_THIS_FRAME */
			CONTROLS::DISABLE_CONTROL_ACTION(0 /*PLAYER_CONTROL*/, 0 /*INPUT_NEXT_CAMERA*/, true);
			CONTROLS::DISABLE_CONTROL_ACTION(0 /*PLAYER_CONTROL*/, 37 /*INPUT_SELECT_WEAPON*/, true);
			CONTROLS::DISABLE_CONTROL_ACTION(0 /*PLAYER_CONTROL*/, 260 /*INPUT_RAPPEL_SMASH_WINDOW*/, true);
			CONTROLS::DISABLE_CONTROL_ACTION(0 /*PLAYER_CONTROL*/, 26 /*INPUT_LOOK_BEHIND*/, true);
			CONTROLS::DISABLE_CONTROL_ACTION(0 /*PLAYER_CONTROL*/, 1 /*INPUT_LOOK_LR*/, true);
			if (invoke<int>(0x29643b8a675f8422, PLAYER::PLAYER_PED_ID()) > 1)
			{
				if (invoke<int>(0x29643b8a675f8422, PLAYER::PLAYER_PED_ID()) == 4 || ENTITY::IS_ENTITY_IN_ANGLED_AREA(PLAYER::PLAYER_PED_ID(), 822.467f, -2201.292f, -50.70026f, 822.3497f, -2206.7815f, -47.20026f, 3.0f, false, true, 0))
				{
					UNK1::_0x81CBAE94390F9F89();
					// prepare the podium garage interior
					func_6767(0);
					Rollerdoor = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(828.684f, -2210.613f, -46.82876f, 2.0f, joaat("m23_2_prop_m32_rollerdoor_podium"), false, false, false);
					if (Rollerdoor != 0)
					{
						ENTITY::SET_ENTITY_COORDS(Rollerdoor, 828.684f, -2210.613f, -50.0f, false, false, false, false);
						ENTITY::SET_ENTITY_DYNAMIC(Rollerdoor, false);
						ENTITY::SET_ENTITY_CAN_BE_DAMAGED(Rollerdoor, false);
					}
					Rollerdoor2 = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(828.6841f, -2257.905f, -46.82876f, 2.0f, joaat("m23_2_prop_m32_rollerdoor_main"), false, false, false);
					if (Rollerdoor2 != 0)
					{
						ENTITY::SET_ENTITY_DYNAMIC(Rollerdoor2, false);
						ENTITY::SET_ENTITY_CAN_BE_DAMAGED(Rollerdoor2, false);
					}
					SpawnPodiumGarageGuards(false);

					CONTROLS::DISABLE_CONTROL_ACTION(0 /*PLAYER_CONTROL*/, 258 /*INPUT_RAPPEL_JUMP*/, true);
					CONTROLS::DISABLE_CONTROL_ACTION(0 /*PLAYER_CONTROL*/, 259 /*INPUT_RAPPEL_LONG_JUMP*/, true);
					
					int drawables[12];
					int textures[12];
					for (int i = 0; i < 12; i++)
					{
						drawables[i] = PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(), i);
						textures[i] = PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(), i);
					}

					CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(PLAYER::PLAYER_PED_ID(), (Any*)"MP_1", 0, 0, 0x40);

					CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"MP_2", 3, 0, 0x40);
					CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"Player_Pulley_2", 3, 0, 0x40);
					CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"Rope_Tie_2", 3, 0, 0x40);
					CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"Player_Rope_2", 3, 0, 0x40);

					CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"MP_3", 3, 0, 0x40);
					CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"Player_Pulley_3", 3, 0, 0x40);
					CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"Rope_Tie_3", 3, 0, 0x40);
					CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"Player_Rope_3", 3, 0, 0x40);

					CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"MP_4", 3, 0, 0x40);
					CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"Player_Pulley_4", 3, 0, 0x40);
					CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"Rope_Tie_4", 3, 0, 0x40);
					CUTSCENE::REGISTER_ENTITY_FOR_CUTSCENE(0, (Any*)"Player_Rope_4", 3, 0, 0x40);

					CUTSCENE::START_CUTSCENE(8);
					WAIT(500);
					for (int i = 0; i < 12; i++)
					{
						PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i, drawables[i], textures[i], 0);
					}

					while (!CUTSCENE::IS_CUTSCENE_PLAYING())
					{
						WAIT(0);
					}

					if (CAM::DOES_CAM_EXIST(RappelCam))
					{
						CAM::DESTROY_CAM(RappelCam, true);
						RappelCam = 0;
					}

					if (ROPE::DOES_ROPE_EXIST(&(Rope)))
					{
						ROPE::DELETE_ROPE(&(Rope));
						Rope = 0;
					}

					if (ROPE::ROPE_ARE_TEXTURES_LOADED())
					{
						ROPE::ROPE_UNLOAD_TEXTURES();
					}

					while (CUTSCENE::IS_CUTSCENE_PLAYING())
					{
						CONTROLS::DISABLE_CONTROL_ACTION(0, 18 /* INPUT_SKIP_CUTSCENE */, true);
						WAIT(0);
					}

					PED::SET_PED_CAN_SWITCH_WEAPON(PLAYER::PLAYER_PED_ID(), true);
					PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), false);
					CAM::RENDER_SCRIPT_CAMS(false, false, 3000, true, false);
					// let's make sure the hud/radar is visible
					UI::DISPLAY_HUD(true); 
					UI::DISPLAY_RADAR(true);
					Index = 4;
				}
			}
		}
	} // controls the rappelling sequence

	void CasinoVehicleRobbery::OpenRollerDoor()
	{
		if (ENTITY::DOES_ENTITY_EXIST(Rollerdoor))
		{
			if (!OBJECT::SLIDE_OBJECT(Rollerdoor, ENTITY::GET_ENTITY_COORDS(Rollerdoor, false).x, ENTITY::GET_ENTITY_COORDS(Rollerdoor, false).y, -46.82876f, 0.0f, 0.0f, 0.004f, false))
			{
				if (RollerDoorSoundId == -1)
				{
					RollerDoorSoundId = AUDIO::GET_SOUND_ID();
					AUDIO::PLAY_SOUND_FROM_ENTITY(RollerDoorSoundId, "METAL_SHUTTER_RAISE_LOOP", Rollerdoor, "GTAO_Script_Doors_Faded_Screen_Sounds", false, 0);
				}
			}
			else if (RollerDoorSoundId != -1)
			{
				AUDIO::STOP_SOUND(RollerDoorSoundId);
				AUDIO::RELEASE_SOUND_ID(RollerDoorSoundId);
				RollerDoorSoundId = -1;
				DEBUG::Debug::PrintToLog("Stopped & Released RollerDoor1SoundId.");
				UI::Screen::SendTextNotification("char_belle", "Belle", "Podium Robbery", "Oh ffs. Get movin the Casino's in full lockdown now.");
			}
			else
			{
				if (AlarmSoundId == -1 && AUDIO::REQUEST_SCRIPT_AUDIO_BANK("SCRIPT/ALARM_KLAXON_05", false))
				{
					AlarmSoundId = AUDIO::GET_SOUND_ID();
					AUDIO::PLAY_SOUND_FROM_COORD(AlarmSoundId, "Klaxon_05", 828.65f, -2229.3f, -45.0f, "ALARMS_SOUNDSET", false, 0, false);
				}

				AUDIO::SET_AMBIENT_ZONE_LIST_STATE_PERSISTENT("AZ_H3_Casino_Alarm_Zone_02_Interior", true, true);

				if (GAMEPLAY::_0x4C9296CBCD1B971E() != 3)
			    {
					GAMEPLAY::SET_FAKE_WANTED_LEVEL(3);
				}

				ShutRollerDoor2(false);
				IsFirstRollerdoorFullyUp_FLAG = true;
			}
		}
	}

	void CasinoVehicleRobbery::ShutRollerDoor2(bool openRollerDoor) // used for a different rollerdoor and similar to OpenRollerDoor() except this can be opened/closed
	{
		if (ENTITY::DOES_ENTITY_EXIST(Rollerdoor2))
		{
			if (!OBJECT::SLIDE_OBJECT(Rollerdoor2, ENTITY::GET_ENTITY_COORDS(Rollerdoor2, false).x, ENTITY::GET_ENTITY_COORDS(Rollerdoor2, false).y, openRollerDoor ? -46.8286f : -50.0f, 0.0f, 0.0f, openRollerDoor ? 0.004f : 0.024f, false))
			{
				if (RollerDoor2SoundId == -1)
				{
					RollerDoor2SoundId = AUDIO::GET_SOUND_ID();
					AUDIO::PLAY_SOUND_FROM_ENTITY(RollerDoor2SoundId, "METAL_SHUTTER_RAISE_LOOP", Rollerdoor2, "GTAO_Script_Doors_Faded_Screen_Sounds", false, 0);
				}
			}
			else if (RollerDoor2SoundId != -1)
			{
				AUDIO::STOP_SOUND(RollerDoor2SoundId);
				AUDIO::RELEASE_SOUND_ID(RollerDoor2SoundId);
				RollerDoor2SoundId = -1;
				DEBUG::Debug::PrintToLog("Stopped & Released RollerDoor2SoundId.");
			}
			else
			{

			}
		}
	}

	void CasinoVehicleRobbery::Dispose()
	{
		BaseMission::Dispose();
		TIME::PAUSE_CLOCK(false);

		if (ENTITY::DOES_ENTITY_EXIST(Boxville))
		{
			VEHICLE::DELETE_VEHICLE(&Boxville);
			Boxville = 0;
		}

		if (ENTITY::DOES_ENTITY_EXIST(BellePed))
		{
			PED::DELETE_PED(&BellePed);
			BellePed = 0;
		}

		// Checkpoints
		if (ParkBoxvilleCheckpoint != 0)
		{
			GRAPHICS::DELETE_CHECKPOINT(ParkBoxvilleCheckpoint);
			ParkBoxvilleCheckpoint = 0;
		}

		if (EscapeCasinoCheckpoint != 0)
		{
			GRAPHICS::DELETE_CHECKPOINT(EscapeCasinoCheckpoint);
			EscapeCasinoCheckpoint = 0;
		}

		if (DeliverCheckpoint != 0)
		{
			GRAPHICS::DELETE_CHECKPOINT(DeliverCheckpoint);
			DeliverCheckpoint = 0;
		}

		// Flags
		IsHardMode_FLAG = false;
		IsAlerted_FLAG = false;
		PlayerLocatedHatch_FLAG = false;
		IsFirstRollerdoorFullyUp_FLAG = false;
		ScriptBlipRoute_FLAG = false;

		VehicleDamageValue = 0;
		VehicleDamageTimer = 0;

		if (CUTSCENE::IS_CUTSCENE_PLAYING())
		{
			CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
			CUTSCENE::REMOVE_CUTSCENE();
		}

		// Stop the rollerdoors sounds
		if (!AUDIO::HAS_SOUND_FINISHED(RollerDoorSoundId) || RollerDoorSoundId != -1)
		{
			AUDIO::STOP_SOUND(RollerDoorSoundId);
			AUDIO::RELEASE_SOUND_ID(RollerDoorSoundId);
			RollerDoorSoundId = -1;
		}

		if (!AUDIO::HAS_SOUND_FINISHED(RollerDoor2SoundId) || RollerDoorSoundId != -1)
		{
			AUDIO::STOP_SOUND(RollerDoor2SoundId);
			AUDIO::RELEASE_SOUND_ID(RollerDoor2SoundId);
			RollerDoor2SoundId = -1;
		}

		// Blips
		if (UI::DOES_BLIP_EXIST(BoxvilleBlip))
		{
			UI::REMOVE_BLIP(&BoxvilleBlip);
			BoxvilleBlip = 0;
		}

		if (UI::DOES_BLIP_EXIST(BelleBlip))
		{
			UI::REMOVE_BLIP(&BelleBlip);
			BelleBlip = 0;
		}

		if (UI::DOES_BLIP_EXIST(ParkBoxvilleBlip))
		{
			UI::REMOVE_BLIP(&ParkBoxvilleBlip);
			ParkBoxvilleBlip = 0;
		}

		if (UI::DOES_BLIP_EXIST(LiftShaftBlip))
		{
			UI::REMOVE_BLIP(&LiftShaftBlip);
			LiftShaftBlip = 0;
		}

		if (UI::DOES_BLIP_EXIST(KeypadBlip))
		{
			UI::REMOVE_BLIP(&KeypadBlip);
			KeypadBlip = 0;
		}

		if (UI::DOES_BLIP_EXIST(RobberyVehicleBlip))
		{
			UI::REMOVE_BLIP(&RobberyVehicleBlip);
			RobberyVehicleBlip = 0;
		}

		if (UI::DOES_BLIP_EXIST(EscapeCasinoBlip))
		{
			UI::REMOVE_BLIP(&EscapeCasinoBlip);
			EscapeCasinoBlip = 0;
		}

		if (UI::DOES_BLIP_EXIST(DeliverBlip))
		{
			UI::REMOVE_BLIP(&DeliverBlip);
			DeliverBlip = 0;
		}

		LoadInteriors(true, true); // this handles a lot of the entities, IPLSs and more

		PLAYER::SET_EVERYONE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), false);
		PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), false);
		PLAYER::SET_MAX_WANTED_LEVEL(5);
		PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(), 0, false);
		GAMEPLAY::SET_FAKE_WANTED_LEVEL(0);
		PLAYER::SET_WANTED_LEVEL_MULTIPLIER(1.0f);
	}

	void CasinoVehicleRobbery::StopAllAlarms()
	{
		if (AUDIO::IS_AMBIENT_ZONE_ENABLED((Any*)"AZ_H3_Casino_Alarm_Zone_01_Exterior"))
		{
			AUDIO::SET_AMBIENT_ZONE_STATE_PERSISTENT("AZ_H3_Casino_Alarm_Zone_01_Exterior", 0, 0);
		}

		if (AUDIO::IS_AMBIENT_ZONE_ENABLED((Any*)"AZ_H3_Casino_Alarm_Zone_02_Interior"))
		{
			AUDIO::SET_AMBIENT_ZONE_STATE_PERSISTENT("AZ_H3_Casino_Alarm_Zone_02_Interior", 0, 0);
		}

		if (!AUDIO::HAS_SOUND_FINISHED(AlarmSoundId) || AlarmSoundId != 0)
		{
			AUDIO::STOP_SOUND(AlarmSoundId);
			AUDIO::RELEASE_SOUND_ID(AlarmSoundId);
			AlarmSoundId = -1;
		}

		if (AUDIO::REQUEST_SCRIPT_AUDIO_BANK("SCRIPT/ALARM_KLAXON_05", false))
		{
			AUDIO::RELEASE_NAMED_SCRIPT_AUDIO_BANK("SCRIPT/ALARM_KLAXON_05");
		}
	}

	void CasinoVehicleRobbery::InsertAccessKeycard(int keypad)
	{
		// Turning off the hud/radar makes this part look way more smooth
		UI::DISPLAY_HUD(false);
		UI::DISPLAY_RADAR(false);

		if (UI::IS_HELP_MESSAGE_BEING_DISPLAYED())
		{
			UI::CLEAR_HELP(true);
		}

		Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);	
		PLAYER::SET_EVERYONE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), true);
		PED::SET_PED_CAN_SWITCH_WEAPON(PLAYER::PLAYER_PED_ID(), false);
		WEAPON::SET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), GAMEPLAY::GET_HASH_KEY("WEAPON_UNARMED"), true);
		AUDIO::RELEASE_NAMED_SCRIPT_AUDIO_BANK("DLC_MPHEIST/HEIST_USE_KEYPAD");
		AUDIO::REQUEST_SCRIPT_AUDIO_BANK("DLC_MPHEIST/HEIST_USE_KEYPAD", false);

		STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("m23_2_prop_m32_accesscard_01a"));
		while (!STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("m23_2_prop_m32_accesscard_01a")))
		{
			WAIT(0);
		}
		Keycard = OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY("m23_2_prop_m32_accesscard_01a"), playerCoords.x, playerCoords.y, playerCoords.z - 2, false, true, false);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(GAMEPLAY::GET_HASH_KEY("m23_2_prop_m32_accesscard_01a"));
		if (ENTITY::DOES_ENTITY_EXIST(Keycard))
		{
			ENTITY::FREEZE_ENTITY_POSITION(Keycard, true);
			ENTITY::SET_ENTITY_COLLISION(Keycard, false, false);
		}

		STREAMING::REQUEST_ANIM_DICT("anim@heists@keycard@");
		while (!STREAMING::HAS_ANIM_DICT_LOADED("anim@heists@keycard@"))
		{
			WAIT(0);
		}

		Vector3 keypadOffset = ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(keypad, -0.025f, -0.8f, -0.3f);
		ENTITY::ATTACH_ENTITY_TO_ENTITY(Keycard, PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), 28422), 0.0f, 0.0f, 0.0f, 270.0f, 0.0f, 0.0f, false, false, false, false, 2, true);

		int sequence;
		float fParam1 = ENTITY::GET_ENTITY_HEADING(keypad);
		AI::OPEN_SEQUENCE_TASK(&sequence);
		AI::TASK_GO_STRAIGHT_TO_COORD(0, keypadOffset.x, keypadOffset.y, keypadOffset.z, 0.75f, -1, fParam1, 0.1f);
		AI::TASK_ACHIEVE_HEADING(0, fParam1, 0);
		AI::TASK_PLAY_ANIM(0, "anim@heists@keycard@", "enter", 8.0f, -8.0f, -1, 0, 0, false, false, false);
		AI::TASK_PLAY_ANIM(0, "anim@heists@keycard@", "idle_a", 8.0f, -8.0f, -1, 0, 0, false, false, false);
		AI::TASK_PLAY_ANIM(0, "anim@heists@keycard@", "exit", 8.0f, -8.0f, -1, 0, 0, false, false, false);
		AI::CLOSE_SEQUENCE_TASK(sequence);
		AI::TASK_PERFORM_SEQUENCE(PLAYER::PLAYER_PED_ID(), sequence);
		AI::CLEAR_SEQUENCE_TASK(&sequence);
		
		while (AI::GET_SEQUENCE_PROGRESS(PLAYER::PLAYER_PED_ID()) != 4) WAIT(0);

		AUDIO::RELEASE_NAMED_SCRIPT_AUDIO_BANK("DLC_MPHEIST/HEIST_USE_KEYPAD");
		STREAMING::REMOVE_ANIM_DICT("anim@heists@keycard@");
		if (ENTITY::DOES_ENTITY_EXIST(Keycard))
		{
			if (ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(Keycard, PLAYER::PLAYER_PED_ID()))
			{
				ENTITY::DETACH_ENTITY(Keycard, true, true);
			}

			OBJECT::DELETE_OBJECT(&Keycard);
			Keycard = 0;
		}

		PED::SET_PED_CAN_SWITCH_WEAPON(PLAYER::PLAYER_PED_ID(), true);
		PLAYER::SET_EVERYONE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), false);
		UI::DISPLAY_HUD(true);
		UI::DISPLAY_RADAR(true);
	}

	void CasinoVehicleRobbery::SetupGuard(int ped)
	{
		if (ENTITY::DOES_ENTITY_EXIST(ped))
		{
			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, true);
			PED::SET_PED_SEEING_RANGE(ped, IsHardMode_FLAG ? 8.0f : 4.0f);
			PED::SET_PED_HEARING_RANGE(ped, IsHardMode_FLAG ? 100.0f : 50.0f);
			PED::SET_PED_VISUAL_FIELD_PERIPHERAL_RANGE(ped, IsHardMode_FLAG ? 4.0f : 2.0f);
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

			invoke<Void>(0xBF0FD6E56C964FCB, ped, joaat(IsHardMode_FLAG ? "WEAPON_SMG" : "WEAPON_PISTOL"), 0, true, true); /* GIVE_WEAPON_TO_PED */
			WEAPON::SET_PED_INFINITE_AMMO(ped, true, joaat(IsHardMode_FLAG ? "WEAPON_SMG" : "WEAPON_PISTOL"));
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(ped, true);
			PED::SET_PED_CONFIG_FLAG(ped, 38, true);
			PED::SET_PED_COMBAT_ATTRIBUTES(ped, 13, true);
			PED::SET_PED_COMBAT_ATTRIBUTES(ped, 39, true);
			PED::SET_PED_COMBAT_MOVEMENT(ped, 3);
			PED::SET_PED_ACCURACY(ped, IsHardMode_FLAG ? 100 : 50); // make the accuracy double if its on hard mode
		}
	}

	void CasinoVehicleRobbery::CheckOnGuards()
	{
		switch (Index)
		{
		    case 2:
		    {
				for (auto ped = HotelGuards.begin(); ped != HotelGuards.end(); ++ped)
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
							AUDIO::TRIGGER_MUSIC_EVENT("MP242_GUNFIGHT");
							IsAlerted_FLAG = true;
						}

						if (IsAlerted_FLAG)
						{
							if (!AUDIO::IS_AMBIENT_ZONE_ENABLED((Any*)"AZ_H3_Casino_Alarm_Zone_01_Exterior"))
							{
								AUDIO::SET_AMBIENT_ZONE_STATE_PERSISTENT("AZ_H3_Casino_Alarm_Zone_01_Exterior", 1, 1);
							}

							if (!AUDIO::IS_AMBIENT_ZONE_ENABLED((Any*)"AZ_H3_Casino_Alarm_Zone_02_Interior"))
							{
								AUDIO::SET_AMBIENT_ZONE_STATE_PERSISTENT("AZ_H3_Casino_Alarm_Zone_02_Interior", 1, 1);
							}

							if (UI::DOES_BLIP_EXIST(attachedBlip) && attachedBlip != 0)
							{
								invoke<Void>(0x13127EC3665E8EE1, attachedBlip, false, 11); /* SET_BLIP_SHOW_CONE */

								if (AI::GET_SCRIPT_TASK_STATUS(*ped, joaat("SCRIPT_TASK_COMBAT_PED")) != 1)
								{
									AI::TASK_COMBAT_PED(*ped, PLAYER::PLAYER_PED_ID(), 0, 16);
								}
							}
						}
					}
				}
		    }
		    break;
			case 5:
		    case 6:
		    case 7:
		    {
				for (auto ped = PodiumGarageGuards.begin(); ped != PodiumGarageGuards.end(); ++ped)
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
							AUDIO::TRIGGER_MUSIC_EVENT("MP242_GUNFIGHT");
							IsAlerted_FLAG = true;
						}

						if (IsAlerted_FLAG)
						{
							if (UI::DOES_BLIP_EXIST(attachedBlip) && attachedBlip != 0)
							{
								invoke<Void>(0x13127EC3665E8EE1, attachedBlip, false, 11); /* SET_BLIP_SHOW_CONE */

								if (AI::GET_SCRIPT_TASK_STATUS(*ped, joaat("SCRIPT_TASK_COMBAT_PED")) != 1)
								{
									AI::TASK_COMBAT_PED(*ped, PLAYER::PLAYER_PED_ID(), 0, 16);
								}
							}
						}
					}
				}
		    }
		    break;
		}
	}

	void CasinoVehicleRobbery::FailConditions()
	{
		switch (Index)
		{
		     case 1:
		     {
				 if (ENTITY::DOES_ENTITY_EXIST(Boxville))
				 {
					 if (ENTITY::IS_ENTITY_DEAD(Boxville))
					 {
						 TriggerFail("The Post OP Van was destroyed.");
					 }
				 }

				 if (ENTITY::DOES_ENTITY_EXIST(BellePed))
				 {
					 if (ENTITY::IS_ENTITY_DEAD(BellePed)) // poor belle :(
					 {
						 TriggerFail("Belle died.");
					 }
				 }
        	 }
		     break;

			 case 6:
			 case 7:
			 {
				 if (ENTITY::DOES_ENTITY_EXIST(RobberyVehicle))
				 {
					 if (ENTITY::IS_ENTITY_DEAD(RobberyVehicle))
					 {
						 TriggerFail("The DR8 was destroyed.");
					 }
				 }
			 }
			 break;
		}
	}

	void CasinoVehicleRobbery::TrackVehicleDamage()
	{
		switch (Index)
		{
		case 6:
		case 7:
		{
			if (ENTITY::DOES_ENTITY_EXIST(RobberyVehicle))
			{
				if (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ANY_OBJECT(RobberyVehicle) || ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ANY_PED(RobberyVehicle) || ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ANY_VEHICLE(RobberyVehicle))
				{
					if (GAMEPLAY::GET_GAME_TIMER() > VehicleDamageTimer)
					{
						VehicleDamageValue += GAMEPLAY::GET_RANDOM_INT_IN_RANGE(1000, 5000);
						ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(RobberyVehicle);
						VehicleDamageTimer = GAMEPLAY::GET_GAME_TIMER() + 1000;
					}
				}
			}
		}
		break;
		}
	}

	void CasinoVehicleRobbery::TriggerFail(std::string reason)
	{
		if (!CAM::IS_SCREEN_FADING_OUT() && !CAM::IS_SCREEN_FADED_OUT())
		{
			CAM::DO_SCREEN_FADE_OUT(250);
		}

		while (CAM::IS_SCREEN_FADING_OUT())
		{
			WAIT(0);
		}

		UI::CLEAR_ALL_HELP_MESSAGES();
		Dispose();
		ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 834.555f, -96.928f, 80.594f, false, false, false, false);
		ENTITY::SET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID(), -30.0f);
		invoke<Void>(0xF28965D04F570DCA, PLAYER::PLAYER_PED_ID(), joaat("MotionState_Idle"), false, true, false); /* FORCE_PED_MOTION_STATE */
		CAM::SET_GAMEPLAY_CAM_RELATIVE_HEADING(0.0f);
		WAIT(2000);
		CAM::DO_SCREEN_FADE_IN(250);
		while (CAM::IS_SCREEN_FADING_IN())
		{
			WAIT(0);
		}
		UI::Scaleforms::MidsizedMessage midsizedMessage;
		midsizedMessage.Show("ROBBERY FAILED", (char*)reason.c_str(), 6 /* Red */);
		std::string failMsgs[3] = { "You had one fucking job. Come back to the Clubhouse when you're ready.", "Why do I even bother? Come back to the Clubhouse when you're ready.", "Fuck sake. Come back to the Clubhouse when you're ready." };
		UI::Screen::SendTextNotification("char_belle", "Belle", "Podium Robbery", failMsgs[GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 3)]);
	}
}