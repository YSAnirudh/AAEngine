#pragma once

#include "Core/Core.h"
#include "Core/Math/Math.h"
#include "Math/Vector3.h"

#include "Math/VectorRegister.h"

#include <type_traits>

namespace AAEngine {
namespace Math {

	/*
	* TO DO:
	* - SIMD support
	* - Angle Between Vectors
	* - Projections
	*/

	template<typename T>
	struct alignas(16) TVector4
	{
		static_assert(std::is_floating_point_v<T>, "T must be a floating point type.");
	public:
		union
		{
			T XYZW[4];
			struct
			{
				T X;
				T Y;
				T Z;
				T W;
			};
		};

		AA_ENGINE_API static const TVector4<T> ZeroVector;
		AA_ENGINE_API static const TVector4<T> OneVector;

		FORCEINLINE constexpr TVector4() noexcept
			: X(static_cast<T>(0.0f)), Y(static_cast<T>(0.0f)), Z(static_cast<T>(0.0f)), W(static_cast<T>(0.0f))
		{}

		FORCEINLINE constexpr TVector4(T InVal) noexcept
			: X(InVal), Y(InVal), Z(InVal), W(InVal)
		{}

		FORCEINLINE constexpr TVector4(T InX, T InY, T InZ, T InW) noexcept
			: X(InX), Y(InY), Z(InZ), W(InW)
		{}

		FORCEINLINE constexpr TVector4(T InX, T InY, T InZ) noexcept
			: X(InX), Y(InY), Z(InZ), W(static_cast<T>(0.0f))
		{}

		FORCEINLINE constexpr TVector4(const TVector4<T>& NewVector) noexcept
		{
			X = NewVector.X;
			Y = NewVector.Y;
			Z = NewVector.Z;
			W = NewVector.W;
		}

		FORCEINLINE constexpr TVector4<T>& operator=(const TVector4<T>& NewVector) noexcept
		{
			X = NewVector.X;
			Y = NewVector.Y;
			Z = NewVector.Z;
			W = NewVector.W;
			return *this;
		}
		
		/*
		* Basic Math Operators
		*/

		FORCEINLINE constexpr TVector4<T> operator+(const TVector4<T>& Vec) const noexcept
		{
			return TVector4<T>(X + Vec.X, Y + Vec.Y, Z + Vec.Z, W + Vec.W);
		}

		FORCEINLINE constexpr TVector4<T> operator+(T Value) const noexcept
		{
			return TVector4<T>(X + Value, Y + Value, Z + Value, W + Value);
		}

		FORCEINLINE constexpr TVector4<T> operator+() const noexcept
		{
			return *this;
		}

		FORCEINLINE constexpr TVector4<T>& operator+=(const TVector4<T>& Vec) noexcept
		{
			X += Vec.X; Y += Vec.Y; Z += Vec.Z; W += Vec.W;
			return *this;
		}

		FORCEINLINE constexpr TVector4<T>& operator+=(T Value) noexcept
		{
			X += Value; Y += Value; Z += Value; W += Value;
			return *this;
		}

		FORCEINLINE constexpr TVector4<T> operator-(const TVector4<T>& Vec) const noexcept
		{
			return TVector4<T>(X - Vec.X, Y - Vec.Y, Z - Vec.Z, W - Vec.W);
		}

		FORCEINLINE constexpr TVector4<T> operator-(T Value) const noexcept
		{
			return TVector4<T>(X - Value, Y - Value, Z - Value, W - Value);
		}

		FORCEINLINE constexpr TVector4<T> operator-() const noexcept
		{
			return TVector4<T>(-X, -Y, -Z, -W);
		}

		FORCEINLINE constexpr TVector4<T>& operator-=(const TVector4<T>& Vec) noexcept
		{
			X -= Vec.X; Y -= Vec.Y; Z -= Vec.Z; W -= Vec.W;
			return *this;
		}

