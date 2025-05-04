#include "RobberyCompleteShardBlock.h"
#include "script.h"

void UI::Scaleforms::RobberyCompleteShardBlock::Draw(int alpha, float posY)
{
	fVar1 = 0.3f * func_14612();
	fVar1 -= func_14613(6);
	fVar1 += func_14613(30) - func_14613(4);

	// Setup the label text that's drawn on the left hand side
	fVar9 = 0.30500004f;
	fVar10 = 0.693f;
	UI::SET_TEXT_COLOUR(255, 255, 255, alpha);
	UI::SET_TEXT_WRAP(fVar9, fVar10);
	UI::SET_TEXT_JUSTIFICATION(1);
	UI::SET_TEXT_SCALE(1, 0.4f);
	UI::SET_TEXT_CENTRE(false);
	UI::SET_TEXT_FONT(0);
	fVar20 = fVar9;
	fVar20 = fVar9 + 0.119f / func_14612() / 2.5f;
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((char*)Label.c_str());
	UI::_DRAW_TEXT(fVar20, fVar1 + func_14613(posY * 2));

	// And finally we set the value text that's drawn on the right hand side
	fVar21 = 0.5f;
	fVar21 += 0.143f;
	fVar22 = fVar21;
	fVar22 -= 0.286f;
	UI::SET_TEXT_COLOUR(255, 255, 255, alpha);
	UI::SET_TEXT_WRAP(fVar20, fVar21);
	UI::SET_TEXT_JUSTIFICATION(2);
	UI::SET_TEXT_SCALE(1, 0.4f);
	UI::SET_TEXT_CENTRE(false);
	UI::SET_TEXT_FONT(0);
	UI::_SET_TEXT_ENTRY("ESDOLLA");
	UI::ADD_TEXT_COMPONENT_INTEGER(Value);
	UI::_0x0E4C749FF9DE9CC4(Value, true);
	UI::_DRAW_TEXT(fVar20, fVar1 + func_14613(posY * 2));
}

float UI::Scaleforms::RobberyCompleteShardBlock::func_14613(float fParam0)
{
	return fParam0 * 0.0013888889f;
}

float UI::Scaleforms::RobberyCompleteShardBlock::func_14612()
{
	float result = 1;
	if (GAMEPLAY::IS_PC_VERSION())
	{

	}
	return result;
}