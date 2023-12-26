#pragma once

#include "AA_PreCompiledHeaders.h"
#include "Core.h"

namespace AAEngine {

	/*
	* Enum for Different Time Resolutions
	*/
	enum ETimeResolution
	{
		NanoSeconds,
		MicroSeconds,
		MilliSeconds,
		Seconds,
		Minutes,
		Hours
	};

	/*
	* Templated Timer class with custom resolution for Time. Ex: Seconds/MicroSeconds
	*/
	template<ETimeResolution InTimeResolution>
	class TTimer
	{
		/*
		* Chrono library define
		*/
		#define CH std::chrono

		/*
		* using define Chrono high res clock 
		*/
		using CH_HRClock = std::chrono::high_resolution_clock;

		/*
		* using define templated Chrono timepoint
		*/
		template<typename TimepointObject>
		using CH_TP = std::chrono::time_point<TimepointObject>;
	public:
		/*
		* Default constructor that Starts the time and sets the Timer Name to "Base"
		*/
		FORCEINLINE TTimer()
		{
			TimerName = "Base";
			StartTimepoint = CH_HRClock::now();
		}

		/*
		* Constructor that takes in rvalue ref of an std::string to prevent copies
		* Starts the time and sets the Timer Name to Move(InTimerName)
		* 
		* @param InTimerName - rvalue Reference of the Timer name as an std::string
		*/
		explicit FORCEINLINE TTimer(std::string&& InTimerName)
		{
			TimerName = Move(InTimerName);
			StartTimepoint = CH_HRClock::now();
		}

		/*
		* Destructor that class the Stop function
		* Stops the Timer and outputs the result
		*/
		FORCEINLINE ~TTimer()
		{
			Stop();
		}

		/*
		* Stop function that
		* 1) Stops the Timer
		* 2) Outputs the Time in the Template Time resolution arguments
		*/
		void Stop()
		{
			CH_TP<CH_HRClock> EndTimepoint = CH_HRClock::now();

			long long Duration = CalculateTime(EndTimepoint);
			AA_CORE_LOG(Info, "%s Timer Duration: %ld", TimerName.c_str(), Duration);
		}

		/*
		* Reset function that 
		* 1) Stops the Timer
		* 2) Outputs the Time in the Template Time resolution arguments
		* 3) Resets the StartTime
		*/
		void Reset()
		{
			CH_TP<CH_HRClock> EndTimepoint = CH_HRClock::now();

			long long Duration = CalculateTime(EndTimepoint);
			AA_CORE_LOG(Info, "Resetting Timer. Current %s Timer Duration: %ld", TimerName.c_str(), Duration);

			StartTimepoint = CH_HRClock::now();
		}
	private:
		/*
		* CalculateTime function calculates the time between Start and End Timepoint and returns the Duration in InTimeResolution
		* 
		* @param EndTimepoint - End time of the Timer
		* 
		* @return long long of the Duration of the Timer for StartTimepoint to EndTimepoint
		*/
		long long CalculateTime(const CH_TP<CH_HRClock>& EndTimepoint)
		{
			long long StartTime = 0;
			long long EndTime = 0;

			switch (InTimeResolution)
			{
			case NanoSeconds:
				StartTime = CH::time_point_cast<CH::nanoseconds>(StartTimepoint).time_since_epoch().count();
				EndTime = CH::time_point_cast<CH::nanoseconds>(EndTimepoint).time_since_epoch().count();
				break;
			case MicroSeconds:
				StartTime = CH::time_point_cast<CH::microseconds>(StartTimepoint).time_since_epoch().count();
				EndTime = CH::time_point_cast<CH::microseconds>(EndTimepoint).time_since_epoch().count();
				break;
			case MilliSeconds:
				StartTime = CH::time_point_cast<CH::milliseconds>(StartTimepoint).time_since_epoch().count();
				EndTime = CH::time_point_cast<CH::milliseconds>(EndTimepoint).time_since_epoch().count();
				break;
			case Seconds:
				StartTime = CH::time_point_cast<CH::seconds>(StartTimepoint).time_since_epoch().count();
				EndTime = CH::time_point_cast<CH::seconds>(EndTimepoint).time_since_epoch().count();
				break;
			case Minutes:
				StartTime = CH::time_point_cast<CH::minutes>(StartTimepoint).time_since_epoch().count();
				EndTime = CH::time_point_cast<CH::minutes>(EndTimepoint).time_since_epoch().count();
				break;
			case Hours:
				StartTime = CH::time_point_cast<CH::hours>(StartTimepoint).time_since_epoch().count();
				EndTime = CH::time_point_cast<CH::hours>(EndTimepoint).time_since_epoch().count();
				break;
			}

			return EndTime - StartTime;
		}

	private:
		/*
		* Chrono Timepoint to track the start time.
		*/
		CH_TP<CH_HRClock> StartTimepoint;
		/*
		* String to name the Timer
		* TO DO? : Maybe not needed? Overhead
		*/
		std::string TimerName;
	};
}