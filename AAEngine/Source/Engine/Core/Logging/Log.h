#pragma once

#include "Core/Core.h"
#include "Core/Math/Color.h"

namespace AAEngine {

	/*
	* TO DO:
	* - Add Time stamps
	* - Add File Logging
	*/

	AA_ENGINE_API typedef std::mutex Mutex;

	enum ELogVerbosity
	{
		NoLogging = 0,
		Fatal,
		Error,
		Warning,
		Info,
		Trace,
	};

	/*
	* Singleton Thread-safe Logger class to handle all logging events coming from the application. 
	* 
	* TO DO? : Convert into non-singleton and create an other class having 2 static references to Core and Client Logger?
	*/
	class AA_ENGINE_API CLogger
	{
	public:

		/*
		* static Get function to get a singleton object of the Logger class
		* 
		* @returns CLogger& - reference to the CLogger class.
		*/
		static CLogger& Get()
		{
			static CLogger StaticLoggerReference;
			return StaticLoggerReference;
		}

		/*
		* Templated LogToConsole function to handle logging for varying verbosities and printf style logging.
		*
		* @param LogVerbosity - enum that tracks Verbosity of the Log message.
		* @param bIsCore - boolean to check if this is a Core log or a Client log.
		* @param Format - const char* of Format of the incoming log message.
		* @param Args - variadic template arguments to take in arguments for printing.
		*/
		template<typename... TemplateArgs>
		void LogToConsole(ELogVerbosity LogVerbosity, bool bIsCore, const char* Format, TemplateArgs... Args)
		{
			std::lock_guard<std::mutex> lock(LogMutex);
			switch (LogVerbosity)
			{
			case ELogVerbosity::NoLogging:
				SET_PLATFORM_LOG_COLOR(FColor::White);
				return;
			case ELogVerbosity::Trace:
				SET_PLATFORM_LOG_COLOR(FColor::White);
				break;
			case ELogVerbosity::Warning:
				SET_PLATFORM_LOG_COLOR(FColor::Yellow);
				break;

			case ELogVerbosity::Error:
			case ELogVerbosity::Fatal:
				SET_PLATFORM_LOG_COLOR(FColor::Red);
				break;
			}

			// NEED TO REPLACE WITH STRING BUILDER LATER;
			std::string NewFormat = std::string(bIsCore ? "[CORE] " : "[APP] ").append(Format).append("\n");

			printf(NewFormat.c_str(), Args...);
			SET_PLATFORM_LOG_COLOR(FColor::White);
		}

	private:
		/* private Default constructor to prevent object creation */
		CLogger() = default;

		/* deleted copy constructor to prevent copies of the singleton */
		CLogger(const CLogger&) = delete;
		/* deleted assignment operator to prevent copies of the singleton */
		CLogger& operator=(const CLogger&) = delete;

		/* default destructor */
		~CLogger() {}

		/* Mutex for thread safety */
		std::mutex LogMutex;
	};

/*
* MACRO to Log messages as the Core Logger
*/
#define AA_CORE_LOG(LogVerbosity, Format, ...)	::AAEngine::CLogger::Get().LogToConsole(::AAEngine::LogVerbosity, true, Format, ##__VA_ARGS__)
/*
* MACRO to Log messages as the Client Logger
*/
#define AA_LOG(LogVerbosity, Format, ...)		::AAEngine::CLogger::Get().LogToConsole(::AAEngine::LogVerbosity, false, Format, ##__VA_ARGS__)
}