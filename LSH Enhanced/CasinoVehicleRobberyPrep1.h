#pragma once

#include "BaseMission.h"
#include "script.h"
#include "Extensions.h"
#include "string"
#include "Screen.h"
#include "list"
#include "MidsizedMessage.h"
#include "vector";
#include "stdexcept"
#include "Debug.h"

namespace Missions
{
	class CasinoVehicleRobberyPrep1 : public BaseMission
	{
	public:
        #pragma region Fields

		int ApartmentIndex;

		int EnterApartmentBlip;

		int SyncScene;

		int Cam;

		int Valet, ValetBlip, Safe, SafeDoor, AccessCard, SafeBlip;

		int ValetSpeechCooldownTimer;

		int ValetSpeechStage = 0;

		float IntimidateValet = 0.0f;

		bool IsValetCowering_FLAG = false;

		bool IsAlerted_FLAG = false;

		std::list<int> GarageVehicles;

		std::list<int> Guards;

		int AlarmSoundId = -1;

		int ElevBlip, ElevCheckpoint;

		int PostOpBlip;

        #pragma endregion

        #pragma region Methods

		void Update() override;

		void Init() override;

		void Dispose() override;

		std::string GetApartmentName();

		Extensions::Vector3 EnterApartmentAnimPosition();

		float EnterApartmentAnimHeading();

	    Extensions::Vector3 InteriorPositions();

		Extensions::Vector3 InteriorPropPositions(int index);

		float InteriorPropHeadings(int index);

		Extensions::Vector3 ValetSpawnPositions();

		float ValetSpawnHeadings();

		void SetupGuard(int ped);

		void CheckOnGuards();

		void LoadInteriors(bool cleanup);

		Extensions::Vector3 ApartmentSpawnPosition();

		float ApartmentSpawnHeading();

		void HideApartmentExterior();

		void OpenSafe();

		Extensions::Vector3 ElevatorCoronaPosition();

		void SetupGarage(bool cleanup);

        #pragma endregion
	};
}