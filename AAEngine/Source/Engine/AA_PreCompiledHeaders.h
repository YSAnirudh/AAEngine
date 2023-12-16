#pragma once

#include <stdio.h>
#include <iostream>
#include <memory>
#include <functional>
#include <algorithm>
#include <mutex>
#include <chrono>

#include <string>
#include <sstream>

#ifdef AA_PLATFORM_WINDOWS
	#include "Windows.h"
#endif

// AA Engine Precompiled headers
#include "Core/Logging/Log.h"

// Core Folder Includes
#include "Core/Memory/IncludesMemory.h"