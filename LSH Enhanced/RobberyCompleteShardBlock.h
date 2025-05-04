#pragma once

#include <string>

namespace UI::Scaleforms
{
	class RobberyCompleteShardBlock
	{
	public:
		float fVar1;

		float fVar9;

		float fVar10;

		float fVar20;

		float fVar21;

		float fVar22;

		std::string Label;

		int Value;

		RobberyCompleteShardBlock(std::string label, int value)
		{
			Label = label;
			Value = value;
		}

		virtual ~RobberyCompleteShardBlock() {};

		void Draw(int alpha, float posY);

		float func_14613(float fParam0);

		float func_14612();
	};
}