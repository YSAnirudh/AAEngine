#pragma once
#define _CRTDBG_MAP_ALLOC

#ifdef AA_PLATFORM_WINDOWS
	/*
	* extern function that needs to be defined in Client Applications for Creating an Application
	*/
	extern AAEngine::CEngineApplication* AAEngine::CreateApplication();

	void* operator new(size_t sz)
	{
		if (sz == 0)
			++sz; // avoid std::malloc(0) which may return nullptr on success

		if (void* ptr = std::malloc(sz))
			return ptr;

		throw std::bad_alloc{};
	}
	/*
	* ENTRY POINT
	* This is the main entry point for the Client Application into the Engine
	*/
	int main(int argc, char** argv)
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		AA_CORE_LOG(Trace, "Starting AAEngine...");
		auto AApplication = AAEngine::CreateApplication();
		AApplication->Run();
		delete AApplication;
		std::cin.get();
	}
#else
	#error AA Engine only supports Windows!
#endif