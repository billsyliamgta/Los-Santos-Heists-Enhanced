#pragma once

#include "Extensions.h"
#include "Screen.h"
#include "script.h"
#include <iostream>
#include <utility>
#include <string>

namespace UI::Elements
{
	class Sprite
	{
	public:
		Extensions::PointF Position;

		Extensions::SizeF Size;

		Extensions::Color Color;

		bool Visible = true;

		float Heading;

		std::pair<std::string, std::string> Texture;

		Sprite(std::string textureDict, std::string textureName, Extensions::PointF position, Extensions::SizeF size, float heading, const Extensions::Color& color)
			: Texture(std::make_pair(textureDict, textureName)), Position(position), Size(size), Heading(heading), Color(color)
		{
		}

		void Draw();

		void Dispose();
	};
}