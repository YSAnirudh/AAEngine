#include "AA_PreCompiledHeaders.h"
#include "EngineApplication.h"
#include "EventSystem/Event.h"
#include "Input/Input.h"

#ifdef AA_RELEASE
#include "Tests/TesterFile.h"
#elif AA_DEBUG
#include "Tests/TesterFile.h"
#endif // AA_DEBUG

// Temp
#include <glad/glad.h>

namespace AAEngine {

	CEngineApplication* CEngineApplication::EngineApplicationInstance = nullptr;

	CEngineApplication::CEngineApplication()
	{
		AA_CORE_ASSERT(!EngineApplicationInstance, "Instance Already Present! Invalid Static ref.");
		EngineApplicationInstance = this;

		ApplicationWindow = TUniquePtr<IWindow>(IWindow::Create());
		ApplicationWindow->SetEventCallbackFunction(BIND_EVENT_FUNCTION(this, &CEngineApplication::HandleEvent));

		ImGuiLayer = new CImGuiLayer();
		PushOverlay(ImGuiLayer);
	}

	CEngineApplication::~CEngineApplication()
	{
	}

	void CEngineApplication::Run()
	{
		/*
		* Useful for Running Tests on Custom Libraries
		*/
#ifdef AA_RELEASE
		CTester::RunTester();
#elif AA_DEBUG
		CTester::RunTester();
#endif


		while(bIsApplicationRunning) 
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (CLayer* Layer : LayerStack)
			{
				Layer->OnUpdate();
			}

			ImGuiLayer->Begin();
			for (CLayer* Layer : LayerStack)
			{
				Layer->OnImGuiRender();
			}
			ImGuiLayer->End();

			ApplicationWindow->Tick();
		}
	}

	void CEngineApplication::HandleEvent(CEvent& Event)
	{
		// Event logs
		// AA_CORE_LOG(Info, Event.ToString().c_str());

		CEventHandler EventHandler(Event);
		EventHandler.HandleEvent<CWindowCloseEvent>(BIND_EVENT_FUNCTION(this, &CEngineApplication::OnWindowClose));

		for (auto It = LayerStack.end(); It != LayerStack.begin(); )
		{
			(*--It)->OnEvent(Event);
			if (Event.IsHandled())
			{
				break;
			}
		}
	}

	void CEngineApplication::PushLayer(CLayer* Layer)
	{
		LayerStack.PushLayer(Layer);
	}

	void CEngineApplication::PushOverlay(CLayer* Overlay)
	{
		LayerStack.PushOverlay(Overlay);
	}
	
	bool CEngineApplication::OnWindowClose(const CWindowCloseEvent& Event)
	{
		bIsApplicationRunning = false;
		return true;
	}
}
