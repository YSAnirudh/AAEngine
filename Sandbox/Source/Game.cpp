#include "Game.h"
#include "AAEngine.h"

class Sandbox : public AAEngine::CEngineApplication
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

};

AAEngine::CEngineApplication* AAEngine::CreateApplication()
{
	return new Sandbox();
}
