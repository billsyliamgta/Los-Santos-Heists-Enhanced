#pragma once

#include <string>
#include <cmath>
#include "script.h"

namespace UI::Scaleforms
{
	/// <summary>
	/// A class adding the GTA Online Rank Bar into Single-Player.
	/// </summary>
	class RankBar
	{
	public:
        #pragma region Fields

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

        #pragma endregion

		/// <summary>
		/// Set's the color of the Rank Bar.
		/// </summary>
		/// <param name="primaryColor"></param>
		/// <param name="secondaryColor"></param>
		void SetColor(int primaryColor, int secondaryColor);

		/// <summary>
		/// Prompts the Rank Bar to stay on screen.
		/// </summary>
		void StayOnScreen();

		/// <summary>
		/// Reset's the Rank Bar's movie.
		/// </summary>
		void ResetMovie();

		inline void BeforeDraw()
		{
			SetRankScores(XPStartLimit, XPEndLimit, PreviousXP, CurrentXP, PlayerLevel, PlayerLevel + 1);
		}

		void SetRankScores(int xpStartLimit, int xpEndLimit, int previousXP, int currentXP, int playerLevel, int rankNext);

		void SetOverrideParams(int speed, int duration);

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

		void Control();
	};
}