#pragma once

/*
* Important Comment Highlights
* NOTE - Any notes for functions/classes/files
* TO DO - To mark something to be done at a later date
* 
* These can be searched for in the Code base to identify the Important Comment Highlights to come back to
*/

/*
* NAMING CONVENTIONS
* PREDEFINED Prefixes for classes and data types in AA Engine
*
* Boolean variables - b (In class or outside class)
*
* Base classes - C
* Enums - E
* Templates - T
* Interfaces - I
* Structs - F
*
* Functions / Variables - Camel Case
*/

/*
* Core{Name}.h files are used for Preprocessor directives related to Name or in the Name folder
* Includes{Name}.h files are used for Including all the required files related to Name or in the Name folder
* 
*/

/*
* Math - 
* Z - Forward
* Y - Up
* X - Right
* Left Handed Coordinate System
* Row Major - Pre-Multiplication Matrices
*/

// TEST RESULTS TEMPLATE = Update whenever it changes
/*
* TEST RESULTS
*
* 1)
* Speed (Avg) =
* Speed (Fastest) =
*/

/*
* TO DO: Pre Build step of Running ProcessorSIMDInfo.cpp before every Generate Project Files.
*/

// DLL import/export
#ifdef AA_PLATFORM_WINDOWS
	#ifdef AA_DYNAMIC_LINK
		#ifdef AA_BUILD_DLL
			#define AA_ENGINE_API __declspec(dllexport)
		#else
			#define AA_ENGINE_API __declspec(dllimport)
		#endif
	#else
		#define AA_ENGINE_API
	#endif
#else
	#error AA Engine only supports Windows!
#endif

#ifdef AA_DEBUG
	#define AA_ENABLE_ASSERTS 1
#endif

#ifndef AA_TESTER_FILE
	#define AA_TESTER_FILE 1
#endif


#if AA_ENABLE_ASSERTS
	#define AA_CORE_ASSERT(x, ...)		{ if (!int(x)) { AA_CORE_LOG(Error, "Assertion Failed: %s", __VA_ARGS__); __debugbreak(); } }
	#define AA_ASSERT(x, ...)			{ if (!int(x)) { AA_LOG(Error, "Assertion Failed: %s", __VA_ARGS__); __debugbreak(); } }
#else
	#define AA_CORE_ASSERT(x, ...)
	#define AA_ASSERT(x, ...)
#endif

#ifdef AA_PLATFORM_WINDOWS
	#define FORCEINLINE __forceinline
#else
	#error AA Engine only supports Windows!
#endif

#include "Engine/EventSystem/CoreEvents.h"
#include "Engine/Core/Math/CoreMath.h"
#include "Engine/Core/Memory/CoreMemory.h"
#include "Platform/CorePlatform.h"