#pragma once

#include "Core/Core.h"
#include "Math/Vector4.h"
#include "Core/CoreForwards.h"

#include "Math/VectorRegister.h"

#include <type_traits>

namespace AAEngine {
namespace Math {

	/* 
	* Row Major - Pre - Multiplication
	* Left Handed Coordinate System
	* TO DO:	Need to add Vector Intrinsics to Addition if Performance matches, later
	*			Currently the way is to use MemCopy which increases the time to compute SISD operations by 0.5x times
	*/
	template<typename T>
	struct alignas(16) TMatrix44
	{
		static_assert(std::is_floating_point_v<T>, "T must be a floating point type.");
	public:

		union
		{
			alignas(16) T MLin[16];
			alignas(16) T M[4][4];
		};

		AA_ENGINE_API static const TMatrix44<T> IdentityMatrix;
		AA_ENGINE_API static const TMatrix44<T> ZeroMatrix;

		FORCEINLINE constexpr TMatrix44() noexcept
		{
			/*for (int i = 0; i < 16; i++)
			{
				MLin[i] = static_cast<T>(0.0f);
			}*/
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
						M[i][j] = static_cast<T>(0.0f);
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
			for (int i = 0; i < 16; i++)
			{
				MLin[i] *= Val;
			}
			return *this;
		}

		FORCEINLINE constexpr TMatrix44 operator+(const TMatrix44& Mat) const noexcept
		{
			TMatrix44 Result;
			for (int i = 0; i < 16; i++)
			{
				Result.MLin[i] = MLin[i] + Mat.MLin[i];
			}
			return Result;
		}

		FORCEINLINE constexpr TMatrix44 operator+(T Val) const noexcept
		{
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
			for (int i = 0; i < 16; i++)
			{
				MLin[i] += Mat.MLin[i];
			}
			return *this;
		}

		FORCEINLINE constexpr TMatrix44& operator+=(T Val) noexcept
		{
			for (int i = 0; i < 16; i++)
			{
				MLin[i] += Val;
			}
			return *this;
		}

		FORCEINLINE constexpr TMatrix44 operator-(const TMatrix44& Mat) const noexcept
		{
			TMatrix44 Result;
			for (int i = 0; i < 16; i++)
			{
				Result.MLin[i] = MLin[i] - Mat.MLin[i];
			}
			return Result;
		}

		FORCEINLINE constexpr TMatrix44 operator-(T Val) const noexcept
		{
			TMatrix44 Result;
			for (int i = 0; i < 16; i++)
			{
				Result.MLin[i] = MLin[i] - Val;
			}
			return Result;
		}

		FORCEINLINE constexpr TMatrix44 operator-() const noexcept
		{
			TMatrix44 Result;
			for (int i = 0; i < 16; i++)
			{
				Result.MLin[i] = -MLin[i];
			}
			return Result;
		}

		FORCEINLINE constexpr TMatrix44& operator-=(const TMatrix44& Mat) noexcept
		{
			for (int i = 0; i < 16; i++)
			{
				MLin[i] -= Mat.MLin[i];
			}
			return *this;
		}

		FORCEINLINE constexpr TMatrix44& operator-=(T Val) noexcept
		{
			for (int i = 0; i < 16; i++)
			{
				MLin[i] -= Val;
			}
			return *this;
		}

		FORCEINLINE constexpr TMatrix44 operator/(T Val) const noexcept
		{
			TMatrix44 Result;
			for (int i = 0; i < 16; i++)
			{
				Result.MLin[i] = MLin[i] / Val;
			}
			return Result;
		}

		FORCEINLINE constexpr TMatrix44& operator/=(T Val) noexcept
		{
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
			AA_CORE_ASSERT(Determinant() != static_cast<T>(0.0f), "Determinant 0.0f, will crash in release.");
			MatrixInverse(this, this);
		}

		FORCEINLINE constexpr void Inverse() noexcept
		{
			T Det = Determinant();
			if (Det == static_cast<T>(0.0f))
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
			AA_CORE_ASSERT(Determinant() != static_cast<T>(0.0f), "Determinant 0, will crash in release.");
			
			TMatrix44 Result;
			MatrixInverse(&Result, this);

			return Result;
		}

		FORCEINLINE constexpr TMatrix44 GetInverse() noexcept
		{
			TMatrix44 Result;

			T Det = Determinant();
			if (Det == static_cast<T>(0))
			{
				Result = IdentityMatrix;
			}
			else
			{
				MatrixInverse(&Result, this);
			}

			return Result;
		}

