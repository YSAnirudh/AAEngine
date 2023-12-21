#pragma once

#include "Core/Core.h"

#include "KeyCodes.h"
#include "MouseCodes.h"

namespace AAEngine {

	class AA_ENGINE_API CInput
	{
	public:
		/*
		* Static function to check whether a key is being pressed
		*
		* @param KeyCode - KeyCode of the key that we are checking
		*
		* @return bool - True if the key is being pressed, false otherwise.
		*/
		static bool IsKeyPressed(EKeyCode KeyCode)
		{
			AA_CORE_ASSERT(InputInstance, "Input Instance is Null! Check initialization in Platform specific Input.");

			return InputInstance->IsKeyPressed_Implementation(KeyCode);
		}

		/*
		* Static function to check whether a mouse button is being pressed
		*
		* @param MouseCode - MouseCode of the mouse button that we are checking
		*
		* @return bool - True if the mouse button is being pressed, false otherwise.
		*/
		static bool IsMouseButtonPressed(EMouseCode MouseCode)
		{
			AA_CORE_ASSERT(InputInstance, "Input Instance is Null! Check initialization in Platform specific Input.");

			return InputInstance->IsMouseButtonPressed_Implementation(MouseCode);
		}

		/*
		* Static function to get the X position of the mouse
		*
		* @return float - The X Position of the Mouse.
		*/
		static float GetMouseX()
		{
			AA_CORE_ASSERT(InputInstance, "Input Instance is Null! Check initialization in Platform specific Input.");

			return InputInstance->GetMouseX_Implementation();
		}
		/*
		* Static function to get the Y position of the mouse
		*
		* @return float - The Y Position of the Mouse.
		*/
		static float GetMouseY()
		{
			AA_CORE_ASSERT(InputInstance, "Input Instance is Null! Check initialization in Platform specific Input.");

			return InputInstance->GetMouseY_Implementation();
		}

	protected:
		/*
		* Implementation function
		* Implemented in Platform Specific Input
		* Pure virtual function to check whether a key is being pressed
		*
		* @param KeyCode - KeyCode of the key that we are checking
		*
		* @return bool - True if the key is being pressed, false otherwise.
		*/
		virtual bool IsKeyPressed_Implementation(EKeyCode KeyCode) = 0;

		/*
		* Implementation function
		* Implemented in Platform Specific Input
		* Pure virtual function to check whether a mouse button is being pressed
		*
		* @param MouseCode - MouseCode of the mouse button that we are checking
		*
		* @return bool - True if the mouse button is being pressed, false otherwise.
		*/
		virtual bool IsMouseButtonPressed_Implementation(EKeyCode MouseCode) = 0;
		/*
		* Implementation function
		* Implemented in Platform Specific Input
		* Pure virtual function to get the X position of the mouse
		*
		* @return float - The X Position of the Mouse.
		*/
		virtual float GetMouseX_Implementation() const = 0;
		/*
		* Implementation function
		* Implemented in Platform Specific Input
		* Pure virtual function to get the Y position of the mouse
		*
		* @return float - The Y Position of the Mouse.
		*/
		virtual float GetMouseY_Implementation() const = 0;

		/*
		* Static Singleton instance of the Input class
		*/
		static CInput* InputInstance;
	};
}