#include "ScaledText.h"

void UI::ScaledText::Draw()
{
	int screenw = 1280;
	int screenh = 720;
	const float height = 1080.0f;
	float ratio = (float)screenw / screenh;
	float width = height * ratio;
	float x = (Position.x) / width;
	float y = (Position.y) / height;

	UI::SET_TEXT_FONT((int)Font);
	UI::SET_TEXT_SCALE(Scale, Scale);
	UI::SET_TEXT_COLOUR(Color.R, Color.G, Color.B, Color.A);
	switch ((int)Alignment)
	{
	   break;
	   case 1:
	   {
		   UI::SET_TEXT_CENTRE(true);
	   }
	   break;
	   case 2:
	   {
		   UI::SET_TEXT_RIGHT_JUSTIFY(true);
		   UI::SET_TEXT_WRAP(0, x);
	   }
	   break;
	}
	UI::_SET_TEXT_ENTRY(IsNumberFormat ? "ESDOLLA" : "STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((char*)Caption.c_str());
	UI::_DRAW_TEXT(x, y);
}