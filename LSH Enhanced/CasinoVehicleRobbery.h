#pragma once

#include "BaseMission.h"
#include "vector"
#include "cmath"
#include "string"
#include "list"
#include "Extensions.h"

namespace Missions
{
	class CasinoVehicleRobbery : public BaseMission
	{
	public:

        #pragma region Fields

		int BellePed;

		int Boxville;
        

		int DisplayHelpTimer = 0;

		Extensions::Vector3 Var1;

		Extensions::Vector3 Var4;

		float fVar7;

		float fVar8;

		float fVar9;

		Extensions::Vector3 Var10;

		Extensions::Vector3 Var13;

		Extensions::Vector3 Var18;

		int iLocal_9096 = 0;

		int Rope;

		int RappelCam;

		int RollerDoorSoundId = -1;

		int RollerDoor2SoundId = -1;

		int AlarmSoundId = -1;

		int Crate;

		int CrateCam;

		int SyncScene;

		std::list<int> HotelGuards;
		
		int LiftShaft;

		int LiftShaftHatch;

		int Keycard;

		int Rollerdoor;

		int Rollerdoor2;

		int Keypad;

		int Keypad2;

		int RobberyVehicle;

		int CoveredVehicleProp;

		int CoveredVehicleProp2;

		int CoveredVehicleProp3;

		int CoveredVehicleProp4;

		int CoveredVehicleProp5;

		int CoveredVehicleProp6;

		int PodiumGarageConcreteBlock;

		int PodiumGarageConcreteBlock2;

		int PodiumGarageConcreteBlock3;

		std::list<int> PodiumGarageGuards; 

		bool IsHardMode_FLAG = true;

		bool IsAlerted_FLAG = false;

		bool PlayerLocatedHatch_FLAG = false;

		bool IsFirstRollerdoorFullyUp_FLAG = false;

		bool ScriptBlipRoute_FLAG = false;

		int BelleBlip;

		int BoxvilleBlip;

		int ParkBoxvilleBlip;

		int LiftShaftBlip;

		int KeypadBlip;

		int RobberyVehicleBlip;

		int EscapeCasinoBlip;

		int DeliverBlip;

		int ParkBoxvilleCheckpoint;

		int EscapeCasinoCheckpoint;

		int DeliverCheckpoint;

        #pragma endregion

        #pragma region Methods

		int VehicleDamageValue;

		int VehicleDamageTimer;

		void TrackVehicleDamage();

		void Update() override;

		void Init() override;

		void LoadInteriors(bool cleanup, bool removeRobberyVehicle);

		void JumpOutCrate();

		void SpawnHotelGuards(bool cleanup);

		void SpawnPodiumGarageGuards(bool cleanup);

		void func_6767(bool bParam0);

		void func_7251(int iParam0);

		void RappelControl();

		void OpenRollerDoor();

		void ShutRollerDoor2(bool openRollerDoor);

		void SetupGuard(int ped);

		void Dispose() override;

		void StopAllAlarms();

		void InsertAccessKeycard(int keypad);

		void CheckOnGuards();

		void FailConditions();

		void TriggerFail(std::string reason);

        #pragma endregion
	};
}