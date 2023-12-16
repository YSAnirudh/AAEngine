#pragma once

#include "Core/Core.h"
#include "Window/Window.h"

// FORWARD DECLARATIONS
struct GLFWwindow;

namespace AAEngine {

	/*
	* Windows-platform specific Window implementation
	*/
	class AA_ENGINE_API CWindowsWindow : public IWindow
	{
	public:
		/*
		* Constructor with WindowProps as default parameter
		* 
		* @param WindowProps - WindowProps for initializing Title, Width and Height of the Window
		*/
		CWindowsWindow(const FWindowProps& WindowProps = FWindowProps());
		
		/*
		* Virtual Destructor
		*/
		virtual ~CWindowsWindow();

		/*
		* Overriden Virtual Tick function for calling Update Events every frame on this Window
		*/
		virtual void Tick() override;

		/*
		* Overriden Virtual Getter Function to get the Window Width
		*
		* @returns Window Width of the Window
		*/
		virtual unsigned int GetWindowWidth() const override { return WindowData.WindowWidth; }
		/*
		* Overriden Virtual Getter Function to get the Window Height
		*
		* @returns Window Height of the Window
		*/
		virtual unsigned int GetWindowHeight() const override { return WindowData.WindowHeight; }

		/*
		* Overriden Virtual Function to set the Event Callback Function for this Window
		*
		* @param EventCallback - const EventCallbackFunction& event callback function used to handle callbacks set for this window
		*/
		virtual void SetEventCallbackFunction(const EventCallbackFunction& EventCallback) override { WindowData.EventCallback = EventCallback; }

		/*
		* Overriden Virtual Function to set if the VSync for this window is enabled
		*
		* @param bIsEnabled - boolean that sets the VSync to true or false
		*/
		virtual void SetVSync(bool bEnabled) override;
		/*
		* Overriden Virtual Getter to see if VSync is Enabled or not
		*
		* @returns true if VSync is Enabled, false if Disabled
		*/
		virtual bool IsVSync() const override;

		/*
		* Virtual Initialize function to initialize Window Data using WindowProps
		*/
		virtual void Initialize(const FWindowProps& WindowProps);
		/*
		* Virtual Shutdown function to shutdown and clean up after the Window.
		*/
		virtual void Shutdown();
		/*
		* Virtual function to set callbacks for GLFW events
		*/
		virtual void SetGLFWEventCallbacks();
	private:
		/*
		* GLFWwindow pointer
		*/
		GLFWwindow* Window = nullptr;

		/*
		* private struct to store the current Window Data
		*/
		struct FWindowData
		{
			std::string WindowTitle;
			unsigned int WindowWidth, WindowHeight;
			EventCallbackFunction EventCallback;
			bool VSync;
		};

		/*
		* FWindowData variable for storing window data
		*/
		FWindowData WindowData;
	};

}