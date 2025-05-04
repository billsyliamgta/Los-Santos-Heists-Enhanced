#pragma once

#include "script.h"
#include "list"
#include "RobberyCompleteShardBlock.h"

namespace UI::Scaleforms
{
	class RobberyCompleteShard
	{
	public:
		int Handle;

		float fVar1;

		float fVar2;

		float fVar3;

		float fVar11;

		float fVar12;

		float fVar9;

		float fVar10;

		float fVar20;

		float fVar21;

		float fVar22;

		std::string Title;

		std::string Subtitle;

		std::string BottomLabel;

		int BottomValue;

		std::list<RobberyCompleteShardBlock> Blocks;

		void Load();

		void Dispose();

		void Show();

		float func_14607(float fParam0);

		float func_14612();

		float func_14613(float fParam0);

		RobberyCompleteShard(std::string title, std::string subtitle, std::string bottomLabel, int bottomValue)
		{
			Title = title;
			Subtitle = subtitle;
			BottomLabel = bottomLabel;
			BottomValue = bottomValue;
		}
	};
}