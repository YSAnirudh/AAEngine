#pragma once

#include "Core/Core.h"
#include "Math/Vector4.h"

#include <type_traits>

namespace AAEngine {
namespace Math {

	template<typename T>
	struct alignas(16) TMatrix44
	{
		static_assert(std::is_floating_point_v<T>, "T must be a floating point type.");
	public:

		union
		{
			T M[4][4];
			T MLin[16];
		};

		FORCEINLINE constexpr TMatrix44() noexcept
		{
		}

		FORCEINLINE constexpr TMatrix44(T InVal) noexcept
		{
			for (int i = 0; i < 16; i++)
			{
				MLin[i] = InVal;
			}
		}

		FORCEINLINE constexpr TMatrix44(TVector4<T> InRow1Vector, TVector4<T> InRow2Vector, TVector4<T> InRow3Vector, TVector4<T> InRow4Vector) noexcept
		{
			for (int i = 0; i < 4; i++)
			{
				M[0][i] = InRow1Vector[i];
				M[1][i] = InRow2Vector[i];
				M[2][i] = InRow3Vector[i];
				M[3][i] = InRow4Vector[i];
			}
		}

		FORCEINLINE constexpr TMatrix44(const TMatrix44& Mat) noexcept
		{
			for (int i = 0; i < 16; i++)
			{
				MLin[i] = Mat.MLin[i];
			}
		}

		FORCEINLINE constexpr TMatrix44& operator=(const TMatrix44& Mat) noexcept
		{
			for (int i = 0; i < 16; i++)
			{
				MLin[i] = Mat.MLin[i];
			}
		}

		FORCEINLINE constexpr TMatrix44 operator*(const TMatrix44& Mat) noexcept
		{

		}



		FORCEINLINE constexpr std::string ToString() const noexcept
		{
			std::stringstream SS;
			SS << "[" << M[0][0] << ", " << M[0][1] << ", " << M[0][2] << ", " << M[0][3] << "]\n";
			SS << "[" << M[1][0] << ", " << M[1][1] << ", " << M[1][2] << ", " << M[1][3] << "]\n";
			SS << "[" << M[2][0] << ", " << M[2][1] << ", " << M[2][2] << ", " << M[2][3] << "]\n";
			SS << "[" << M[3][0] << ", " << M[3][1] << ", " << M[3][2] << ", " << M[3][3] << "]";
			return SS.str();
		}
	};

}
}