		/*
		* Const ToString function to convert out matrix into a String format
		* Used Printing Our Matrix to the Console for Debugging
		*
		* @returns std::string of our matrix in a formatted way.
		*/
		FORCEINLINE constexpr std::string ToString() const noexcept
		{
			std::stringstream SS;
			SS << "[" << M[0][0] << ", " << M[0][1] << ", " << M[0][2] << ", " << M[0][3] << "]\n";
			SS << "[" << M[1][0] << ", " << M[1][1] << ", " << M[1][2] << ", " << M[1][3] << "]\n";
			SS << "[" << M[2][0] << ", " << M[2][1] << ", " << M[2][2] << ", " << M[2][3] << "]\n";
			SS << "[" << M[3][0] << ", " << M[3][1] << ", " << M[3][2] << ", " << M[3][3] << "]";
			return SS.str();
		}

		/*
		* Graphics/Transformations Based Matrices and Matrix Transformations
		* 
		* NOTE: All Graphics Matrices are Left Handed to reflect the Left Handedness of the AAEngine
		* 
		* TO DO: Make Perspective matrices support -1 to 1 and 0 to 1 depending of the Graphics API
		* TO DO: Convert to Z - Up, Y - Right, X - Forward ???
		* 
		* Euler		- Pitch = Y (Right)
		*			- Yaw = Z (Up)
		*			- Roll = X (Forward)
		*/

		FORCEINLINE constexpr static TMatrix44 LookAt(const TVector3<T>& Forward, const TVector3<T>& Up, const TVector3<T>& LookingAt)
		{

		}

		FORCEINLINE constexpr static TMatrix44 MakeFromRotationX(float AngleDeg) noexcept
		{
			TMatrix44 RotMatrix(static_cast<T>(1.0f));

			T AngleRad = FMath::DegToRad(AngleDeg);

			RotMatrix.M[1][1] = FMath::Cos(AngleRad);
			RotMatrix.M[2][1] = FMath::Sin(AngleRad);
			RotMatrix.M[1][2] = -FMath::Sin(AngleRad);
			RotMatrix.M[2][2] = FMath::Cos(AngleRad);

			return RotMatrix;
		}

		FORCEINLINE constexpr static TMatrix44 MakeFromRotationY(float AngleDeg) noexcept
		{
			TMatrix44 RotMatrix(static_cast<T>(1.0f));

			T AngleRad = FMath::DegToRad(AngleDeg);

			RotMatrix.M[0][0] = FMath::Cos(AngleRad);
			RotMatrix.M[2][0] = -FMath::Sin(AngleRad);
			RotMatrix.M[0][2] = FMath::Sin(AngleRad);
			RotMatrix.M[2][2] = FMath::Cos(AngleRad);

			return RotMatrix;
		}

		FORCEINLINE constexpr static TMatrix44 MakeFromRotationZ(float AngleDeg) noexcept
		{
			TMatrix44 RotMatrix(static_cast<T>(1.0f));

			T AngleRad = FMath::DegToRad(AngleDeg);

			RotMatrix.M[0][0] = FMath::Cos(AngleRad);
			RotMatrix.M[1][0] = FMath::Sin(AngleRad);
			RotMatrix.M[0][1] = -FMath::Sin(AngleRad);
			RotMatrix.M[1][1] = FMath::Cos(AngleRad);

			return RotMatrix;
		}

		FORCEINLINE constexpr static TMatrix44 MakeFromRotationXYZ(const TEuler<T>& InRotation) noexcept
		{
			TMatrix44 XRotMat = MakeFromRotationX(InRotation.Pitch);
			TMatrix44 YRotMat = MakeFromRotationY(InRotation.Yaw);
			TMatrix44 ZRotMat = MakeFromRotationZ(InRotation.Roll);

			return XRotMat * YRotMat * ZRotMat;
		}

		FORCEINLINE constexpr static TMatrix44 MakeFromLocation(const TVector3<T>& InLocation) noexcept
		{
			TMatrix44 TranslationMatrix(static_cast<T>(1.0f));

			TranslationMatrix.M[3][0] = InLocation.X;
			TranslationMatrix.M[3][1] = InLocation.Y;
			TranslationMatrix.M[3][2] = InLocation.Z;

			return TranslationMatrix;
		}

