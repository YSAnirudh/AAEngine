#pragma once

#ifdef AA_PLATFORM_WINDOWS
	/*
	* extern function that needs to be defined in Client Applications for Creating an Application
	*/
	extern AAEngine::CEngineApplication* AAEngine::CreateApplication();

	/*
	* ENTRY POINT
	* This is the main entry point for the Client Application into the Engine
	*/
	int main(int argc, char** argv)
	{
		AA_CORE_LOG(Trace, "Starting AAEngine...");
		auto AApplication = AAEngine::CreateApplication();
		AApplication->Run();
		delete AApplication;
	}
#else
	#error AA Engine only supports Windows!
#endif