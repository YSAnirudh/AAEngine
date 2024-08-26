#pragma once

#include "Core.h"
#include <initializer_list>

namespace AAEngine {

	/*
	* Class representing a static array in the engine
	* 
	* @tparam DataType - The type of elements stored in the array
	* @tparam Size - The size of the array
	*/
	template<typename DataType, size_t Size>
	class AA_ENGINE_API TStaticArray
	{
	public:
		/*
		* Default constructor for the TStaticArray class
		*/
		FORCEINLINE constexpr TStaticArray() noexcept
		{
		}

		/*
		* Copy constructor for the TStaticArray class
		*/
		FORCEINLINE constexpr TStaticArray(const TStaticArray& Array) noexcept
		{
			if (Array.Num() != Num()) 
			{
				return;
			}
			for (int i = 0; i < Num(); i++)
			{
				InternalArray[i] = Array[i];
			}
		}

		/*
		* Move constructor for the TStaticArray class
		*/
		FORCEINLINE constexpr TStaticArray(TStaticArray&& Array) noexcept
		{
			if (Array.Num() != Num())
			{
				return;
			}
			for (int i = 0; i < Num(); i++)
			{
				InternalArray[i] = Move(Array[i]);
			}
		}

		/*
		* Copy assignment operator for the TStaticArray class
		*/
		FORCEINLINE constexpr TStaticArray& operator=(const TStaticArray& Array) noexcept
		{
			if (Array.Num() != Num())
			{
				return *this;
			}
			for (int i = 0; i < Num(); i++)
			{
				InternalArray[i] = Array[i];
			}
			return *this;
		}

		/*
		* Move assignment operator for the TStaticArray class
		*/
		FORCEINLINE constexpr TStaticArray& operator=(TStaticArray&& Array) noexcept
		{
			if (Array.Num() != Num())
			{
				return *this;
			}
			for (int i = 0; i < Num(); i++)
			{
				InternalArray[i] = Move(Array[i]);
			}
			return *this;
		}

		/*
		* Overloaded operator [] to access elements of the array
		* 
		* @param Index - Index of the element to be accessed
		* 
		* @returns Reference to the element at the specified index
		*/
		FORCEINLINE constexpr DataType& operator[](size_t Index) noexcept
		{
			AA_CORE_ASSERT(int(Index < Size), "Index Out of Bounds: %d when Size is %d", Index, Size);
			return InternalArray[Index];
		}

		/*
		* Overloaded operator [] to access elements of the array (const version)
		*
		* @param Index - Index of the element to be accessed
		*
		* @returns Reference to the element at the specified index
		*/
		FORCEINLINE constexpr const DataType& operator[](size_t Index) const noexcept
		{
			AA_CORE_ASSERT(int(Index < Size), "Index Out of Bounds: %d when Size is %d", Index, Size);
			return InternalArray[Index];
		}

		/*
		* Returns the size of the static array.
		* @returns The size of the array.
		*/
		FORCEINLINE constexpr size_t Num() const noexcept
		{
			return Size;
		}

		/*
		* Checks if the static array is empty.
		*
		* @returns True if the array is empty, false otherwise.
		*/
		FORCEINLINE constexpr bool IsEmpty() const noexcept
		{
			return Size == 0;
		}

		/*
		* Retrieves a Pointer to the first element in the array (non-const version).
		*
		* @returns Pointer to the first element.
		*/
		FORCEINLINE constexpr DataType* Data() noexcept
		{
			return InternalArray;
		}

		/*
		* Retrieves a Pointer to the first element in the array (const version).
		*
		* @returns Const Pointer to the first element.
		*/
		FORCEINLINE constexpr const DataType* Data() const noexcept
		{
			return InternalArray;
		}

		/*
		* Retrieves a reference to the front element in the array (non-const version).
		*
		* @returns Reference to the front element.
		*/
		FORCEINLINE constexpr DataType& Front() noexcept
		{
			AA_CORE_ASSERT(Size > 0, "Empty Array! Cannot get front.");
			return InternalArray[0];
		}

		/*
		* Retrieves a reference to the front element in the array (const version).
		*
		* @returns Const reference to the front element.
		*/
		FORCEINLINE constexpr const DataType& Front() const noexcept
		{
			AA_CORE_ASSERT(Size > 0, "Empty Array! Cannot get front.");
			return InternalArray[0];
		}

