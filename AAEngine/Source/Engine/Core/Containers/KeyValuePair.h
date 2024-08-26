#pragma once

#include "Core/Core.h"

namespace AAEngine {

	template<typename KeyType, typename ValueType>
	class TKeyValuePair
	{
	public:
		FORCEINLINE constexpr TKeyValuePair() noexcept
		{
		}

		FORCEINLINE constexpr TKeyValuePair(const TKeyValuePair& Pair) noexcept
		{
			Key = Pair.Key;
			Value = Pair.Value;
		}

		FORCEINLINE constexpr TKeyValuePair(TKeyValuePair&& Pair) noexcept
		{
			Key = Move(Pair.Key);
			Value = Move(Pair.Value);
		}

		FORCEINLINE constexpr TKeyValuePair(const KeyType& InKey, const ValueType& InValue) noexcept
		{
			Key = InKey;
			Value = InValue;
		}

		FORCEINLINE constexpr TKeyValuePair(KeyType&& InKey, const ValueType& InValue) noexcept
		{
			Key = Move(InKey);
			Value = InValue;
		}

		FORCEINLINE constexpr TKeyValuePair(const KeyType& InKey, ValueType&& InValue) noexcept
		{
			Key = InKey;
			Value = Move(InValue);
		}

		FORCEINLINE constexpr TKeyValuePair(KeyType&& InKey, ValueType&& InValue) noexcept
		{
			Key = Move(InKey);
			Value = Move(InValue);
		}

		FORCEINLINE constexpr TKeyValuePair& operator=(const TKeyValuePair& Pair) noexcept
		{
			Key = Pair.Key;
			Value = Pair.Value;
			return *this;
		}

		FORCEINLINE constexpr TKeyValuePair& operator=(TKeyValuePair&& Pair) noexcept
		{
			Key = Move(Pair.Key);
			Value = Move(Pair.Value);
			return *this;
		}

		FORCEINLINE constexpr bool operator==(const TKeyValuePair& Pair) noexcept
		{
			return Key == Pair.Key && Value == Pair.Value;
		}

		/*FORCEINLINE constexpr const KeyType& Key() const noexcept
		{
			return Key;
		}

		FORCEINLINE constexpr KeyType& Key() noexcept
		{
			return Key;
		}

		FORCEINLINE constexpr const ValueType& Value() const noexcept
		{
			return Value;
		}

		FORCEINLINE constexpr ValueType& Value() noexcept
		{
			return Value;
		}*/

		KeyType Key;
		ValueType Value;
		
		//~TKeyValuePair();
	private:
	};

	template<typename InKey, typename InValue>
	using TPair = TKeyValuePair<InKey, InValue>;
}