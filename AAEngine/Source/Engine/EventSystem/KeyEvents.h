#pragma once

#include "Event.h"
#include "Core/KeyCodes.h"

namespace AAEngine {
	/*
	* KeyEvent class to define an Event for when a Key is pressed/released
	*/
	class AA_ENGINE_API CKeyEvent : public CEvent
	{
	public:
		/*
		* Getter function for the KeyCode associated with the KeyEvent
		*
		* @returns KeyCode for the Key
		*/
		EKeyCode GetKeyCode() const { return KeyCode; }

		/*
		* MACRO for overriding Event Category based functions from Event
		*/
		EVENT_CLASS_CATEGORY(EventCategory_InputEvent | EventCategory_KeyboardEvent)

	protected:
		/*
		* Protected Constructor (to avoid instancing this class) that takes in a KeyCode for the Key that is pressed/released
		*
		* @param XPos - X Position of the mouse
		* @param YPos - Y Position of the mouse
		*/
		CKeyEvent(const EKeyCode KeyCode)
			: KeyCode(KeyCode) {}

		/*
		* KeyCode to store Key Code for the Key that is pressed/released
		*/
		EKeyCode KeyCode;
	};

	/*
	* KeyPressedEvent class to define an KeyEvent for when a Key is pressed
	*/
	class AA_ENGINE_API CKeyPressedEvent : public CKeyEvent
	{
	public:
		/*
		* Constructor that takes in a KeyCode for registering which key has been pressed
		* Also, initialized the bIsRepeat to false
		*
		* @param KeyCode - KeyCode associated with a Key Press
		* @param bIsRepeat - bool for Whether this Event is a Key Repeat Event
		*/
		CKeyPressedEvent(const EKeyCode KeyCode, bool bIsRepeat)
			: CKeyEvent(KeyCode), bIsRepeat(bIsRepeat) {}

		/*
		* Getter function for Whether this Event is a Key Repeat Event
		*
		* @returns bIsRepeat - true if this Event is a Key Repeat Event, false otherwise
		*/
		bool IsRepeating() const { return bIsRepeat; }

		/*
		* Overriden Virtual Function to return an std::string for the KeyPressedEvent
		* Useful for Logging Events
		*
		* @returns KeyPressedEvent represented as a String
		*/
		virtual std::string ToString() const override
		{
			std::stringstream SS;
			SS << "KeyPressedEvent: " << KeyCode << (bIsRepeat ? " (REPEAT)" : "");
			return SS.str();
		}

		/*
		* MACRO for overriding Event Type based functions from Event
		*/
		EVENT_CLASS_TYPE(Keyboard_KeyPressedEvent)

	protected:
		/*
		* bool to store whether the Key Press is a repeating one or not.
		* Press ... Pause ... Repeat.Repeat.Repeat...
		*/
		bool bIsRepeat;
	};

	/*
	* KeyReleasedEvent class to define an KeyEvent for when a Key is released
	*/
	class AA_ENGINE_API CKeyReleasedEvent : public CKeyEvent
	{
	public:
		/*
		* Constructor that takes in a KeyCode for registering which key has been released
		*
		* @param KeyCode - KeyCode associated with a Key Release
		*/
		CKeyReleasedEvent(const EKeyCode KeyCode)
			: CKeyEvent(KeyCode) {}

		/*
		* Overriden Virtual Function to return an std::string for the KeyReleasedEvent
		* Useful for Logging Events
		*
		* @returns KeyReleasedEvent represented as a String
		*/
		virtual std::string ToString() const override
		{
			std::stringstream SS;
			SS << "KeyReleasedEvent: " << KeyCode;
			return SS.str();
		}

		/*
		* MACRO for overriding Event Type based functions from Event
		*/
		EVENT_CLASS_TYPE(Keyboard_KeyReleasedEvent)

	private:
	};

}