		FORCEINLINE constexpr TVector4<T>& operator-=(T Value) noexcept
		{
			X -= Value; Y -= Value; Z -= Value; W -= Value;
			return *this;
		}

		FORCEINLINE constexpr TVector4<T> operator*(const TVector4<T>& Vec) const noexcept
		{
			return TVector4<T>(X * Vec.X, Y * Vec.Y, Z * Vec.Z, W * Vec.W);
		}

		FORCEINLINE constexpr TVector4<T> operator*(T Value) const noexcept
		{
			return TVector4<T>(X * Value, Y * Value, Z * Value, W * Value);
		}

		FORCEINLINE constexpr TVector4<T>& operator*=(const TVector4<T>& Vec) noexcept
		{
			X *= Vec.X; Y *= Vec.Y; Z *= Vec.Z; W *= Vec.W;
			return *this;
		}

		FORCEINLINE constexpr TVector4<T>& operator*=(T Value) noexcept
		{
			X *= Value; Y *= Value; Z *= Value; W *= Value;
			return *this;
		}

		FORCEINLINE constexpr TVector4<T> operator/(const TVector4<T>& Vec) const noexcept
		{
			return TVector4<T>(X / Vec.X, Y / Vec.Y, Z / Vec.Z, W / Vec.W);
		}

		FORCEINLINE constexpr TVector4<T> operator/(T Value) const noexcept
		{
			return TVector4<T>(X / Value, Y / Value, Z / Value, W / Value);
		}

		FORCEINLINE constexpr TVector4<T>& operator/=(const TVector4<T>& Vec) noexcept
		{
			X /= Vec.X; Y /= Vec.Y; Z /= Vec.Z; W /= Vec.W;
			return *this;
		}

		FORCEINLINE constexpr TVector4<T>& operator/=(T Value) noexcept
		{
			X /= Value; Y /= Value; Z /= Value; W /= Value;
			return *this;
		}

		/*
		* Comparision Operators
		*/
		FORCEINLINE constexpr bool operator==(const TVector4<T> Vec) const noexcept
		{
			return X == Vec.X && Y == Vec.Y && Z == Vec.Z && W == Vec.W;
		}
		FORCEINLINE constexpr bool operator==(T Value) const noexcept
		{
			return X == Value && Y == Value && Z == Value && W == Value;
		}

		FORCEINLINE constexpr bool operator!=(const TVector4<T> Vec) const noexcept
		{
			return X != Vec.X || Y != Vec.Y || Z != Vec.Z || W != Vec.W;
		}
		FORCEINLINE constexpr bool operator!=(T Value) const noexcept
		{
			return X != Value || Y != Value || Z != Value || W != Value;
		}

		/*
		* Index Operators
		*/

		FORCEINLINE constexpr T& operator[](int Index)
		{
			//AA_CORE_ASSERT(Index >= 0 && Index < 4, "Cannot access Vector4 with %d Index", Index);
			return XYZW[Index];
		}

		FORCEINLINE constexpr const T& operator[](int Index) const
		{
			//AA_CORE_ASSERT(Index >= 0 && Index < 4, "Cannot access Vector4 with %d Index", Index);
			return XYZW[Index];
		}

		/*
		* Basic Vector Operations
		*/

		FORCEINLINE constexpr T Dot(const TVector4<T>& Vec) const noexcept
		{
			return X * Vec.X + Y * Vec.Y + Z * Vec.Z + W * Vec.W;
		}

		FORCEINLINE constexpr T Dot3(const TVector4<T>& Vec) const noexcept
		{
			return X * Vec.X + Y * Vec.Y + Z * Vec.Z;
		}

		FORCEINLINE constexpr T operator|(const TVector4<T>& Vec) const noexcept
		{
			return Dot(Vec);
		}

		FORCEINLINE constexpr T Dot(const TVector3<T>& Vec) noexcept
		{
			return X * Vec.X + Y * Vec.Y + Z * Vec.Z;
		}

