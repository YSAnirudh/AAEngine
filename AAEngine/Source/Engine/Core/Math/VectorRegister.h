#pragma once

#if AA_PLATFORM_USING_SIMD
	#include "Math/MathSSE.h"
#else
	// Currently Only SSE
	#include "Math/MathSISD.h"
#endif

#include <type_traits>

namespace AAEngine {
namespace Math {

	template<typename T>
	using TVectorRegister = std::conditional_t<std::is_same_v<T, float> , VectorRegister4Float , std::conditional_t<std::is_same_v<T, double>, VectorRegister4Double, void>>;
}
}