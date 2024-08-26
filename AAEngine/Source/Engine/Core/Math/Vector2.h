#pragma once

#include "Core/Core.h"
#include "Core/Math/Math.h"

#include <type_traits>

namespace AAEngine {
	namespace Math {

		template<typename T>
		struct TVector2
		{
			static_assert(std::is_floating_point_v<T>, "T must be a floating point type.");
		public:
			union
			{
				struct
				{
					T X, Y;
				};
				T XY[2];
			};

			AA_ENGINE_API static const TVector2<T> ZeroVector;
			AA_ENGINE_API static const TVector2<T> OneVector;

			FORCEINLINE constexpr TVector2() noexcept
				: X(static_cast<T>(0.0f)), Y(static_cast<T>(0.0f))
			{}

			FORCEINLINE constexpr TVector2(T InVal) noexcept
				: X(InVal), Y(InVal)
			{}

			FORCEINLINE constexpr TVector2(T InX, T InY) noexcept
				: X(InX), Y(InY)
			{}

			FORCEINLINE constexpr TVector2(const TVector2<T>& NewVector) noexcept
			{
				X = NewVector.X;
				Y = NewVector.Y;
			}

			FORCEINLINE constexpr TVector2<T>& operator=(const TVector2<T>& NewVector) noexcept
			{
				X = NewVector.X;
				Y = NewVector.Y;
				return *this;
			}

			/*
			* Basic Math Operators
			*/

			FORCEINLINE constexpr TVector2<T> operator+(const TVector2<T>& Vec) const noexcept
			{
				return TVector2<T>(X + Vec.X, Y + Vec.Y);
			}

			FORCEINLINE constexpr TVector2<T> operator+(T Value) const noexcept
			{
				return TVector2<T>(X + Value, Y + Value);
			}

			FORCEINLINE constexpr TVector2<T> operator+() const noexcept
			{
				return *this;
			}

			FORCEINLINE constexpr TVector2<T>& operator+=(const TVector2<T>& Vec) noexcept
			{
				X += Vec.X; Y += Vec.Y;
				return *this;
			}

			FORCEINLINE constexpr TVector2<T>& operator+=(T Value) noexcept
			{
				X += Value; Y += Value;
				return *this;
			}

			FORCEINLINE constexpr TVector2<T> operator-(const TVector2<T>& Vec) const noexcept
			{
				return TVector2<T>(X - Vec.X, Y - Vec.Y);
			}

			FORCEINLINE constexpr TVector2<T> operator-(T Value) const noexcept
			{
				return TVector2<T>(X - Value, Y - Value);
			}

			FORCEINLINE constexpr TVector2<T> operator-() const noexcept
			{
				return TVector2<T>(-X, -Y);
			}

			FORCEINLINE constexpr TVector2<T>& operator-=(const TVector2<T>& Vec) noexcept
			{
				X -= Vec.X; Y -= Vec.Y;
				return *this;
			}

			FORCEINLINE constexpr TVector2<T>& operator-=(T Value) noexcept
			{
				X -= Value; Y -= Value;
				return *this;
			}

			FORCEINLINE constexpr TVector2<T> operator*(const TVector2<T>& Vec) const noexcept
			{
				return TVector2<T>(X * Vec.X, Y * Vec.Y);
			}

			FORCEINLINE constexpr TVector2<T> operator*(T Value) const noexcept
			{
				return TVector2<T>(X * Value, Y * Value);
			}

			FORCEINLINE constexpr TVector2<T>& operator*=(const TVector2<T>& Vec) noexcept
			{
				X *= Vec.X; Y *= Vec.Y;
				return *this;
			}

			FORCEINLINE constexpr TVector2<T>& operator*=(T Value) noexcept
			{
				X *= Value; Y *= Value;
				return *this;
			}

			FORCEINLINE constexpr TVector2<T> operator/(const TVector2<T>& Vec) const noexcept
			{
				return TVector2<T>(X / Vec.X, Y / Vec.Y);
			}

			FORCEINLINE constexpr TVector2<T> operator/(T Value) const noexcept
			{
				return TVector2<T>(X / Value, Y / Value);
			}

			FORCEINLINE constexpr TVector2<T>& operator/=(const TVector2<T>& Vec) noexcept
			{
				X /= Vec.X; Y /= Vec.Y;
				return *this;
			}

			FORCEINLINE constexpr TVector2<T>& operator/=(T Value) noexcept
			{
				X /= Value; Y /= Value;
				return *this;
			}

			/*
			* Comparision Operators
			*/
			FORCEINLINE constexpr bool operator==(const TVector2<T> Vec) const noexcept
			{
				return X == Vec.X && Y == Vec.Y;
			}
			FORCEINLINE constexpr bool operator==(T Value) const noexcept
			{
				return X == Value && Y == Value;
			}

