#pragma once

#include "script.h"
#include <string>
#include "Extensions.h"
#include <stdexcept>
#include <vector>

namespace UI::Scaleforms
{
	/// <summary>
	/// A class implementing Michael/GTA Online protagonist mobile phone (iFruit).
	/// </summary>
	class iFruit
	{
	public:
        #pragma region Fields

		inline static bool IsMobilePhoneOpen;

		inline static Vector3 Var0;
		
		inline static float fVar3;
		
		inline static float fVar4;
		
		inline static float fVar5;

		inline static int iLocal_16;

		inline static Vector3 Global_20994;

		inline static Vector3 Global_20997;

		/// <summary>
		/// The name of the iFruit Scaleform Movie.
		/// </summary>
		inline static std::string gfxName = "CELLPHONE_IFRUIT";

		/// <summary>
		/// The Scaleform Movie handle.
		/// </summary>
		inline static int ScaleformMovieHandle;

		/// <summary>
		/// The iFruit's render target used for 3d rendering onto the phone prop.
		/// </summary>
		inline static int MobilePhoneRT;

		/// <summary>
		/// SoundSet used for the audio of the iFruit phone. 
		/// </summary>
		const std::string AudioSoundSet = "Phone_SoundSet_Default";

        #pragma endregion

        #pragma region Scaleform Methods

		/// <summary>
		/// Loads the Scaleform Movie.
		/// </summary>
		static void LoadScaleform();

		/// <summary>
		/// Draws the Scaleform Movie.
		/// </summary>
		static void Draw();

		static void MovePhone(bool up);

		static void Control();

		static void Dispose();

        #pragma endregion
	};
}