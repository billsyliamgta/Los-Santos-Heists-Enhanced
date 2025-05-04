#pragma once

#include <string>
#include <cmath>

namespace UI::Scaleforms
{
	/// <summary>
	/// A class adding the GTA Online Rank Bar into Single-Player.
	/// </summary>
	class RankBar
	{
	public:
		/// <summary>
		/// The name of the GFX.
		/// </summary>
		std::string gfxName = "MP_RANK_BAR";

		/// <summary>
		/// The id of the Hud Component.
		/// </summary>
		const int BarId = 19;

		/// <summary>
		/// This is the value that the CurrentXP will start at after moving to the next rank.
		/// </summary>
		int XPStartLimit = 0;
        
		/// <summary>
		/// This is the value that when the CurrentXP hits it, the next rank will unlock.
		/// </summary>
		int XPEndLimit = 1000;

		int PreviousXP = 0;

		/// <summary>
		/// The player's current XP.
		/// </summary>
		int CurrentXP = 0;

		/// <summary>
		/// The player's rank. By default this is 1.
		/// </summary>
		int PlayerLevel = 1;

		/// <summary>
		/// Calculates the rank value to an xp value.
		/// </summary>
		/// <param name="rank"></param>
		/// <returns></returns>
		inline int CalculateXP(int rank)
		{
			return (1000 + (rank - 1) * 125) * rank;
		}

		inline float CurrentExpLvl(float exp)
		{
			float multi = 0.002f; // Changing this number will result in a higher or lower scale.
			float level = (float)(multi * std::sqrt(multi));
			return level;
		}
	};
}