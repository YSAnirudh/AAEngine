#pragma once

#include "Core/Core.h"
#include "Core/Math/Math.h"

#include <type_traits>

namespace AAEngine {
	namespace Math {

		template<typename T>
		struct TVector3
		{
			static_assert(std::is_floating_point_v<T>, "T must be a floating point type.");
		public:
			union
			{
				struct
				{
					T X, Y, Z;
				};
				T XYZ[3];
			};

			AA_ENGINE_API static const TVector3<T> ZeroVector;
			AA_ENGINE_API static const TVector3<T> OneVector;

			FORCEINLINE constexpr TVector3() noexcept
				: X(static_cast<T>(0.0f)), Y(static_cast<T>(0.0f)), Z(static_cast<T>(0.0f))
			{}

			FORCEINLINE constexpr TVector3(T InVal) noexcept
				: X(InVal), Y(InVal), Z(InVal)
			{}

			FORCEINLINE constexpr TVector3(T InX, T InY, T InZ) noexcept
				: X(InX), Y(InY), Z(InZ)
			{}

			FORCEINLINE constexpr TVector3(const TVector3<T>& NewVector) noexcept
			{
				X = NewVector.X;
				Y = NewVector.Y;
				Z = NewVector.Z;
			}

			FORCEINLINE constexpr TVector3<T>& operator=(const TVector3<T>& NewVector) noexcept
			{
				X = NewVector.X;
				Y = NewVector.Y;
				Z = NewVector.Z;
				return *this;
			}

			/*
			* Basic Math Operators
			*/

			FORCEINLINE constexpr TVector3<T> operator+(const TVector3<T>& Vec) const noexcept
			{
				return TVector3<T>(X + Vec.X, Y + Vec.Y, Z + Vec.Z);
			}

			FORCEINLINE constexpr TVector3<T> operator+(T Value) const noexcept
			{
				return TVector3<T>(X + Value, Y + Value, Z + Value);
			}

			FORCEINLINE constexpr TVector3<T> operator+() const noexcept
			{
				return *this;
			}

			FORCEINLINE constexpr TVector3<T>& operator+=(const TVector3<T>& Vec) noexcept
			{
				X += Vec.X; Y += Vec.Y; Z += Vec.Z;
				return *this;
			}

			FORCEINLINE constexpr TVector3<T>& operator+=(T Value) noexcept
			{
				X += Value; Y += Value; Z += Value;
				return *this;
			}

			FORCEINLINE constexpr TVector3<T> operator-(const TVector3<T>& Vec) const noexcept
			{
				return TVector3<T>(X - Vec.X, Y - Vec.Y, Z - Vec.Z);
			}

			FORCEINLINE constexpr TVector3<T> operator-(T Value) const noexcept
			{
				return TVector3<T>(X - Value, Y - Value, Z - Value);
			}

			FORCEINLINE constexpr TVector3<T> operator-() const noexcept
			{
				return TVector3<T>(-X, -Y, -Z);
			}

			FORCEINLINE constexpr TVector3<T>& operator-=(const TVector3<T>& Vec) noexcept
			{
				X -= Vec.X; Y -= Vec.Y; Z -= Vec.Z;
				return *this;
			}

			FORCEINLINE constexpr TVector3<T>& operator-=(T Value) noexcept
			{
				X -= Value; Y -= Value; Z -= Value;
				return *this;
			}

			FORCEINLINE constexpr TVector3<T> operator*(const TVector3<T>& Vec) const noexcept
			{
				return TVector3<T>(X * Vec.X, Y * Vec.Y, Z * Vec.Z);
			}

			FORCEINLINE constexpr TVector3<T> operator*(T Value) const noexcept
			{
				return TVector3<T>(X * Value, Y * Value, Z * Value);
			}

			FORCEINLINE constexpr TVector3<T>& operator*=(const TVector3<T>& Vec) noexcept
			{
				X *= Vec.X; Y *= Vec.Y; Z *= Vec.Z;
				return *this;
			}

			FORCEINLINE constexpr TVector3<T>& operator*=(T Value) noexcept
			{
				X *= Value; Y *= Value; Z *= Value;
				return *this;
			}

			FORCEINLINE constexpr TVector3<T> operator/(const TVector3<T>& Vec) const noexcept
			{
				return TVector3<T>(X / Vec.X, Y / Vec.Y, Z / Vec.Z);
			}

			FORCEINLINE constexpr TVector3<T> operator/(T Value) const noexcept
			{
				return TVector3<T>(X / Value, Y / Value, Z / Value);
			}

			FORCEINLINE constexpr TVector3<T>& operator/=(const TVector3<T>& Vec) noexcept
			{
				X /= Vec.X; Y /= Vec.Y; Z /= Vec.Z;
				return *this;
			}

			FORCEINLINE constexpr TVector3<T>& operator/=(T Value) noexcept
			{
				X /= Value; Y /= Value; Z /= Value;
				return *this;
			}

			/*
			* Comparision Operators
			*/
			FORCEINLINE constexpr bool operator==(const TVector3<T> Vec) const noexcept
			{
				return X == Vec.X && Y == Vec.Y && Z == Vec.Z;
			}
			FORCEINLINE constexpr bool operator==(T Value) const noexcept
			{
				return X == Value && Y == Value && Z == Value;
			}

			FORCEINLINE constexpr bool operator!=(const TVector3<T> Vec) const noexcept
			{
				return X != Vec.X || Y != Vec.Y || Z != Vec.Z;
			}
			FORCEINLINE constexpr bool operator!=(T Value) const noexcept
			{
				return X != Value || Y != Value || Z != Value;
			}

