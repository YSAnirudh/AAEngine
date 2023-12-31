#pragma once

namespace AAEngine {
namespace Math {

	template<typename T>
	struct alignas(16) TQuaternion
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

		FORCEINLINE constexpr TQuaternion() noexcept
			: X(static_cast<T>(0.0f)), Y(static_cast<T>(0.0f)), Z(static_cast<T>(0.0f)), W(static_cast<T>(0.0f))
		{}

		FORCEINLINE constexpr TQuaternion(T InVal) noexcept
			: X(InVal), Y(InVal), Z(InVal), W(InVal)
		{}

		FORCEINLINE constexpr TQuaternion(T InX, T InY, T InZ, T InW) noexcept
			: X(InX), Y(InY), Z(InZ), W(InW)
		{}

		FORCEINLINE constexpr TQuaternion(T InX, T InY, T InZ) noexcept
			: X(InX), Y(InY), Z(InZ), W(static_cast<T>(0.0f))
		{}

		FORCEINLINE constexpr TQuaternion(const TQuaternion<T>& NewQuat) noexcept
		{
			X = NewQuat.X;
			Y = NewQuat.Y;
			Z = NewQuat.Z;
			W = NewQuat.W;
		}

		FORCEINLINE constexpr TQuaternion<T>& operator=(const TQuaternion<T>& NewQuat) noexcept
		{
			X = NewQuat.X;
			Y = NewQuat.Y;
			Z = NewQuat.Z;
			W = NewQuat.W;
			return *this;
		}
	};
}
}