		/*
		* Retrieves a reference to the last element in the array (non-const version).
		*
		* @returns Reference to the last element.
		*/
		FORCEINLINE constexpr DataType& Back() noexcept
		{
			AA_CORE_ASSERT(Size > 0, "Empty Array! Cannot get back.");
			return InternalArray[Size - 1];
		}

		/*
		* Retrieves a reference to the last element in the array (const version).
		*
		* @returns Const reference to the last element.
		*/
		FORCEINLINE constexpr const DataType& Back() const noexcept
		{
			AA_CORE_ASSERT(Size > 0, "Empty Array! Cannot get back.");
			return InternalArray[Size - 1];
		}

		/*
		* Equality comparison operator for two TStaticArray objects.
		*
		* @param Other - The array to compare against.
		*
		* @returns True if arrays are equal, false otherwise.
		*/
		FORCEINLINE constexpr bool operator==(const TStaticArray& Other) noexcept
		{
			for (size_t i = 0; i < Size; i++)
			{
				if (InternalArray[i] != Other.InternalArray[i])
				{
					return false;
				}
			}
			return true;
		}

		/*
		* Inequality comparison operator for two TStaticArray objects.
		*
		* @param Other - The array to compare against.
		*
		* @returns True if arrays are not equal, false otherwise.
		*/
		FORCEINLINE constexpr bool operator!=(const TStaticArray& Other) noexcept
		{
			for (size_t i = 0; i < Size; i++)
			{
				if (InternalArray[i] != Other.InternalArray[i])
				{
					return true;
				}
			}
			return false;
		}

		/*
		* Sorts the elements in the Array
		* Uses Quick Sort
		*/
		FORCEINLINE constexpr void Sort() noexcept
		{
			Algorithms::QuickSort(InternalArray, Size);
		}

		/*
		* Sorts the elements in the Array
		* Uses Quick Sort
		*
		* @param Pred - A Predicate function that 'overrides the () operator taking in 2 (const T&/ T&&) and comparing them returning a bool'
		*				bool operator()(const T& A, const T& B) const { return A < B; } => Sorted List { ... A, ..., B, ...} A comes before B
		*/
		template<class Predicate>
		FORCEINLINE constexpr void Sort(Predicate Pred) noexcept
		{
			Algorithms::QuickSort(InternalArray, Size, Pred);
		}

	private:
		/*
		* Internal Array object for the TStaticArray class 
		*/
		DataType InternalArray[Size] = {};

	public:
		/*
		* Iterator for the Static Array class
		*/
		template<typename InDataType, size_t Size>
		class StaticArrayIterator
		{
		public:
			using ValType = InDataType;
			using PtrType = ValType*;
			using RefType = ValType&;
			using PtrDiffType = ptrdiff_t;

			/*
			* Default constructor for the iterator.
			*/
			FORCEINLINE constexpr StaticArrayIterator() noexcept
			{
			}

			/*
			* Constructor for the iterator.
			*
			* @param Data - Pointer to the data.
			* @param Offset - Offset for the iterator.
			*/
			FORCEINLINE constexpr StaticArrayIterator(PtrType Data, size_t Offset = 0) noexcept
				: Pointer(Data + Offset)
			{
			}

			/*
			* Dereferencing operator to get the value at the iterator.
			*
			* @returns Reference to the value at the iterator.
			*/
			FORCEINLINE constexpr RefType operator*() const noexcept
			{
				return *Pointer;
			}

			/*
			* Member access operator to access methods/properties of the value at the iterator.
			*
			* @returns Pointer to the value at the iterator.
			*/
			FORCEINLINE constexpr PtrType operator->() const noexcept
			{
				return Pointer;
			}

			/*
			* Pre-increment operator for the iterator.
			* Moves the iterator to the next element.
			*
			* @returns Reference to the incremented iterator.
			*/
			FORCEINLINE constexpr StaticArrayIterator& operator++() noexcept {
				++Pointer;
				return *this;
			}

			/*
			* Post-increment operator for the iterator.
			* Moves the iterator to the next element.
			*
			* @returns Copy of the iterator before the increment.
			*/
			FORCEINLINE constexpr StaticArrayIterator operator++(int) noexcept {
				StaticArrayIterator It = *this;
				++Pointer;
				return It;
			}

