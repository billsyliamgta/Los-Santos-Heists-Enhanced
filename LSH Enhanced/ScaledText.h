#pragma once

#include "Extensions.h"
#include "string"
#include "script.h"
#include "Screen.h"

namespace UI
{
	class ScaledText
	{
	public:

		enum GTAFontTypes : int
		{
			ChaletLondon = 0,
			HouseScript = 1,
			Monospace = 2,
			ChaletComprimeColonge = 4,
			Pricedown = 7
		};

		enum TextAlignment : int
		{
			Left = 0,
			Centre = 1,
			Right = 2
		};

		Extensions::PointF Position;
		
		float Scale;

		GTAFontTypes Font;

		TextAlignment Alignment;

		/// <summary>
		/// When true this will add a dollar sign and commas when needed. E.g $1,000
		/// </summary>
		bool IsNumberFormat;

		bool Center;

		/// <summary>
		/// What text should be displayed when drawn
		/// </summary>
		std::string Caption;

		/// <summary>
		/// By default the color will be white however you can change it to anything you like
		/// </summary>
		Extensions::Color Color;

		void Draw();

		ScaledText(std::string caption, Extensions::PointF position, float scale, GTAFontTypes font = GTAFontTypes::ChaletLondon,
			bool centre = false, bool isNumberFormat = false, const Extensions::Color& color = Extensions::Color(255, 255, 255, 255))
			: Caption(caption), Position(position), Scale(scale), Font(font), Center(centre), IsNumberFormat(isNumberFormat), Color(color)
		{
		}

		virtual ~ScaledText() {};
	};
}