			FORCEINLINE constexpr bool operator!=(const TVector2<T> Vec) const noexcept
			{
				return X != Vec.X || Y != Vec.Y;
			}
			FORCEINLINE constexpr bool operator!=(T Value) const noexcept
			{
				return X != Value || Y != Value;
			}

			/*
			* Index Operators
			*/

			FORCEINLINE constexpr T& operator[](int Index)
			{
				AA_CORE_ASSERT(Index >= 0 && Index < 2, "Cannot access Vector2 with %d Index", Index);
				return XY[Index];
			}

			FORCEINLINE constexpr const T& operator[](int Index) const
			{
				AA_CORE_ASSERT(Index >= 0 && Index < 2, "Cannot access Vector2 with %d Index", Index);
				return XY[Index];
			}

			/*
			* Basic Vector Operations
			*/

			FORCEINLINE constexpr T Dot(const TVector2<T>& Vec) const noexcept
			{
				return X * Vec.X + Y * Vec.Y;
			}

			FORCEINLINE constexpr T operator|(const TVector2<T>& Vec) const noexcept
			{
				return Dot(Vec);
			}

			/*FORCEINLINE constexpr TVector2<T> Cross(const TVector2<T> Vec) noexcept
			{
				return TVector2<T>
					(
						Y * Vec.Z - Z * Vec.Y,
						-(X * Vec.Z - Z * Vec.X),
						Y * Vec.X - X * Vec.Y
					);
			}

			FORCEINLINE constexpr TVector2<T> operator^(const TVector2<T>& Vec) const noexcept
			{
				return Cross(Vec);
			}*/

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
				return FMath::Abs(X) < Tolerance && FMath::Abs(Y) < Tolerance;
			}

			FORCEINLINE constexpr bool IsNormalized(T Tolerance = AA_SMALL_NUMBER) const noexcept
			{
				return FMath::Abs(static_cast<T>(0.0f) - Size()) < Tolerance;
			}

			FORCEINLINE constexpr bool Normalize(T Tolerance = AA_SMALL_NUMBER) const noexcept
			{
				T SumSquared = X * X + Y * Y;
				if (SumSquared > Tolerance)
				{
					*this *= FMath::InvSqrt(SumSquared);
					return true;
				}
				return false;
			}

			FORCEINLINE constexpr TVector2<T> GetSafeNormal(T Tolerance = AA_SMALL_NUMBER) const noexcept
			{
				T SumSquared = X * X + Y * Y;
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
				return X * X + Y * Y;
			}

			FORCEINLINE constexpr T Magnitude() const noexcept
			{
				return FMath::Sqrt(MagnitudeSquared());
			}

			FORCEINLINE constexpr T SizeSquared() const noexcept
			{
				return X * X + Y * Y;
			}

			FORCEINLINE constexpr T Size() const noexcept
			{
				return FMath::Sqrt(SizeSquared());
			}

			FORCEINLINE constexpr T Max() const noexcept
			{
				return FMath::Max(X, Y);
			}

			FORCEINLINE constexpr T Min() const noexcept
			{
				return FMath::Min(X, Y);
			}

			FORCEINLINE constexpr T MaxAbs() const noexcept
			{
				return FMath::Max(FMath::Abs(X), FMath::Abs(Y));
			}

			FORCEINLINE constexpr T MinAbs() const noexcept
			{
				return FMath::Min(FMath::Abs(X), FMath::Abs(Y));
			}

			FORCEINLINE constexpr TVector2<T> GetAbs() const noexcept
			{
				return TVector2<T>(FMath::Abs(X), FMath::Abs(Y));
			}

			FORCEINLINE constexpr std::string ToString() const noexcept
			{
				std::stringstream SS;
				SS << "X: " << X << ", Y: " << Y;
				return SS.str();
			}
		};

		template<typename T>
		FORCEINLINE constexpr T DotProduct(const TVector2<T>& Vec1, const TVector2<T>& Vec2) noexcept
		{
			return Vec1 | Vec2;
		}

		/*template<typename T>
		FORCEINLINE constexpr TVector2<T> CrossProduct(const TVector2<T>& Vec1, const TVector2<T>& Vec2) noexcept
		{
			return Vec1 ^ Vec2;
		}*/

		template<typename T>
		FORCEINLINE constexpr T Distance(const TVector2<T>& Vec1, const TVector2<T>& Vec2) noexcept
		{
			return (Vec1 - Vec2).Size();
		}

		template<typename T>
		FORCEINLINE constexpr TVector2<T> operator*(T Val, const TVector2<T>& Vec) noexcept
		{
			return Vec * Val;
		}
	}
}