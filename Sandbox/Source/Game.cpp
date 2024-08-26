#include "Game.h"
#include "AAEngine.h"

class SandboxLayer : public AAEngine::CLayer
{
public:
	SandboxLayer()
		: CLayer("Example")
	{

	}

	virtual void OnUpdate(float DeltaSeconds) override
	{
		//AA_LOG(Info, "App Update");
	}

	virtual void OnEvent(AAEngine::CEvent& Event) override
	{
		// AA_LOG(Info, "Event: %s", Event.ToString().c_str());
	}
};

class Sandbox : public AAEngine::CEngineApplication
{
public:
	Sandbox()
	{
		PushLayer(new SandboxLayer());
	}

	~Sandbox()
	{

	}

};

AAEngine::CEngineApplication* AAEngine::CreateApplication()
{
	return new Sandbox();
}
