#pragma once

#include "Input/Input.h"

namespace AAEngine {

	class CWindowsInput : public CInput
	{
	protected:
		/*
		* Implementation function
		* IMPLEMENTED for Windows Platform
		* Virtual function to check whether a key is being pressed
		*
		* @param KeyCode - KeyCode of the key that we are checking
		*
		* @return bool - True if the key is being pressed, false otherwise.
		*/
		virtual bool IsKeyPressed_Implementation(EKeyCode KeyCode) override;

		/*
		* Implementation function
		* IMPLEMENTED for Windows Platform
		* Virtual function to check whether a mouse button is being pressed
		*
		* @param MouseCode - MouseCode of the mouse button that we are checking
		*
		* @return bool - True if the mouse button is being pressed, false otherwise.
		*/
		virtual bool IsMouseButtonPressed_Implementation(EMouseCode MouseCode) override;
		/*
		* Implementation function
		* IMPLEMENTED for Windows Platform
		* Virtual function to get the X position of the mouse
		*
		* @return float - The X Position of the Mouse.
		*/
		virtual float GetMouseX_Implementation() const override;
		/*
		* Implementation function
		* IMPLEMENTED for Windows Platform
		* Virtual function to get the Y position of the mouse
		*
		* @return float - The Y Position of the Mouse.
		*/
		virtual float GetMouseY_Implementation() const override;
	};
}