		FORCEINLINE constexpr bool IsZero() const noexcept
		{
			return *this == static_cast<T>(0.0f);
		}

		FORCEINLINE constexpr bool IsNearlyZero(T Tolerance = AA_SMALL_NUMBER) const noexcept
		{
			return FMath::Abs(X) < Tolerance && FMath::Abs(Y) < Tolerance && FMath::Abs(Z) < Tolerance && FMath::Abs(W) < Tolerance;
		}

		FORCEINLINE constexpr bool IsNormalized(T Tolerance = AA_SMALL_NUMBER) const noexcept
		{
			return FMath::Abs(static_cast<T>(0.0f) - Size()) < Tolerance;
		}

		FORCEINLINE constexpr bool Normalize(T Tolerance = AA_SMALL_NUMBER) const noexcept
		{
			T SumSquared = X * X + Y * Y + Z * Z + W * W;
			if (SumSquared > Tolerance)
			{
				*this *= FMath::InvSqrt(SumSquared);
				return true;
			}
			return false;
		}

		FORCEINLINE constexpr TVector4<T> GetSafeNormal(T Tolerance = AA_SMALL_NUMBER) const noexcept
		{
			T SumSquared = X * X + Y * Y + Z * Z + W * W;
			if (SumSquared == static_cast<T>(0.0f))
			{
				return *this;
			}
			else if (SumSquared > Tolerance)
			{
				return *this * FMath::InvSqrt(SumSquared);
			}
			return OneVector;
		}

		FORCEINLINE constexpr T MagnitudeSquared() const noexcept
		{
			return X * X + Y * Y + Z * Z + W * W;
		}

		FORCEINLINE constexpr T Magnitude() const noexcept
		{
			return FMath::Sqrt(MagnitudeSquared());
		}

		FORCEINLINE constexpr T SizeSquared() const noexcept
		{
			return X * X + Y * Y + Z * Z + W * W;
		}

		FORCEINLINE constexpr T Size() const noexcept
		{
			return FMath::Sqrt(SizeSquared());
		}

		FORCEINLINE constexpr T Max() const noexcept
		{
			return FMath::Max(FMath::Max(X, Y), FMath::Max(Z, W));
		}

		FORCEINLINE constexpr T Min() const noexcept
		{
			return FMath::Min(FMath::Min(X, Y), FMath::Min(Z, W));
		}

		FORCEINLINE constexpr T MaxAbs() const noexcept
		{
			return FMath::Max(FMath::Max(FMath::Abs(X), FMath::Abs(Y)), FMath::Max(FMath::Abs(Z), FMath::Abs(W)));
		}

		FORCEINLINE constexpr T MinAbs() const noexcept
		{
			return FMath::Min(FMath::Min(FMath::Abs(X), FMath::Abs(Y)), FMath::Min(FMath::Abs(Z), FMath::Abs(W)));
		}

		FORCEINLINE constexpr TVector4<T> GetAbs() const noexcept
		{
			return TVector4<T>(FMath::Abs(X), FMath::Abs(Y), FMath::Abs(Z), FMath::Abs(W));
		}

		FORCEINLINE constexpr std::string ToString() const noexcept
		{
			std::stringstream SS;
			SS << "X: " << X << ", Y: " << Y << ", Z: " << Z << ", W: " << W;
			return SS.str();
		}
	};

	template<typename T>
	FORCEINLINE constexpr T DotProduct(const TVector4<T>& Vec1, const TVector4<T>& Vec2) noexcept
	{
		return Vec1 | Vec2;
	}

	template<typename T>
	FORCEINLINE constexpr T Distance(const TVector4<T>& Vec1, const TVector4<T>& Vec2) noexcept
	{
		return (Vec1 - Vec2).Size();
	}

	template<typename T>
	FORCEINLINE constexpr TVector4<T> operator*(T Val, const TVector4<T>& Vec) noexcept
	{
		return Vec * Val;
	}

}
}