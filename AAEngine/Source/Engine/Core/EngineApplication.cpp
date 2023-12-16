#include "AA_PreCompiledHeaders.h"
#include "EngineApplication.h"
#include "EventSystem/Event.h"

#ifdef AA_RELEASE
#include "Tests/TesterFile.h"
#endif // AA_DEBUG

namespace AAEngine {

	CEngineApplication::CEngineApplication()
	{
		ApplicationWindow = TUniquePtr<IWindow>(IWindow::Create());
		ApplicationWindow->SetEventCallbackFunction(BIND_EVENT_FUNCTION(this, &CEngineApplication::HandleEvent));
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
#endif // AA_DEBUG


		while(bIsApplicationRunning) 
		{
			//ApplicationWindow->Tick();
		}
	}

	void CEngineApplication::HandleEvent(CEvent& Event)
	{
		// Event logs
		// AA_CORE_LOG(Info, Event.ToString().c_str());

		CEventHandler EventHandler(Event);
		EventHandler.HandleEvent<CWindowCloseEvent>(BIND_EVENT_FUNCTION(this, &CEngineApplication::OnWindowClose));

	}
	
	bool CEngineApplication::OnWindowClose(const CWindowCloseEvent& Event)
	{
		bIsApplicationRunning = false;
		return true;
	}
}
