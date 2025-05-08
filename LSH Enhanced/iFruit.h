#pragma once

#include "script.h"
#include <string>
#include "Extensions.h"


namespace UI::Scaleforms
{
	/// <summary>
	/// A class implementing Michael/GTA Online protagonist mobile phone (iFruit).
	/// </summary>
	class iFruit
	{
	public:
		enum eApps : int
		{
			Homepage = 1 | 3 | 5,
			Contacts = 2,
			Call = 4,
			TextsList = 6,
			Text = 7,
			EmailList = 8,
			Email = 9,
			Keypad = 11,
			Settings = 13 | 18 | 22,
			ListFor14 = 17,
			List = 19,
			JobList = 20 | 25,
			Trackify = 23,
			Coords = 24,
			BlackText = 26,
			SecuroServ = 27
		};

        #pragma region Fields

		/// <summary>
		/// The name of the iFruit Scaleform Movie.
		/// </summary>
		const std::string gfxName = "CELLPHONE_IFRUIT";

		/// <summary>
		/// SoundSet used for the audio of the iFruit phone. 
		/// </summary>
		const std::string AudioSoundSet = "Phone_SoundSet_Default";

        #pragma endregion

        #pragma region Scaleform Methods

		/// <summary>
		/// Loads the Scaleform Movie.
		/// </summary>
		void LoadScaleform();

        #pragma endregion
	};
}