			/*
			* Pre-decrement operator for the iterator.
			* Moves the iterator to the previous element.
			*
			* @returns Reference to the decremented iterator.
			*/
			FORCEINLINE constexpr StaticArrayIterator& operator--() noexcept {
				--Pointer;
				return *this;
			}

			/*
			* Post-decrement operator for the iterator.
			* Moves the iterator to the previous element.
			*
			* @returns Copy of the iterator before the decrement.
			*/
			FORCEINLINE constexpr StaticArrayIterator operator--(int) noexcept {
				StaticArrayIterator It = *this;
				--(*this);
				return It;
			}

			/*
			* Compound assignment subtraction operator for the iterator.
			* Moves the iterator backward by the specified offset.
			*
			* @param Offset - Offset value to subtract.
			* @returns Reference to the modified iterator.
			*/
			FORCEINLINE constexpr StaticArrayIterator& operator-=(ptrdiff_t Offset) noexcept {
				Pointer -= Offset;
				return *this;
			}

			/*
			* Compound assignment addition operator for the iterator.
			* Moves the iterator forward by the specified offset.
			*
			* @param Offset - Offset value to add.
			* @returns Reference to the modified iterator.
			*/
			FORCEINLINE constexpr StaticArrayIterator& operator+=(ptrdiff_t Offset) noexcept {
				Pointer += Offset;
				return *this;
			}

			/*
			* Subtraction operator for the iterator.
			* Calculates the distance between two iterators.
			*
			* @param Right - The iterator to subtract from this iterator.
			* @returns The distance between iterators as ptrdiff_t.
			*/
			FORCEINLINE constexpr ptrdiff_t operator-(const StaticArrayIterator& Right) const noexcept {
				return Pointer - Right.Pointer;
			}

			/*
			* Addition operator for the iterator.
			* Moves the iterator forward by the specified offset.
			*
			* @param Offset - Offset value to add.
			* @returns Copy of the iterator moved forward by the offset.
			*/
			FORCEINLINE constexpr StaticArrayIterator operator+(const ptrdiff_t Offset) const noexcept {
				StaticArrayIterator It = *this;
				Pointer += Offset;
				return It;
			}

			/*
			* Subtraction operator for the iterator.
			* Moves the iterator backward by the specified offset.
			*
			* @param Offset - Offset value to subtract.
			* @returns Copy of the iterator moved backward by the offset.
			*/
			FORCEINLINE constexpr StaticArrayIterator operator-(const ptrdiff_t Offset) const noexcept {
				StaticArrayIterator It = *this;
				Pointer -= Offset;
				return It;
			}

			/*
			* Subscript operator for the iterator.
			* Accesses the element at the specified offset from the iterator.
			*
			* @param Offset - Offset value to access the element.
			* @returns Reference to the element at the specified offset.
			*/
			FORCEINLINE constexpr RefType operator[](const ptrdiff_t Offset) const noexcept {
				return Pointer[Offset];
			}

			/*
			* Equality comparison operator for two iterators.
			*
			* @param Other - The iterator to compare against.
			* @returns True if iterators are pointing to the same element, false otherwise.
			*/
			FORCEINLINE constexpr bool operator==(const StaticArrayIterator& Other) const noexcept {
				return Other.Pointer == Pointer;
			}

			/*
			* Inequality comparison operator for two iterators.
			*
			* @param Other - The iterator to compare against.
			* @returns True if iterators are not pointing to the same element, false otherwise.
			*/
			FORCEINLINE constexpr bool operator!=(const StaticArrayIterator& Other) const noexcept {
				return Other.Pointer != Pointer;
			}
		private:
			/*
			* Pointer of the Iterator.
			*/
			PtrType Pointer;
		};

		// Alias for iterator of non-const array.
		using StaticAIt = StaticArrayIterator<DataType, Size>;
		// Alias for iterator of const array.
		using StaticConstAIt = StaticArrayIterator<const DataType, Size>;

		// Functions for array iteration.
		FORCEINLINE StaticAIt			begin()			{ return StaticAIt(InternalArray); }
		FORCEINLINE StaticConstAIt		begin() const	{ return StaticConstAIt(InternalArray); }
		FORCEINLINE StaticAIt			end()			{ return StaticAIt(InternalArray, Size); }
		FORCEINLINE StaticConstAIt		end() const		{ return StaticConstAIt(InternalArray, Size); }
	};
}