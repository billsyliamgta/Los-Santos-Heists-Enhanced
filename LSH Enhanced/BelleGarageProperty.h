#pragma once

#include <string>
#include <list>
#include "script.h"
#include "RenderTarget.h"
#include "Debug.h"
#include "Extensions.h"

namespace PROPERTIES
{
	class BelleGarageProperty
	{
	public:
		enum ComputerScaleformState : int
		{
			STATE_AVAILABLE = 0,
		    STATE_PAID = 1,
		    STATE_SALVAGED = 2,
		    STATE_OWNED = 3,
		    STATE_IN_PROGRESS = 4,
		    STATE_ACQUIRED = 5,
		    STATE_SALVAGING = 6,
		    STATE_UNAVAILABLE = 7,
		};

		enum PlanningButtonId : int
		{
			TASK = 100,
		    PREP_1 = 101,
		    PREP_2 = 102,
		    PREP_3 = 103,
	        START = 104,
		    TODO_BASE = 106,
		};

		struct VehicleData
		{
		public:
			std::string Label;

			std::string Txd;

			std::string Txn;

			int Value;

			VehicleData(std::string label, std::string txd, std::string txn, int value)
			{
				Label = label;
				Txd = txd;
				Txn = txn;
				Value = value;
			}

			void PushScaleformFunctionFromData(int scaleform, int index)
			{
				if (GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(scaleform))
				{
					for (int i = 0; i < 3; i++)
					{
						GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(scaleform, "CLEAR_VEHICLE");
						GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(i);
						GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION();
					}

					GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(scaleform, "SET_VEHICLE");
					GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(index);
					
					if (UI::DOES_TEXT_LABEL_EXIST((char*)Label.c_str()))
					{
						GRAPHICS::_BEGIN_TEXT_COMPONENT((char*)Label.c_str());
						GRAPHICS::_END_TEXT_COMPONENT();
					}
					else
					{
						GRAPHICS::_BEGIN_TEXT_COMPONENT("STRING");
						UI::_ADD_TEXT_COMPONENT_STRING("null");
						GRAPHICS::_END_TEXT_COMPONENT();
						DEBUG::Debug::PrintToLog("ERROR: Could not find GXT entry " + Label);
					}

					GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_STRING((char*)Txn.c_str());
					GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_STRING((char*)Txn.c_str());
					GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(Value);

					GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_BOOL(false); // ownable
					GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION();
					DEBUG::Debug::PrintToLog("Successfully pushed Vehicle Data for index " + std::to_string(index));
				}
				else
				{
					DEBUG::Debug::PrintToLog("ERROR: Unable to push Scaleform Movie functions because the handle isn't loaded.");
				}
			}
		};

		/// <summary>
		/// Control's everything from entering, while inside and exiting.
		/// </summary>
		void Control();

		/// <summary>
		/// The property blip seen on the map before entering the Garage.
		/// </summary>
		int PropertyBlip;

        #pragma region Scaleforms/RenderTargets

		const char* ComputerScaleformName = "SALVAGE_VEHICLE_TARGETS";

		const char* PlanningScaleformName = "SALVAGE_PLANNING";

		int ComputerScaleform = 0;

		int PlanningScaleform = 0;

		UI::RenderTarget* ComputerRT;

		UI::RenderTarget* PlanningRT;

		std::list<VehicleData> VehicleDatas;

		void GenerateVehicleData()
		{
			if (!VehicleDatas.empty()) // if the vehicle data list is not empty we can push the data
			{
				int index = 0;
				for (auto it = VehicleDatas.begin(); it != VehicleDatas.end(); ++it)
				{
					it->PushScaleformFunctionFromData(ComputerScaleform, index);
					index++;
				}
			}
			else // otherwise, no
			{
				DEBUG::Debug::PrintToLog("ERROR: Cannot generate Vehicle Data because the list is empty.");
			}
		}

		bool IntializedScaleforms_FLAG = false;

		void SetupScaleforms();

		/// <summary>
		/// Set's the heading (or title) of the Planning Scaleform.
		/// </summary>
		/// <param name="heading"></param>
		void SetPlanningHeading(std::string heading);

		/// <summary>
		/// Handles drawing of the 2 Scaleforms. Make sure you call the GenerateVehicleData function before using this otherwise nothing will be loaded.
		/// </summary>
		void DrawScaleforms();

		/// <summary>
		/// Disposes the 2 Scaleforms and its Render Targets.
		/// </summary>
		void DisposeScaleforms();

        #pragma endregion

        #pragma region Interior

		/// <summary>
		/// Coordinates of the interior
		/// </summary>
		Extensions::Vector3 interiorCoords = { 1200.0f, -3250.0f, -50.0f };

		const bool IsPlayerInsideGarage();

		int TableProp;

		void SetupIPL();

		void SpawnProps(bool cleanup);

        #pragma endregion

        #pragma region Progress 

        #pragma endregion
	};
}