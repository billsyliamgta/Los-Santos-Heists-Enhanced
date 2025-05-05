#pragma once

#include <string>
#include "script.h"

namespace UI::Scaleforms
{
	/// <summary>
	/// A class adding GTA Online Cash Hud to Single-Player.
	/// </summary>
	class CashHud
	{
	public:
       #pragma region Fields
	   
	   /// <summary>
	   /// The name of the GFX.
	   /// </summary>
	   std::string gfxName = "HUD_CASH";

	   /// <summary>
	   /// The hud component id used for the Cash Hud.
	   /// </summary>
	   const int HudComponent = 21;

	   int AddedCash;

	   int PreviousCash;

	   int AddedBank;

	   int PreviousBank;
	   
	   /// <summary>
	   /// The amount of Cash the player has.
	   /// </summary>
	   int Cash = 0;

	   /// <summary>
	   /// The amount of Cash the player has in their Bank.
	   /// </summary>
	   int Bank = 0;

       #pragma endregion

       #pragma region Stat Adjustment Methods

	   // CASH

	   inline void SetCash(int cash)
	   {
		   Cash = cash;
		   AddedCash = cash;
	   }

	   inline void AddCash(int cash)
	   {
		   Cash += cash;
		   AddedCash = cash;
	   }

	   inline void RemoveCash(int cash)
	   {
		   Cash -= cash;
		   AddedCash = cash;
	   }

	   // BANK

	   inline void SetBank(int cash)
	   {
		   Bank = cash;
		   AddedBank = cash;
	   }

	   inline void AddBank(int cash)
	   {
		   Bank += cash;
		   AddedBank = cash;
	   }

	   inline void RemoveBank(int cash)
	   {
		   Bank -= cash;
		   AddedBank = cash;
	   }

       #pragma endregion

       #pragma region Handling Methods

	   /// <summary>
	   /// Requests the Hud Scaleform Components.
	   /// </summary>
	   void Request();

	   /// <summary>
	   /// Disposes the Hud Scaleform Components if they're loaded.
	   /// </summary>
	   void Dispose();

	   void Control();

       #pragma endregion


	   
	};
}