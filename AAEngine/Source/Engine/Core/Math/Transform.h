#pragma once

#include "Math/Vector3.h"
#include "Math/Euler.h"

namespace AAEngine {
namespace Math {

	template<typename T>
	struct alignas(16) TTransform
	{
		static_assert(std::is_floating_point_v<T>, "T must be a floating point type.");
	public:
		union
		{
			struct
			{
				TVector3<T> Location;
				TEuler<T> Rotation;
				TVector3<T> Scale;
			};
		};

		FORCEINLINE constexpr TTransform() noexcept
			: X(static_cast<T>(0.0f)), Y(static_cast<T>(0.0f)), Z(static_cast<T>(0.0f)), W(static_cast<T>(0.0f))
		{}

		FORCEINLINE constexpr TTransform(const TVector3<T>& InVec, const TEuler<T>& InEuler = TEuler<T>::ZeroEuler, const TVector3<T>& InScale = TVector3<T>::OneVector) noexcept
			: Location(InVec)
		{}

		FORCEINLINE constexpr TTransform(const TEuler<T>& InEuler) noexcept
			: Rotation(InEuler)
		{}

		FORCEINLINE constexpr TTransform(const TVector3<T>& InScale) noexcept
			: Scale(InVec)
		{}

		FORCEINLINE constexpr TTransform(const TTransform<T>& NewTransform) noexcept
		{
			Location = NewTransform.Location;
			Rotation = NewTransform.Rotation;
			Scale = NewTransform.Scale;
		}

		FORCEINLINE constexpr TTransform<T>& operator=(const TTransform<T>& NewVector) noexcept
		{
			Location = NewTransform.Location;
			Rotation = NewTransform.Rotation;
			Scale = NewTransform.Scale;
			return *this;
		}
	};

}
}