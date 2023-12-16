#pragma once
#include "Core.h"
#include "Engine/Core/Memory/CoreMemory.h"
#include "Engine/EventSystem/Event.h"
#include "Engine/EventSystem/ApplicationEvents.h"
#include "Engine/Window/Window.h"

// FORWARD DECLARATIONS

namespace AAEngine {

	/*
	* Engine Application class that defines an Application class for the Client to Sub class for projects using the AAEngine
	*/
	class AA_ENGINE_API CEngineApplication
	{
	public:
		/*
		* No-Arg constructor
		*/
		CEngineApplication();
		/*
		* Virtual Destructor as this class will be subclassed
		*/
		virtual ~CEngineApplication();

		/*
		* Run Method for the Engine Game Loop
		*/
		void Run();

		/*
		* HandleEvent Method used to handle any event that comes into this application, that needs to be handled by the application
		* 
		* @param Event - Event& of the Event that needs to be handled
		*/
		void HandleEvent(CEvent& Event);
	private:
		// EVENT Handling functions
		/*
		* 
		*/
		bool OnWindowClose(const CWindowCloseEvent& Event);

		/*
		* Pointer to the Window for our Application.
		*/
		TUniquePtr<IWindow> ApplicationWindow = nullptr;
		/*
		* boolean to check if the Application is still running.
		*/
		bool bIsApplicationRunning = true;
	};

	// To be defined on the CLIENT of AAEngine
	CEngineApplication* CreateApplication();
}

