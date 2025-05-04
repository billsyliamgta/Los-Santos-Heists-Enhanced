#include "BelleGarageProperty.h"

void PROPERTIES::BelleGarageProperty::Control()
{
	if (!UI::DOES_BLIP_EXIST(PropertyBlip))
	{

	}
	else
	{
		UI::SET_BLIP_ALPHA(PropertyBlip, IsPlayerInsideGarage() ? 0 : 255);
	}


	if (IsPlayerInsideGarage())
	{
		if (!IntializedScaleforms_FLAG)
		{
			SetupScaleforms();
			return;
		}
		DrawScaleforms();
	}
	else if (IntializedScaleforms_FLAG)
	{
		DisposeScaleforms();
	}
}

void PROPERTIES::BelleGarageProperty::SetupScaleforms()
{
	ComputerScaleform = GRAPHICS::REQUEST_SCALEFORM_MOVIE((char*)ComputerScaleformName);
	while (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(ComputerScaleform)) WAIT(0);

	if (ComputerRT == nullptr)
	{
		ComputerRT = new UI::RenderTarget("m32_crtscreen_01a", -1492862692);
	}

	PlanningScaleform = GRAPHICS::REQUEST_SCALEFORM_MOVIE((char*)PlanningScaleformName);
	while (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(PlanningScaleform)) WAIT(0);

	if (PlanningRT == nullptr)
	{
		PlanningRT = new UI::RenderTarget("m32_yarduv_plan_01a", 1553525713);
	}

	GenerateVehicleData();
	IntializedScaleforms_FLAG = true;
	DEBUG::Debug::PrintToLog("Successfully loaded Belle's Garage Scaleforms and Render Targets.");
}

void PROPERTIES::BelleGarageProperty::SetPlanningHeading(std::string heading)
{
	if (GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(PlanningScaleform))
	{
		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(PlanningScaleform, "SET_HEADING");
		GRAPHICS::_BEGIN_TEXT_COMPONENT("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING((char*)heading.c_str());
		GRAPHICS::_END_TEXT_COMPONENT();
		GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION();
	} 
}

void PROPERTIES::BelleGarageProperty::DrawScaleforms()
{
	if (GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(PlanningScaleform) && PlanningRT != nullptr)
	{
		invoke<Void>(0xE6A9F00D4240B519, PlanningScaleform, 1);
		UI::SET_TEXT_RENDER_ID(PlanningRT->Handle);
		invoke<Void>(0x61BB1D9B3A95D802, 4);
		invoke<Void>(0xC6372ECD45D73BCD, true);
		GRAPHICS::DRAW_SCALEFORM_MOVIE(PlanningScaleform, 0.25f, 0.5f, 0.5f, 1.0f, 255, 255, 255, 255, 0);
		UI::SET_TEXT_RENDER_ID(-1);
	}
}

void PROPERTIES::BelleGarageProperty::DisposeScaleforms()
{
	if (GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(ComputerScaleform))
	{
		GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&ComputerScaleform);
		ComputerScaleform = 0;
	}

	if (ComputerRT != nullptr)
	{
		ComputerRT->Release();
		ComputerRT = nullptr;
	}

	if (GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(PlanningScaleform))
	{
		GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&PlanningScaleform);
		PlanningScaleform = 0;
	}

	if (PlanningRT != nullptr)
	{
		PlanningRT->Release();
		PlanningRT = nullptr;
	}

	IntializedScaleforms_FLAG = false;
	DEBUG::Debug::PrintToLog("Disposed Belle's Garage Scaleforms and Render Targets.");
}

const bool PROPERTIES::BelleGarageProperty::IsPlayerInsideGarage()
{
	return INTERIOR::GET_INTERIOR_FROM_ENTITY(PLAYER::PLAYER_PED_ID()) == INTERIOR::GET_INTERIOR_AT_COORDS(interiorCoords.x, interiorCoords.y, interiorCoords.z);
}

void PROPERTIES::BelleGarageProperty::SetupIPL()
{
	int interiorId = INTERIOR::GET_INTERIOR_AT_COORDS(interiorCoords.x, interiorCoords.y, interiorCoords.z);
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

		INTERIOR::_DISABLE_INTERIOR_PROP(interiorId, "entity_set_backdrop_frames");
		INTERIOR::_DISABLE_INTERIOR_PROP(interiorId, "entity_set_no_plus");
		INTERIOR::_DISABLE_INTERIOR_PROP(interiorId, "entity_set_plus");
		INTERIOR::_DISABLE_INTERIOR_PROP(interiorId, "entity_set_signs");
		INTERIOR::_DISABLE_INTERIOR_PROP(interiorId, "entity_set_stairs");
		INTERIOR::REFRESH_INTERIOR(interiorId);

		AUDIO::SET_STATIC_EMITTER_ENABLED("se_m23_1_dlc_int_02_m23_1_warehouse_medium_01", false);
		AUDIO::SET_STATIC_EMITTER_ENABLED("se_m23_1_dlc_int_02_m23_1_warehouse_medium_02", false);
		AUDIO::SET_STATIC_EMITTER_ENABLED("se_m23_1_dlc_int_02_m23_1_warehouse_medium_03", false);
		AUDIO::SET_STATIC_EMITTER_ENABLED("se_m23_1_dlc_int_02_m23_1_warehouse_medium_04", false);
	}
}

void PROPERTIES::BelleGarageProperty::SpawnProps(bool cleanup)
{
	if (cleanup)
	{
		if (ENTITY::DOES_ENTITY_EXIST(TableProp))
		{
			OBJECT::DELETE_OBJECT(&TableProp);
			TableProp = 0;
		}
		DEBUG::Debug::PrintToLog("Cleaned up Belle's Garage Property props.");
	}
	else
	{
		STREAMING::REQUEST_MODEL(-799726175);
		while (!STREAMING::HAS_MODEL_LOADED(-799726175)) WAIT(0);

		TableProp = OBJECT::CREATE_OBJECT(-799726175, 1190.044f, -3259.767f, -49.99305f, false, true, false);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(-799726175);
		if (ENTITY::DOES_ENTITY_EXIST(TableProp))
		{
			ENTITY::SET_ENTITY_HEADING(TableProp, -180.0f);
			ENTITY::FREEZE_ENTITY_POSITION(TableProp, true);
		}
		DEBUG::Debug::PrintToLog("Belle's Garage Property props spawned.");
	}
}