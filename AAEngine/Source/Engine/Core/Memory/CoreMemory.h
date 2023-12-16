#pragma once

#include "Core/Core.h"

#ifdef AA_PLATFORM_WINDOWS
	typedef decltype(nullptr) NULLPTR_TYPE;
#else
	#error AAEngine only supports Windows!
#endif
