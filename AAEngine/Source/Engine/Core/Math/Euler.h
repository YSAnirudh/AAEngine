#pragma once

#include "Core/Core.h"

namespace AAEngine {
namespace Math {

	template<typename T>
	struct TEuler
	{
		static_assert(std::is_floating_point_v<T>, "T must be a floating point type.");
	public:
		/*
		* Pitch = Rotation about X (Right)
		* Yaw = Rotation about Y (Up)
		* Roll = Rotation about Z (Forward)
		*/
		T Roll, Pitch, Yaw;

		AA_ENGINE_API static const TEuler<T> ZeroEuler;

		FORCEINLINE constexpr TEuler() noexcept
			: Roll(static_cast<T>(0.0f)), Pitch(static_cast<T>(0.0f)), Yaw(static_cast<T>(0.0f))
		{
		}

		FORCEINLINE constexpr TEuler(T InEqual) noexcept
			: Roll(InEqual), Pitch(InEqual), Yaw(InEqual)
		{
		}

		FORCEINLINE constexpr TEuler(T Roll, T Pitch, T Yaw) noexcept
			: Roll(Roll), Pitch(Pitch), Yaw(Yaw)
		{
		}

		FORCEINLINE constexpr TEuler(const TEuler& Euler) noexcept
			: Roll(Euler.Roll), Pitch(Euler.Pitch), Yaw(Euler.Yaw)
		{
		}

		FORCEINLINE constexpr TEuler& operator=(const TEuler& Euler) noexcept
		{
			Roll = Euler.Roll; Pitch = Euler.Pitch; Yaw = Euler.Yaw;
			return *this;
		}

		/*
		* Basic Math Operators
		*/

		FORCEINLINE constexpr TEuler<T> operator+(const TEuler<T>& Euler) const noexcept
		{
			return TEuler<T>(Roll + Euler.Roll, Pitch + Euler.Pitch, Yaw + Euler.Yaw);
		}

		FORCEINLINE constexpr TEuler<T> operator+() const noexcept
		{
			return *this;
		}

		FORCEINLINE constexpr TEuler<T>& operator+=(const TEuler<T>& Euler) noexcept
		{
			Roll += Euler.Roll; Pitch += Euler.Pitch; Yaw += Euler.Yaw;
			return *this;
		}

		FORCEINLINE constexpr TEuler<T> operator-(const TEuler<T>& Euler) const noexcept
		{
			return TEuler<T>(Roll - Euler.Roll, Pitch - Euler.Pitch, Yaw - Euler.Yaw);
		}

		FORCEINLINE constexpr TEuler<T> operator-() const noexcept
		{
			return TEuler<T>(-Roll, -Pitch, -Roll);
		}

		FORCEINLINE constexpr TEuler<T>& operator-=(const TEuler<T>& Euler) noexcept
		{
			Roll -= Euler.Roll; Pitch -= Euler.Pitch; Yaw -= Euler.Yaw;
			return *this;
		}

		FORCEINLINE constexpr TEuler<T> operator*(T Value) const noexcept
		{
			return TEuler<T>(Roll * Value, Pitch * Value, Yaw * Value);
		}

		FORCEINLINE constexpr TEuler<T>& operator*=(T Value) noexcept
		{
			Roll *= Value; Pitch *= Value; Yaw *= Value;
			return *this;
		}

		FORCEINLINE constexpr TEuler<T> operator/(T Value) const
		{
			return TEuler<T>(Roll / Value, Pitch / Value, Yaw / Value);
		}

		FORCEINLINE constexpr TEuler<T>& operator/=(T Value)
		{
			Roll /= Value; Pitch /= Value; Yaw /= Value;
			return *this;
		}
	};
}
}