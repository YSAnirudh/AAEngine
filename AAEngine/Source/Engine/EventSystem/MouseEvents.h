#pragma once

#include "Event.h"
#include "Core/MouseCodes.h"

namespace AAEngine {

	/*
	* MouseMovedEvent class to define an Event for when a Mouse is moved
	*/
	class AA_ENGINE_API CMouseMovedEvent : public CEvent
	{
	public:
		/*
		* Constructor that takes in the XPos and YPos for registering where the mouse is when moving
		*
		* @param XPos - X Position of the mouse
		* @param YPos - Y Position of the mouse
		*/
		CMouseMovedEvent(double XPos, double YPos)
			: XPos(XPos), YPos(YPos) {}

		/*
		* Getter function for the X Position for Mouse Moved Event
		*
		* @returns X Position for Mouse
		*/
		double GetXPos() const { return XPos; }
		/*
		* Getter function for the Y Position for Mouse Moved Event
		*
		* @returns Y Position for Mouse
		*/
		double GetYPos() const { return YPos; }

		/*
		* Overriden Virtual Function to return an std::string for the MouseMovedEvent
		* Useful for Logging Events
		*
		* @returns MouseMovedEvent represented as a String
		*/
		virtual std::string ToString() const override
		{
			std::stringstream SS;
			SS << "MouseMovedEvent: " << XPos << " (X Position) | " << YPos << " (Y Position)";
			return SS.str();
		}

		/*
		* MACRO for overriding Event Type based functions from Event
		*/
		EVENT_CLASS_TYPE(Mouse_MovedEvent)
		/*
		* MACRO for overriding Event Category based functions from Event
		*/
		EVENT_CLASS_CATEGORY(EventCategory_InputEvent | EventCategory_MouseEvent);

	private:
		/*
		* doubles to store X Position and Y Position of the Mouse
		*/
		double XPos, YPos;
	};

	/*
	* MouseScrollEvent class to define an Event for when a Mouse is scrolled
	*/
	class AA_ENGINE_API CMouseScrollEvent : public CEvent
	{
	public:
		/*
		* Constructor that takes in the XOffset and YOffset for tracking how much scrolling has happened
		*
		* @param XOffset - X Offset of the mouse scroll
		* @param YOffset - Y Offset of the mouse scroll
		*/
		CMouseScrollEvent(double XOffset, double YOffset)
			: XOffset(XOffset), YOffset(YOffset) {}

		/*
		* Getter function for the X Offset for Mouse Scroll Event
		*
		* @returns X Offset for Mouse Scroll
		*/
		double GetXOffset() const { return XOffset; }
		/*
		* Getter function for the Y Offset for Mouse Scroll Event
		*
		* @returns Y Offset for Mouse Scroll
		*/
		double GetYOffset() const { return YOffset; }

		/*
		* Overriden Virtual Function to return an std::string for the MouseMovedEvent
		* Useful for Logging Events
		*
		* @returns MouseMovedEvent represented as a String
		*/
		virtual std::string ToString() const override
		{
			std::stringstream SS;
			SS << "MouseScrollEvent: " << XOffset << " (X Scroll Offset) | " << YOffset << " (Y Scroll Offset)";
			return SS.str();
		}

		/*
		* MACRO for overriding Event Type based functions from Event
		*/
		EVENT_CLASS_TYPE(Mouse_ScrollEvent)
		/*
		* MACRO for overriding Event Category based functions from Event
		*/
		EVENT_CLASS_CATEGORY(EventCategory_InputEvent | EventCategory_MouseEvent);

	private:
		/*
		* doubles to store X Offset and Y Offset of the Mouse Scroll
		*/
		double XOffset, YOffset;
	};

	/*
	* MouseButtonEvent class to define an Event for when a Mouse Button is pressed/released
	* To be sub classed further for pressed and released
	*/
	class AA_ENGINE_API CMouseButtonEvent : public CEvent
	{
	public:
		/*
		* Getter function for the MouseCode associated with the MouseButtonEvent
		*
		* @returns MouseCode for the MouseButtonEvent
		*/
		EMouseCode GetMouseCode() const { return MouseCode; }

		/*
		* MACRO for overriding Event Category based functions from Event
		*/
		EVENT_CLASS_CATEGORY(EventCategory_InputEvent | EventCategory_MouseEvent)

	protected:
		/*
		* Protected Constructor (to avoid instancing this class) that takes in a MouseCode for registering which button has been pressed/released
		*
		* @param MouseCode - MouseCode associated with a MouseButton Press/Release
		*/
		CMouseButtonEvent(const EMouseCode MouseCode)
			: MouseCode(MouseCode) {}

		/*
		* MouseCode to store Mouse Code for the Mouse button that is pressed/released
		*/
		EMouseCode MouseCode;
	};

	/*
	* MouseButtonPressedEvent class to define an MouseButtonEvent for when a Mouse button is pressed
	*/
	class AA_ENGINE_API CMouseButtonPressedEvent : public CMouseButtonEvent
	{
	public:
		/*
		* Constructor that takes in a MouseCode for registering which button has been pressed
		*
		* @param MouseCode - MouseCode associated with a MouseButton Press
		*/
		CMouseButtonPressedEvent(const EMouseCode MouseCode)
			: CMouseButtonEvent(MouseCode) {}

		/*
		* Overriden Virtual Function to return an std::string for the MouseButtonPressedEvent
		* Useful for Logging Events
		*
		* @returns MouseButtonPressedEvent represented as a String
		*/
		virtual std::string ToString() const override
		{
			std::stringstream SS;
			SS << "MouseButtonPressedEvent: " << MouseCode;
			return SS.str();
		}

		/*
		* MACRO for overriding Event Type based functions from Event
		*/
		EVENT_CLASS_TYPE(Mouse_ButtonPressedEvent)

	private:
	};

	/*
	* MouseButtonReleasedEvent class to define an Event for when a Mouse button is released
	*/
	class AA_ENGINE_API CMouseButtonReleasedEvent : public CMouseButtonEvent
	{
	public:
		/*
		* Constructor that takes in a MouseCode for registering which button has been released
		*
		* @param MouseCode - MouseCode associated with a MouseButton Release
		*/
		CMouseButtonReleasedEvent(const EMouseCode MouseCode)
			: CMouseButtonEvent(MouseCode) {}

		/*
		* Overriden Virtual Function to return an std::string for the MouseButtonReleasedEvent
		* Useful for Logging Events
		*
		* @returns MouseButtonReleasedEvent represented as a String
		*/
		virtual std::string ToString() const override
		{
			std::stringstream SS;
			SS << "MouseButtonReleasedEvent: " << MouseCode;
			return SS.str();
		}

		/*
		* MACRO for overriding Event Type based functions from Event
		*/
		EVENT_CLASS_TYPE(Mouse_ButtonReleasedEvent)

	private:
	};

}