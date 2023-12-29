#pragma once

#if AA_PLATFORM_ENABLE_SIMD_INTRINSICS

	// Currently No SIMD
	#include "Math/MathSISD.h"
#else
	#include "Math/MathSISD.h"
#endif

#include <type_traits>

namespace AAEngine {
namespace Math {

	template<typename T>
	using TVectorRegister = std::conditional_t<std::is_same_v<T, float> , VectorRegister4Float , std::conditional_t<std::is_same_v<T, double>, VectorRegister4Double, void>>;
}
}