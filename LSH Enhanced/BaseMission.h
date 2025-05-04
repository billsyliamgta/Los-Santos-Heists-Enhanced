#pragma once

namespace Missions
{
	class BaseMission
	{
	public:
		int Index = 0;

		virtual void Update();

		virtual void UpdateStats();

		virtual void Init();

		virtual void Dispose();

		unsigned int joaat(char* string);
	};
}