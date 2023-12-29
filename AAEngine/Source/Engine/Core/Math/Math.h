#pragma once

#include "Core/Core.h"
#include "Math/MathUtils.h"

namespace AAEngine {
namespace Math {

	struct FMath
	{
		
		static FORCEINLINE float Sqrt(float A) noexcept { return sqrtf(A); }
		static FORCEINLINE double Sqrt(double A) noexcept { return sqrt(A); }

		static FORCEINLINE float InvSqrt(float A) noexcept { return 1.0f / sqrtf(A); }
		static FORCEINLINE double InvSqrt(double A) noexcept { return 1.0 / sqrt(A); }

		static FORCEINLINE float Sin(float A) noexcept { return sinf(A); }
		static FORCEINLINE double Sin(double A) noexcept { return sin(A); }

		static FORCEINLINE float Cos(float A) noexcept { return cosf(A); }
		static FORCEINLINE double Cos(double A) noexcept { return cos(A); }

		static FORCEINLINE float Tan(float A) noexcept { return tanf(A); }
		static FORCEINLINE double Tan(double A) noexcept { return tan(A); }

		static FORCEINLINE float ASin(float A) noexcept { return asinf(A); }
		static FORCEINLINE double ASin(double A) noexcept { return asin(A); }

		static FORCEINLINE float ACos(float A) noexcept { return acosf(A); }
		static FORCEINLINE double ACos(double A) noexcept { return acos(A); }

		static FORCEINLINE float ATan(float A) noexcept { return atanf(A); }
		static FORCEINLINE double ATan(double A) noexcept { return atan(A); }

		static FORCEINLINE float ATan2(float A, float B) noexcept { return atan2f(A, B); }
		static FORCEINLINE double ATan2(double A, double B) noexcept { return atan2(A, A); }

		static FORCEINLINE float Abs(float A) noexcept { return fabsf(A); }
		static FORCEINLINE double Abs(double A) noexcept { return abs(A); }

		/** Computes absolute value in a generic way */
		template<class T>
		static FORCEINLINE constexpr T Abs(const T A)
		{
			return (A < (T)0) ? -A : A;
		}

		/** Returns 1, 0, or -1 depending on relation of T to 0 */
		template<class T>
		static FORCEINLINE constexpr T Sign(const T A)
		{
			return (A > (T)0) ? (T)1 : ((A < (T)0) ? (T)-1 : (T)0);
		}

		/** Returns higher value in a generic way */
		template<class T>
		static FORCEINLINE constexpr T Max(const T A, const T B)
		{
			return (B < A) ? A : B;
		}

		/** Returns lower value in a generic way */
		template<class T>
		static FORCEINLINE constexpr T Min(const T A, const T B)
		{
			return (A < B) ? A : B;
		}

		/** Swaps 2 elements */
		template<class T>
		static FORCEINLINE constexpr void Swap(T& A, T& B)
		{
			T Temp = B;
			B = A;
			A = Temp;
		}

		
	};

}
}
