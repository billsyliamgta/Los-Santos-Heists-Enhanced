#pragma once

#include "Extensions.h"
#include <string>

namespace UI
{
	class Screen
	{
	public:
        #pragma region  Fading

		/// <summary>
		/// Returns a boolean indicating if the screen is currently fading out.
		/// </summary>
		/// <returns></returns>
		static bool IsFadingOut();

		/// <summary>
		/// Returns a boolean indicating if the screen is completely faded out.
		/// </summary>
		/// <returns></returns>
		static bool IsFadedOut();

		/// <summary>
		/// Returns a boolean indicating if the screen is currently fading in.
		/// </summary>
		/// <returns></returns>
		static bool IsFadingIn();

		/// <summary>
		/// Returns a boolean indicating if the screen is completely faded in.
		/// </summary>
		/// <returns></returns>
		static bool IsFadedIn();

		/// <summary>
		/// Fades out the whole screen black. Useful for transitions.
		/// </summary>
		/// <param name="time">How long it takes to fade out (this value is in milliseconds so 1000 would be a second).</param>
		static void DoFadeOut(int time);


		/// <summary>
		/// Fades in the whole screen if its already faded out.
		/// </summary>
		/// <param name="time">How long it takes to fade in (this value is in milliseconds so 1000 would be a second).</param>
		static void DoFadeIn(int time);

        #pragma endregion

        #pragma region Effects

		/// <summary>
		/// Load's the specifed timecycle modifier e.g. 'TransformRaceFlash`
		/// </summary>
		/// <param name="modiferName"></param>
		static void SetTimecycleModifer(std::string modiferName);

		/// <summary>
		/// Set's the strength of the current timecycle modifier.
		/// </summary>
		/// <param name="strength">Float value between 0.0 - 1.0</param>
		static void SetTimecycleModiferStrength(float strength);
		
		/// <summary>
		/// According to NativeDB its the same as SetTimecycleModifier except its for the secondary timecycle modifier.
		/// </summary>
		/// <param name="strength">Float value between 0.0 - 1.0</param>
		static void EnableMoonCycleOverride(float strength);

		/// <summary>
		/// Clear's the active timecycle modifier.
		/// </summary>
		static void ClearTimecycleModifer();

        #pragma endregion

        #pragma region Text

		/// <summary>
		/// Returns a value indicating if help text is currently being displayed on screen.
		/// </summary>
		/// <returns></returns>
		static bool IsHelpTextBeingDisplayed();

		static void ShowSubtitle(char* text, int duration = 2500);

		static int ShowNotification(char* text, bool blink = false);

		static void ShowHelpTextThisFrame(std::string helpText, bool beep);
		
		static void ShowHelpText(std::string helpText, int duration = -1, bool beep = true, bool looped = false);

		/// <summary>
		/// Clears a help message immediately.
		/// </summary>
		static void ClearHelpText();

		static void SendTextNotification(std::string avatar, std::string author, std::string title, std::string message);

        #pragma endregion
 
        #pragma region Minimap

		static bool IsHudHidden();

		static bool IsRadarHidden();

		static bool IsMinimapRendering();

		static void DisplayHud(bool toggle);

		static void DisplayRadar(bool toggle);

        #pragma endregion

        #pragma region Fields

		/// <summary>
		/// The base width of the screen used for pretty much all UI calculations e.g. TimerBars.
		/// </summary>
		static const float Width;

		/// <summary>
		/// The base height of the screen used for pretty much all UI calculations e.g TimerBars.
		/// </summary>
		static const float Height;

		static float AspectRatio();

		/// <summary>
		/// Gets the 720 pixel height base against the aspect ratio.
		/// </summary>
		/// <returns></returns>
		static float ScaledWidth();

		static Extensions::Size Resolution();

        #pragma endregion
	};
}