			/*
			* Index Operators
			*/

			FORCEINLINE constexpr T& operator[](int Index)
			{
				AA_CORE_ASSERT(Index >= 0 && Index < 3, "Cannot access Vector4 with %d Index", Index);
				return XYZ[Index];
			}

			FORCEINLINE constexpr const T& operator[](int Index) const
			{
				AA_CORE_ASSERT(Index >= 0 && Index < 3, "Cannot access Vector4 with %d Index", Index);
				return XYZ[Index];
			}

			/*
			* Basic Vector Operations
			*/

			FORCEINLINE constexpr T Dot(const TVector3<T>& Vec) const noexcept
			{
				return X * Vec.X + Y * Vec.Y + Z * Vec.Z;
			}

			FORCEINLINE constexpr T operator|(const TVector3<T>& Vec) const noexcept
			{
				return Dot(Vec);
			}

			FORCEINLINE constexpr TVector3<T> Cross(const TVector3<T>& Vec) const noexcept
			{
				return TVector3<T>
					(
						Y * Vec.Z - Z * Vec.Y,
						-(X * Vec.Z - Z * Vec.X),
						X * Vec.Y - Y * Vec.X
					);
			}

			FORCEINLINE constexpr TVector3<T> operator^(const TVector3<T>& Vec) const noexcept
			{
				return Cross(Vec);
			}

			// Vector 3
			/*FORCEINLINE constexpr T Dot(const TVector3& ToDot3Vector) noexcept
			{
				T Result = X * ToDotVector.X + Y * ToDotVector.Y + Z * ToDotVector.Z;
				return Result;
			}*/

			FORCEINLINE constexpr bool IsZero() const noexcept
			{
				return *this == static_cast<T>(0.0f);
			}

			FORCEINLINE constexpr bool IsNearlyZero(T Tolerance = AA_SMALL_NUMBER) const noexcept
			{
				return FMath::Abs(X) < Tolerance && FMath::Abs(Y) < Tolerance && FMath::Abs(Z) < Tolerance;
			}

			FORCEINLINE constexpr bool IsNormalized(T Tolerance = AA_SMALL_NUMBER) const noexcept
			{
				return FMath::Abs(static_cast<T>(0.0f) - Size()) < Tolerance;
			}

			FORCEINLINE constexpr bool Normalize(T Tolerance = AA_SMALL_NUMBER) const noexcept
			{
				T SumSquared = X * X + Y * Y + Z * Z;
				if (SumSquared > Tolerance)
				{
					*this *= FMath::InvSqrt(SumSquared);
					return true;
				}
				return false;
			}

			FORCEINLINE constexpr TVector3<T> GetSafeNormal(T Tolerance = AA_SMALL_NUMBER) const noexcept
			{
				T SumSquared = X * X + Y * Y + Z * Z;
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
				return X * X + Y * Y + Z * Z;
			}

			FORCEINLINE constexpr T Magnitude() const noexcept
			{
				return FMath::Sqrt(MagnitudeSquared());
			}

			FORCEINLINE constexpr T SizeSquared() const noexcept
			{
				return X * X + Y * Y + Z * Z;
			}

			FORCEINLINE constexpr T Size() const noexcept
			{
				return FMath::Sqrt(SizeSquared());
			}

			FORCEINLINE constexpr T Max() const noexcept
			{
				return FMath::Max(FMath::Max(X, Y), Z);
			}

			FORCEINLINE constexpr T Min() const noexcept
			{
				return FMath::Min(FMath::Min(X, Y), Z);
			}

			FORCEINLINE constexpr T MaxAbs() const noexcept
			{
				return FMath::Max(FMath::Max(FMath::Abs(X), FMath::Abs(Y)), FMath::Abs(Z));
			}

			FORCEINLINE constexpr T MinAbs() const noexcept
			{
				return FMath::Min(FMath::Min(FMath::Abs(X), FMath::Abs(Y)), FMath::Abs(Z));
			}

			FORCEINLINE constexpr TVector3<T> GetAbs() const noexcept
			{
				return TVector3<T>(FMath::Abs(X), FMath::Abs(Y), FMath::Abs(Z));
			}

			FORCEINLINE constexpr std::string ToString() const noexcept
			{
				std::stringstream SS;
				SS << "X: " << X << ", Y: " << Y << ", Z: " << Z;
				return SS.str();
			}

			template<typename T>
			FORCEINLINE static constexpr T DotProduct(const TVector3<T>& Vec1, const TVector3<T>& Vec2) noexcept
			{
				return Vec1 | Vec2;
			}

			template<typename T>
			FORCEINLINE static constexpr TVector3<T> CrossProduct(const TVector3<T>& Vec1, const TVector3<T>& Vec2) noexcept
			{
				return Vec1 ^ Vec2;
			}

			template<typename T>
			FORCEINLINE static constexpr T Distance(const TVector3<T>& Vec1, const TVector3<T>& Vec2) noexcept
			{
				return (Vec1 - Vec2).Size();
			}

			FORCEINLINE static constexpr bool AreNearlyEqual(const TVector3<T>& Vec1, const TVector3<T>& Vec2, T Tolerance = AA_SMALL_NUMBER) noexcept
			{
				return FMath::Abs(Vec1.X - Vec2.X) < Tolerance && FMath::Abs(Vec1.Y - Vec2.Y) < Tolerance && FMath::Abs(Vec1.Z - Vec2.Z) < Tolerance;
			}
		};

		template<typename T>
		FORCEINLINE static constexpr TVector3<T> operator*(T Val, const TVector3<T>& Vec) noexcept
		{
			return Vec * Val;
		}
	}
}