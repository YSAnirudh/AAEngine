#pragma once

#include "Event.h"

namespace AAEngine {

	/*
	* WindowResizeEvent class to define an Event for when a Window is resized
	*/
	class AA_ENGINE_API CWindowResizeEvent : public CEvent
	{
	public:
		/*
		* Constructor that takes in the NewWindowWidth and NewWindowHeight
		* 
		* @param NewWindowWidth - New Window Width after resize
		* @param NewWindowHeight - New Window Height after resize
		*/
		CWindowResizeEvent(int NewWindowWidth, int NewWindowHeight):
			WindowWidth(NewWindowWidth), WindowHeight(NewWindowHeight) {}

		/*
		* Getter function for the Window Width for the Resize Event
		*
		* @returns Window Width of the Resize Event
		*/
		inline unsigned int GetWindowWidth() const { return WindowWidth; }
		/*
		* Getter function for the Window Height for the Resize Event
		*
		* @returns Window Height of the Resize Event
		*/
		inline unsigned int GetWindowHeight() const { return WindowHeight; }

		/*
		* Overriden Virtual Function to return an std::string for the WindowResizeEvent
		* Useful for Logging Events
		*
		* @returns WindowResizeEvent represented as a String
		*/
		virtual std::string ToString() const override
		{
			std::stringstream SS;
			SS << "WindowResizeEvent: " << WindowWidth << "(Width) | " << WindowHeight << "(Height) called";
			return SS.str();
		}

		/*
		* MACRO for overriding Event Type based functions from Event
		*/
		EVENT_CLASS_TYPE(Window_ResizeEvent)
		/*
		* MACRO for overriding Event Category based functions from Event
		*/
		EVENT_CLASS_CATEGORY(EventCategory_ApplicationEvent)
	private:
		/*
		* Unsigned integers to store Window Width and Height
		*/
		unsigned int WindowWidth, WindowHeight;
	};

	/*
	* WindowMovedEvent class to define an Event for when a Window is moved
	*/
	class AA_ENGINE_API CWindowMovedEvent : public CEvent
	{
	public:
		/*
		* Constructor that takes in the XPos and YPos
		*
		* @param XPos - New X Position after move
		* @param YPos - New Y Position after move
		*/
		CWindowMovedEvent(int XPos, int YPos) :
			XPos(XPos), YPos(YPos) {}

		/*
		* Getter function for the Window X Position for the Moved Event
		*
		* @returns Window X Position of the Moved Event
		*/
		inline unsigned int GetWindowXPosition() const { return XPos; }
		/*
		* Getter function for the Window Y Position for the Moved Event
		*
		* @returns Window Y Position of the Moved Event
		*/
		inline unsigned int GetWindowYPosition() const { return YPos; }

		/*
		* Overriden Virtual Function to return an std::string for the WindowMovedEvent
		* Useful for Logging Events
		*
		* @returns WindowMovedEvent represented as a String
		*/
		virtual std::string ToString() const override
		{
			std::stringstream SS;
			SS << "WindowMovedEvent: " << XPos << "(X Position) | " << YPos << "(Y Position) called";
			return SS.str();
		}

		/*
		* MACRO for overriding Event Type based functions from Event
		*/
		EVENT_CLASS_TYPE(Window_MovedEvent)
		/*
		* MACRO for overriding Event Category based functions from Event
		*/
		EVENT_CLASS_CATEGORY(EventCategory_ApplicationEvent)
	private:
		/*
		* Unsigned integers to store Window X and Y Position
		*/
		int XPos, YPos;
	};

	/*
	* WindowCloseEvent class to define an Event for when a Window is closed
	*/
	class AA_ENGINE_API CWindowCloseEvent : public CEvent
	{
	public:
		/*
		* Default Constructor for the WindowCloseEvent class
		*/
		CWindowCloseEvent() = default;

		/*
		* Overriden Virtual Function to return an std::string for the WindowCloseEvent
		* Useful for Logging Events
		*
		* @returns WindowCloseEvent represented as a String
		*/
		virtual std::string ToString() const override
		{
			std::stringstream SS;
			SS << "WindowCloseEvent called";
			return SS.str();
		}

		/*
		* MACRO for overriding Event Type based functions from Event
		*/
		EVENT_CLASS_TYPE(Window_CloseEvent)
		/*
		* MACRO for overriding Event Category based functions from Event
		*/
		EVENT_CLASS_CATEGORY(EventCategory_ApplicationEvent)
	private:
	};

	/*
	* WindowFocusEvent class to define an Event for when a Window is focused
	*/
	class AA_ENGINE_API CWindowFocusEvent : public CEvent
	{
	public:
		/*
		* Default Constructor for the WindowFocusEvent class
		*/
		CWindowFocusEvent() = default;

		/*
		* Overriden Virtual Function to return an std::string for the WindowFocusEvent
		* Useful for Logging Events
		*
		* @returns WindowFocusEvent represented as a String
		*/
		virtual std::string ToString() const override
		{
			std::stringstream SS;
			SS << "WindowFocusEvent called";
			return SS.str();
		}

		/*
		* MACRO for overriding Event Type based functions from Event
		*/
		EVENT_CLASS_TYPE(Window_FocusedEvent)
		/*
		* MACRO for overriding Event Category based functions from Event
		*/
		EVENT_CLASS_CATEGORY(EventCategory_ApplicationEvent)
	private:
	};

	/*
	* WindowLostFocusEvent class to define an Event for when a Window loses focus
	*/
	class AA_ENGINE_API CWindowLostFocusEvent : public CEvent
	{
	public:
		/*
		* Default Constructor for the WindowLostFocusEvent class
		*/
		CWindowLostFocusEvent() = default;

		/*
		* Overriden Virtual Function to return an std::string for the WindowLostFocusEvent
		* Useful for Logging Events
		*
		* @returns WindowLostFocusEvent represented as a String
		*/
		virtual std::string ToString() const override
		{
			std::stringstream SS;
			SS << "WindowLostFocusEvent called";
			return SS.str();
		}

		/*
		* MACRO for overriding Event Type based functions from Event
		*/
		EVENT_CLASS_TYPE(Window_LostFocusEvent)
		/*
		* MACRO for overriding Event Category based functions from Event
		*/
		EVENT_CLASS_CATEGORY(EventCategory_ApplicationEvent)
	private:
	};

}