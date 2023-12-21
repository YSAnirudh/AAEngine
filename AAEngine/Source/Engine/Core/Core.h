#pragma once

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

// TEST RESULTS TEMPLATE = Update whenever it changes
/*
* TEST RESULTS
*
* 1)
* Speed (Avg) =
* Speed (Fastest) =
*/

// DLL import/export
#ifdef AA_PLATFORM_WINDOWS
	#ifdef AA_BUILD_DLL
		#define AA_ENGINE_API __declspec(dllexport)
	#else
		#define AA_ENGINE_API __declspec(dllimport)
	#endif
#else
	#error AA Engine only supports Windows!
#endif

#ifdef AA_DEBUG
	#define AA_ENABLE_ASSERTS
#endif


#ifdef AA_ENABLE_ASSERTS
	#define AA_CORE_ASSERT(x, ...)		{ if (!x) { AA_CORE_LOG(Error, "Assertion Failed: %s", __VA_ARGS__); __debugbreak(); } }
	#define AA_ASSERT(x, ...)			{ if (!x) { AA_LOG(Error, "Assertion Failed: %s", __VA_ARGS__); __debugbreak(); } }
#else
	#define AA_CORE_ASSERT(x, ...)
	#define AA_ASSERT(x, ...)
#endif

#ifdef AA_PLATFORM_WINDOWS
	#define FORCEINLINE __forceinline
#else
	#error AA Engine only supports Windows!
#endif

#ifndef COMPILER_HAS_GENERATED_COMPARISION_OPERATORS
	#define COMPILER_HAS_GENERATED_COMPARISION_OPERATORS (__cplusplus >= 202002L)
#endif

#include "Engine/EventSystem/CoreEvents.h"
#include "Engine/Core/Math/CoreMath.h"
#include "Engine/Core/Memory/CoreMemory.h"