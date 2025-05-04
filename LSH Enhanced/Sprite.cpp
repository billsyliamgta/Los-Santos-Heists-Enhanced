#include "Sprite.h"

void UI::Elements::Sprite::Draw()
{
	while (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)Texture.first.c_str()))
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)Texture.first.c_str(), true);
		WAIT(0);
	}

	int screenw = UI::Screen::Width;
	int screenh = UI::Screen::Height;
	const float height = 1080;
	float ratio = screenw / screenh;
	float width = height * ratio;
	float w = (Size.Width / width);
	float h = (Size.Height / height);
	float x = (Position.x / width) + w * 0.5f;
	float y = (Position.y / height) + h * 0.5f;
	GRAPHICS::DRAW_SPRITE((char*)Texture.first.c_str(), (char*)Texture.second.c_str(), x, y, w, h, Heading, Color.R, Color.G, Color.B, Color.A);
}

void UI::Elements::Sprite::Dispose()
{
	if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)Texture.first.c_str()))
	{
		GRAPHICS::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED((char*)Texture.first.c_str());
	}
}