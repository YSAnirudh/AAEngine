#pragma once
#include "Core.h"
#include "Engine/Core/Memory/CoreMemory.h"
#include "Engine/EventSystem/Event.h"
#include "Engine/EventSystem/ApplicationEvents.h"
#include "Engine/Window/Window.h"
#include "Engine/LayerSystem/LayerStack.h"

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

		/*
		* PushLayer Method used to Push new Layers onto the Layer Stack.
		*
		* @param Layer - Layer* of the layer to push onto the Layer Stack
		*/
		void PushLayer(CLayer* Layer);
		/*
		* PushOverlay Method used to Push new Overlays onto the Layer Stack.
		*
		* @param Overlay - Layer* of the overlay to push onto the Layer Stack
		*/
		void PushOverlay(CLayer* Overlay);

		/*
		* Inline Getter function to return a reference to the Application Window
		* 
		* @returns Reference to the Application Window
		*/
		FORCEINLINE IWindow& GetWindow() { return *ApplicationWindow; }

		/*
		* Inline Static Getter function to return a static reference to the Application
		*
		* @returns Reference to the Application
		*/
		FORCEINLINE static CEngineApplication& Get() { return *EngineApplicationInstance; }
	protected:
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

		/*
		* Layer Stack for the application to handle Layers
		*/
		CLayerStack LayerStack;

	private:
		/*
		* Static Singleton instance of the Application.
		* Only one application possible.
		*/
		static CEngineApplication* EngineApplicationInstance;
	};

	// To be defined on the CLIENT of AAEngine
	CEngineApplication* CreateApplication();
}