		FORCEINLINE constexpr static TMatrix44 MakeFromAngleAxis(float AngleDeg, const TVector3<T>& Axis) noexcept
		{
			AA_CORE_ASSERT(int(Axis.IsNormalized()), "UnNormalized Axis. Incorrect!");

			TMatrix44 RotMatrix(static_cast<T>(1.0f));

			T AngleRad = FMath::DegToRad(AngleDeg);
			T CosAngle = FMath::Cos(AngleRad);
			T SinAngle = FMath::Sin(AngleRad);

			RotMatrix.M[0][0] = (Axis.X * Axis.X * static_cast<T>(1.0f) - CosAngle) + CosAngle;
			RotMatrix.M[0][1] = (Axis.X * Axis.Y * static_cast<T>(1.0f) - CosAngle) + Axis.Z * SinAngle;
			RotMatrix.M[0][2] = (Axis.X * Axis.Z * static_cast<T>(1.0f) - CosAngle) - Axis.Y * SinAngle;

			RotMatrix.M[1][0] = (Axis.Y * Axis.X * static_cast<T>(1.0f) - CosAngle) - Axis.Z * SinAngle;
			RotMatrix.M[1][1] = (Axis.Y * Axis.Y * static_cast<T>(1.0f) - CosAngle) + CosAngle;
			RotMatrix.M[1][2] = (Axis.Y * Axis.Z * static_cast<T>(1.0f) - CosAngle) + Axis.X * SinAngle;
			
			RotMatrix.M[2][0] = (Axis.Z * Axis.X * static_cast<T>(1.0f) - CosAngle) + Axis.Y * SinAngle;
			RotMatrix.M[2][1] = (Axis.Z * Axis.Y * static_cast<T>(1.0f) - CosAngle) - Axis.X * SinAngle;
			RotMatrix.M[2][2] = (Axis.Z * Axis.Z * static_cast<T>(1.0f) - CosAngle) + CosAngle;

			return RotMatrix;
		}

		FORCEINLINE constexpr static TMatrix44 MakeFromTransform(const TTransform<T>& InTransform) noexcept
		{
			return TMatrix44();
		}

		FORCEINLINE constexpr static TMatrix44 MakePerspective(T FOV, T Aspect, T Near, T Far) noexcept
		{
			// Only for OpenGL
			return MakePerspectiveNegativeOneToOne(FOV, Aspect, Near, Far);
		}

		FORCEINLINE constexpr static TMatrix44 MakePerspectiveNegativeOneToOne(T FOV, T Aspect, T Near, T Far) noexcept
		{
			AA_CORE_ASSERT(int(Aspect != static_cast<T>(0.0f)), "Aspect Ratio is 0");

			TMatrix44 PerspectiveProjectionMatrix;

			T TanFOVBy2 = FMath::Tan(FOV / static_cast<T>(2.0f));
			T OneByFarMinusNear = static_cast<T>(1.0f) / (Far - Near);

			PerspectiveProjectionMatrix.M[0][0] = static_cast<T>(1.0f) / (Aspect * TanFOVBy2);
			PerspectiveProjectionMatrix.M[1][1] = static_cast<T>(1.0f) / TanFOVBy2;
			PerspectiveProjectionMatrix.M[2][2] = (Far + Near) * OneByFarMinusNear;
			PerspectiveProjectionMatrix.M[3][2] = -static_cast<T>(2.0f) * Far * Near * OneByFarMinusNear;
			PerspectiveProjectionMatrix.M[2][3] = static_cast<T>(1.0f);

			return PerspectiveProjectionMatrix;
		}

		FORCEINLINE constexpr static TMatrix44 MakePerspectiveZeroToOne(T FOV, T Aspect, T Near, T Far) noexcept
		{
			TMatrix44 PerspectiveProjectionMatrix;

			T TanFOVBy2 = FMath::Tan(FOV / static_cast<T>(2.0f));
			T OneByFarMinusNear = static_cast<T>(1.0f) / (Far - Near);

			PerspectiveProjectionMatrix.M[0][0] = static_cast<T>(1.0f) / (Aspect * TanFOVBy2);
			PerspectiveProjectionMatrix.M[1][1] = static_cast<T>(1.0f) / TanFOVBy2;
			PerspectiveProjectionMatrix.M[2][2] = Far * OneByFarMinusNear;
			PerspectiveProjectionMatrix.M[3][2] = -Far * Near * OneByFarMinusNear;
			PerspectiveProjectionMatrix.M[2][3] = static_cast<T>(1.0f);

			return PerspectiveProjectionMatrix;
		}

		FORCEINLINE constexpr static TMatrix44 MakePerspective(T Left, T Right, T Bottom, T Top, T Near, T Far) noexcept
		{
			// Only for OpenGL
			return MakePerspectiveNegativeOneToOne(Left, Right, Bottom, Top, Near, Far);
		}

		FORCEINLINE constexpr static TMatrix44 MakePerspectiveNegativeOneToOne(T Left, T Right, T Bottom, T Top, T Near, T Far) noexcept
		{
			TMatrix44 PerspectiveProjectionMatrix;

			T OneByRightMinusLeft = static_cast<T>(1.0f) / (Right - Left);
			T OneByTopMinusBottom = static_cast<T>(1.0f) / (Top - Bottom);
			T OneByFarMinusNear = static_cast<T>(1.0f) / (Far - Near);

			PerspectiveProjectionMatrix.M[0][0] = static_cast<T>(2.0f) * Near * OneByRightMinusLeft;
			PerspectiveProjectionMatrix.M[1][1] = static_cast<T>(2.0f) * Near * OneByTopMinusBottom;
			PerspectiveProjectionMatrix.M[2][2] = (Far + Near) * OneByFarMinusNear;
			PerspectiveProjectionMatrix.M[2][0] = -(Right + Left) * OneByRightMinusLeft;
			PerspectiveProjectionMatrix.M[2][1] = -(Top + Bottom) * OneByTopMinusBottom;
			PerspectiveProjectionMatrix.M[3][2] = static_cast<T>(1.0f);
			PerspectiveProjectionMatrix.M[2][3] = -static_cast<T>(2.0f) * Far * Near * OneByFarMinusNear;

			return PerspectiveProjectionMatrix;
		}

