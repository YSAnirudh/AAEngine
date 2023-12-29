#pragma once

#include "Core.h"
#include <memory>

namespace AAEngine {

	struct AA_ENGINE_API FMemory
	{
	public:
		static void*	MemCopy(void* Dest, const void* Src, size_t Size)							{ return std::memcpy(Dest, Src, Size); }
		static void*	MemMove(void* Dest, const void* Src, size_t Size)							{ return std::memmove(Dest, Src, Size); }
		static void*	MemSet(void* Dest, int Value, size_t Size)									{ return std::memset(Dest, Value, Size); }
		static int		MemCompare(const void* Buffer1, const void* Buffer2, size_t Size)			{ return std::memcmp(Buffer1, Buffer2, Size); }
	};	
}