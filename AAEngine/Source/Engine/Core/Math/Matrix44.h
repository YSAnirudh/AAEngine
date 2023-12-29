#pragma once

#include "Core/Core.h"
#include "Math/Vector4.h"
#include "Platform/PlatformMath.h"
#include "Core/CoreForwards.h"

#include "Math/VectorRegister.h"

#include <type_traits>

namespace AAEngine {
namespace Math {

	// Row Major - Pre-Multiplication
	// Left Handed Coordinate System
	template<typename T>
	struct alignas(16) TMatrix44
	{
		static_assert(std::is_floating_point_v<T>, "T must be a floating point type.");
	public:

		union
		{
			T MLin[16];
			T M[4][4];
		};

		AA_ENGINE_API static const TMatrix44<T> IdentityMatrix;
		AA_ENGINE_API static const TMatrix44<T> ZeroMatrix;

		FORCEINLINE constexpr TMatrix44() noexcept
		{
			for (int i = 0; i < 16; i++)
			{
				MLin[i] = 0.0f;
			}
		}

		FORCEINLINE constexpr TMatrix44(T InVal) noexcept
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (i == j)
					{
						M[i][i] = InVal;
					}
					else
					{
						M[i][j] = 0.0f;
					}
				}
			}
		}

		FORCEINLINE constexpr TMatrix44(TVector4<T> InRow1Vector, TVector4<T> InRow2Vector, TVector4<T> InRow3Vector, TVector4<T> InRow4Vector) noexcept
		{
			for (int i = 0; i < 4; i++)
			{
				MLin[i] = InRow1Vector[i];
				MLin[i + 4] = InRow2Vector[i];
				MLin[i + 8] = InRow3Vector[i];
				MLin[i + 12] = InRow4Vector[i];
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
			return *this;
		}

		FORCEINLINE constexpr TMatrix44 operator*(const TMatrix44& Mat) const noexcept
		{
			TMatrix44 Result;
			MatrixMultiply(&Result, this, &Mat);
			return Result;
		}

		FORCEINLINE constexpr TMatrix44 operator*(T Val) const noexcept
		{
			// Need to add Vector Intrinsics later
			TMatrix44 Result;
			for (int i = 0; i < 16; i++)
			{
				Result.MLin[i] = MLin[i] * Val;
			}
			return Result;
		}

		FORCEINLINE constexpr TMatrix44& operator*=(const TMatrix44& Mat) noexcept
		{
			MatrixMultiply(this, this, &Mat);
			return *this;
		}

		FORCEINLINE constexpr TMatrix44& operator*=(T Val) noexcept
		{
			// Need to add Vector Intrinsics later
			for (int i = 0; i < 16; i++)
			{
				MLin[i] *= Val;
			}
			return *this;
		}

		FORCEINLINE constexpr TMatrix44 operator+(const TMatrix44& Mat) const noexcept
		{
			// Need to add Vector Intrinsics later
			TMatrix44 Result;
			for (int i = 0; i < 16; i++)
			{
				Result.MLin[i] = MLin[i] + Mat.MLin[i];
			}
			return Result;
		}

		FORCEINLINE constexpr TMatrix44 operator+(T Val) const noexcept
		{
			// Need to add Vector Intrinsics later
			TMatrix44 Result;
			for (int i = 0; i < 16; i++)
			{
				Result.MLin[i] = MLin[i] + Val;
			}
			return Result;
		}

		FORCEINLINE constexpr TMatrix44 operator+() const noexcept
		{
			return *this;
		}

		FORCEINLINE constexpr TMatrix44& operator+=(const TMatrix44& Mat) noexcept
		{
			// Need to add Vector Intrinsics later
			for (int i = 0; i < 16; i++)
			{
				MLin[i] += Mat.MLin[i];
			}
			return *this;
		}

		FORCEINLINE constexpr TMatrix44& operator+=(T Val) noexcept
		{
			// Need to add Vector Intrinsics later
			for (int i = 0; i < 16; i++)
			{
				MLin[i] += Val;
			}
			return *this;
		}

		FORCEINLINE constexpr TMatrix44 operator-(const TMatrix44& Mat) const noexcept
		{
			// Need to add Vector Intrinsics later
			TMatrix44 Result;
			for (int i = 0; i < 16; i++)
			{
				Result.MLin[i] = MLin[i] - Mat.MLin[i];
			}
			return Result;
		}

		FORCEINLINE constexpr TMatrix44 operator-(T Val) const noexcept
		{
			// Need to add Vector Intrinsics later
			TMatrix44 Result;
			for (int i = 0; i < 16; i++)
			{
				Result.MLin[i] = MLin[i] - Val;
			}
			return Result;
		}

		FORCEINLINE constexpr TMatrix44 operator-() const noexcept
		{
			// Need to add Vector Intrinsics later
			TMatrix44 Result;
			for (int i = 0; i < 16; i++)
			{
				Result.MLin[i] = -MLin[i];
			}
			return Result;
		}

		FORCEINLINE constexpr TMatrix44& operator-=(const TMatrix44& Mat) noexcept
		{
			// Need to add Vector Intrinsics later
			for (int i = 0; i < 16; i++)
			{
				MLin[i] -= Mat.MLin[i];
			}
			return *this;
		}

		FORCEINLINE constexpr TMatrix44& operator-=(T Val) noexcept
		{
			// Need to add Vector Intrinsics later
			for (int i = 0; i < 16; i++)
			{
				MLin[i] -= Val;
			}
			return *this;
		}

		FORCEINLINE constexpr TMatrix44 operator/(T Val) const noexcept
		{
			// Need to add Vector Intrinsics later
			TMatrix44 Result;
			for (int i = 0; i < 16; i++)
			{
				Result.MLin[i] = MLin[i] / Val;
			}
			return Result;
		}

		FORCEINLINE constexpr TMatrix44& operator/=(T Val) noexcept
		{
			// Need to add Vector Intrinsics later
			for (int i = 0; i < 16; i++)
			{
				MLin[i] /= Val;
			}
			return *this;
		}

		FORCEINLINE constexpr T Determinant3x3() const noexcept
		{
			return	(M[0][0] * (M[1][1] * M[2][2] - M[2][1] * M[1][2])) - 
					(M[0][1] * (M[1][0] * M[2][2] - M[2][0] * M[1][2])) + 
					(M[0][2] * (M[1][0] * M[2][1] - M[2][0] * M[1][1]));
		}

		FORCEINLINE constexpr T Determinant() const noexcept
		{
			return	M[0][0] * ((M[1][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2])) - (M[1][2] * (M[2][1] * M[3][3] - M[2][3] * M[3][1])) + (M[1][3] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]))) -
					M[0][1] * ((M[1][0] * (M[2][2] * M[3][3] - M[2][3] * M[3][2])) - (M[1][2] * (M[2][0] * M[3][3] - M[2][3] * M[3][0])) + (M[1][3] * (M[2][0] * M[3][2] - M[2][2] * M[3][0]))) +
					M[0][2] * ((M[1][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1])) - (M[1][1] * (M[2][0] * M[3][3] - M[2][3] * M[3][0])) + (M[1][3] * (M[2][0] * M[3][1] - M[2][1] * M[3][0]))) -
					M[0][3] * ((M[1][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1])) - (M[1][1] * (M[2][0] * M[3][2] - M[2][2] * M[3][0])) + (M[1][2] * (M[2][0] * M[3][1] - M[2][1] * M[3][0])));
		}

		FORCEINLINE constexpr void Transpose() noexcept
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = i + 1; j < 4; j++)
				{
					FMath::Swap(M[i][j], M[j][i]);
				}
			}
		}

		FORCEINLINE constexpr void InverseFast() noexcept
		{
			AA_CORE_ASSERT(Determinant() != 0.0f, "Determinant 0.0f, will crash in release.");
			MatrixInverse(this, this);
		}

		FORCEINLINE constexpr void Inverse() noexcept
		{
			T Det = Determinant();
			if (Det == 0.0f)
			{
				*this = IdentityMatrix;
			}
			else
			{
				MatrixInverse(this, this);
			}
		}

		FORCEINLINE constexpr TMatrix44 GetTranspose() noexcept
		{
			TMatrix44 Result;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					Result.M[j][i] = M[i][j];
				}
			}
			return Result;
		}

		FORCEINLINE constexpr TMatrix44 GetInverseFast() noexcept
		{
			AA_CORE_ASSERT(Determinant() != 0.0f, "Determinant 0.0f, will crash in release.");
			
			TMatrix44 Result;
			MatrixInverse(&Result, this);

			return Result;
		}

		FORCEINLINE constexpr TMatrix44 GetInverse() noexcept
		{
			TMatrix44 Result;

			T Det = Determinant();
			if (Det == 0.0f)
			{
				Result = IdentityMatrix;
			}
			else
			{
				MatrixInverse(&Result, this);
			}

			return Result;
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

	template<typename T>
	FORCEINLINE TVector4<T> operator*(const TVector4<T>& Vec, const TMatrix44<T>& Matrix)
	{
		TVector4<T> Result;
		TVectorRegister<T> VecReg = VectorLoadAligned(Vec.XYZW);
		TVectorRegister<T> ResReg = VectorMatrixMultiply(VecReg, &Matrix);
		VectorStoreAligned(ResReg, Result.XYZW);
		return Result;
	}

}
}