		FORCEINLINE constexpr static TMatrix44 MakePerspectiveZeroToOne(T Left, T Right, T Bottom, T Top, T Near, T Far) noexcept
		{
			TMatrix44 PerspectiveProjectionMatrix;

			T OneByRightMinusLeft = static_cast<T>(1.0f) / (Right - Left);
			T OneByTopMinusBottom = static_cast<T>(1.0f) / (Top - Bottom);
			T OneByFarMinusNear = static_cast<T>(1.0f) / (Far - Near);

			PerspectiveProjectionMatrix.M[0][0] = static_cast<T>(2.0f) * Near * OneByRightMinusLeft;
			PerspectiveProjectionMatrix.M[1][1] = static_cast<T>(2.0f) * Near * OneByTopMinusBottom;
			PerspectiveProjectionMatrix.M[2][2] = Far * OneByFarMinusNear;
			PerspectiveProjectionMatrix.M[2][0] = -(Right + Left) * OneByRightMinusLeft;
			PerspectiveProjectionMatrix.M[2][1] = -(Top + Bottom) * OneByTopMinusBottom;
			PerspectiveProjectionMatrix.M[3][2] = static_cast<T>(1.0f);
			PerspectiveProjectionMatrix.M[2][3] = -Far * Near * OneByFarMinusNear;

			return PerspectiveProjectionMatrix;
		}

		FORCEINLINE constexpr static TMatrix44 MakeOrthographic(T Left, T Right, T Bottom, T Top, T Near, T Far) noexcept
		{
			// Only for OpenGL
			return MakeOrthographicNegativeOneToOne(Left, Right, Bottom, Top, Near, Far);
		}

		FORCEINLINE constexpr static TMatrix44 MakeOrthographicNegativeOneToOne(T Left, T Right, T Bottom, T Top, T Near, T Far) noexcept
		{
			TMatrix44 OrthographicProjectionMatrix(static_cast<T>(1.0f));

			T OneByRightMinusLeft = static_cast<T>(1.0f) / (Right - Left);
			T OneByTopMinusBottom = static_cast<T>(1.0f) / (Top - Bottom);
			T OneByFarMinusNear = static_cast<T>(1.0f) / (Far - Near);

			OrthographicProjectionMatrix.M[0][0] = static_cast<T>(2.0f) * OneByRightMinusLeft;
			OrthographicProjectionMatrix.M[1][1] = static_cast<T>(2.0f) * OneByTopMinusBottom;
			OrthographicProjectionMatrix.M[2][2] = static_cast<T>(2.0f) * OneByFarMinusNear;
			OrthographicProjectionMatrix.M[3][0] = -(Right + Left) * OneByRightMinusLeft;
			OrthographicProjectionMatrix.M[3][1] = -(Top + Bottom) * OneByTopMinusBottom;
			OrthographicProjectionMatrix.M[3][2] = -(Far + Near) * OneByFarMinusNear;

			return OrthographicProjectionMatrix;
		}

		FORCEINLINE constexpr static TMatrix44 MakeOrthographicZeroToOne(T Left, T Right, T Bottom, T Top, T Near, T Far) noexcept
		{
			TMatrix44 OrthographicProjectionMatrix(static_cast<T>(1));

			T OneByRightMinusLeft = static_cast<T>(1.0f) / (Right - Left);
			T OneByTopMinusBottom = static_cast<T>(1.0f) / (Top - Bottom);
			T OneByFarMinusNear = static_cast<T>(1.0f) / (Far - Near);

			OrthographicProjectionMatrix.M[0][0] = static_cast<T>(2.0f) * OneByRightMinusLeft;
			OrthographicProjectionMatrix.M[1][1] = static_cast<T>(2.0f) * OneByTopMinusBottom;
			OrthographicProjectionMatrix.M[2][2] = OneByFarMinusNear;
			OrthographicProjectionMatrix.M[3][0] = -(Right + Left) * OneByRightMinusLeft;
			OrthographicProjectionMatrix.M[3][1] = -(Top + Bottom) * OneByTopMinusBottom;
			OrthographicProjectionMatrix.M[3][2] = -Near * OneByFarMinusNear;

			return OrthographicProjectionMatrix;
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