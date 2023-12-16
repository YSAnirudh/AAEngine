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

#ifdef AA_PLATFORM_WINDOWS
	#define FORCEINLINE __forceinline
#else
	#define FORCEINLINE
	#error AA Engine only supports Windows!
#endif

#ifdef AA_ENABLE_ASSERTS
	#define AA_CORE_ASSERT(x, ...)		{ if (!x) { AA_CORE_LOG("Assertion Failed: %s", __VA_ARGS__); __debugbreak(); } }
	#define AA_ASSERT(x, ...)			{ if (!x) { AA_LOG("Assertion Failed: %s", __VA_ARGS__); __debugbreak(); } }
#else
	#define AA_CORE_ASSERT(x, ...)
	#define AA_ASSERT(x, ...)
#endif

#include "Engine/EventSystem/CoreEvents.h"
#include "Engine/Core/Math/CoreMath.h"
#include "Engine/Core/Memory/CoreMemory.h"