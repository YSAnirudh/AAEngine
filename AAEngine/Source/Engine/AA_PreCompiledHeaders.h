#pragma once

#include <stdio.h>
#include <iostream>
#include <memory>
#include <functional>
#include <algorithm>
#include <mutex>
#include <chrono>
#include <vector>
#include <array>
#include <math.h>

#include <string>
#include <sstream>
#include <fstream>

#ifdef AA_PLATFORM_WINDOWS
	#include "Windows.h"
#endif

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

// AA Engine Precompiled headers
#include "Core/Logging/Log.h"

// Core Folder Includes
#include "Core/Memory/IncludesMemory.h"
#include "Core/Containers/IncludesContainers.h"
#include "Core/Math/IncludesMath.h"