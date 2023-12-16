#pragma once

#include "Engine/Core/Core.h"
#include "Engine/EventSystem/Event.h"

namespace AAEngine {

	/*
	* Struct to store Properties of a Window
	* 
	* WindowTitle - Title for a Window (Name)
	* WindowWidth - Width of a Window
	* WindowHeight - Height of a Window
	*/
	struct FWindowProps
	{
		std::string WindowTitle;
		unsigned int WindowWidth, WindowHeight;

		/*
		* Constructor with Title, Width and Height as arguments with default values
		*/
		FWindowProps(const std::string& WindowTitle= "AA Engine", unsigned int WindowWidth = 1280, unsigned int WindowHeight = 720)
			: WindowTitle(WindowTitle), WindowWidth(WindowWidth), WindowHeight(WindowHeight)
		{}
	};

	/*
	* A Platform Independent Window class interface to be implemented per platform and Initialized in the AAEngine
	*/
	class AA_ENGINE_API IWindow
	{
	public:
		/*
		* using define for EventCallbackFunction for this Window class
		*/
		using EventCallbackFunction = std::function<void(CEvent&)>;

		/*
		* Virtual Destructor as this needs to be subclassed
		*/
		virtual ~IWindow() {}

		/*
		* Pure Virtual Tick function for calling Update Events every frame on this Window
		*/
		virtual void Tick() = 0;

		/*
		* Pure Virtual Getter for this Window's Width
		* 
		* @returns Window's Width
		*/
		virtual unsigned int GetWindowWidth() const = 0;
		/*
		* Pure Virtual Getter for this Window's Height
		* 
		* @returns Window's Height
		*/
		virtual unsigned int GetWindowHeight() const = 0;

		/*
		* Pure Virtual Setter for this Window's Event Callback Function to handle Window Events
		* 
		* @param EventCallbackFunction's const ref
		*/
		virtual void SetEventCallbackFunction(const EventCallbackFunction& Callback) = 0;
		/*
		* Pure Virtual Setter to set this Window's VSync to true or false 
		* 
		* @param bEnabled boolean that sets the VSync to true or false
		*/
		virtual void SetVSync(bool bEnabled) = 0;
		/*
		* Pure Virtual Getter to see if VSync is Enabled or not
		* 
		* @returns true if VSync is Enabled, false if Disabled
		*/
		virtual bool IsVSync() const = 0;
		
		/*
		* Pure Virtual Create method to be implemented per platform
		* Used for the Creation of a Window
		*
		* @param WindowProps used to set WindowTitle, WindowWidth, and WindowHeight
		*/
		static IWindow* Create(const FWindowProps& WindowData = FWindowProps());
	private:
	};

}