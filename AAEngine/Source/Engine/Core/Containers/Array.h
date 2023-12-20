#pragma once

#include "Core/Core.h"

#include "Templates/AATemplates.h"
#include "Memory/Memory.h"

namespace AAEngine {

	/*
	* Iterator for the Dynamic Array class
	*/
	template<typename InDataType>
	class AA_ENGINE_API DynArrayIterator
	{
	public:
		using ValType = InDataType;
		using PtrType = ValType*;
		using RefType = ValType&;
		using PtrDiffType = ptrdiff_t;

		/*
		* Default constructor for DynArrayIterator.
		*/
		constexpr DynArrayIterator() noexcept
			: Pointer(nullptr)
		{
		}

		/*
		* Constructor for DynArrayIterator.
		* 
		* @param Data - Pointer to the data.
		* 
		* @param Offset - Offset for the iterator.
		*/
		constexpr DynArrayIterator(PtrType Data, size_t Offset = 0) noexcept
			: Pointer(Data + Offset)
		{
		}

		/*
		* Dereferencing operator to get the value at the iterator.
		* 
		* @returns Reference to the value at the iterator.
		*/
		constexpr RefType operator*() const noexcept
		{
			return *Pointer;
		}

		/*
		* Member access operator to access methods/properties of the value at the iterator.
		* 
		* @returns Pointer to the value at the iterator.
		*/
		constexpr PtrType operator->() const noexcept
		{
			return Pointer;
		}

		/*
		* Pre-increment operator: Moves the iterator to the next element.
		*
		* @returns Reference to the updated iterator.
		*/
		constexpr DynArrayIterator& operator++() noexcept
		{
			++Pointer;
			return *this;
		}

		/*
		* Post-increment operator: Creates a copy of the current iterator, moves the original to the next element, and returns the copy.
		*
		* @returns Copy of the current iterator before increment.
		*/
		constexpr DynArrayIterator operator++(int) noexcept
		{
			DynArrayIterator It = *this;
			++Pointer;
			return It;
		}

		/*
		* Pre-decrement operator: Moves the iterator to the previous element.
		*
		* @returns Reference to the updated iterator.
		*/
		constexpr DynArrayIterator& operator--() noexcept
		{
			Pointer--;
			return *this;
		}

		/*
		* Post-decrement operator: Creates a copy of the current iterator, moves the original to the previous element, and returns the copy.
		*
		* @returns Copy of the current iterator before decrement.
		*/
		constexpr DynArrayIterator operator--(int) noexcept
		{
			DynArrayIterator It = *this;
			--(*this);
			return It;
		}

		/*
		* Compound assignment subtraction operator: Moves the iterator backward by the specified offset.
		*
		* @param Offset - The offset to move backward.
		* 
		* @returns Reference to the updated iterator.
		*/
		constexpr DynArrayIterator& operator-=(ptrdiff_t Offset) noexcept
		{
			Pointer -= Offset;
			return *this;
		}

		/*
		* Compound assignment addition operator: Moves the iterator forward by the specified offset.
		*
		* @param Offset - The offset to move forward.
		* 
		* @returns Reference to the updated iterator.
		*/
		constexpr DynArrayIterator& operator+=(ptrdiff_t Offset) noexcept
		{
			Pointer += Offset;
			return *this;
		}

		/*
		* Subtraction operator for iterators: Calculates the difference between two iterators and returns the distance between their pointers.
		*
		* @param Right - The iterator to subtract.
		* 
		* @returns Distance between the iterators' pointers.
		*/
		constexpr ptrdiff_t operator-(const DynArrayIterator& Right) const noexcept
		{
			return Pointer - Right.Pointer;
		}

		/*
		* Addition operator for iterators: Creates a new iterator by moving it forward by the specified offset from the current iterator.
		*
		* @param Offset - The offset to move forward.
		* 
		* @returns New iterator moved by the specified offset.
		*/
		constexpr DynArrayIterator operator+(const ptrdiff_t Offset) const noexcept
		{
			DynArrayIterator It = *this;
			It += Offset;
			return It;
		}

		/*
		* Subtraction operator for iterators: Creates a new iterator by moving it backward by the specified offset from the current iterator.
		*
		* @param Offset - The offset to move backward.
		* 
		* @returns New iterator moved by the specified offset.
		*/
		constexpr DynArrayIterator operator-(const ptrdiff_t Offset) const noexcept
		{
			DynArrayIterator It = *this;
			It -= Offset;
			return It;
		}

		/*
		* Subscript operator for the iterator: Accesses the value at the specified offset from the iterator.
		*
		* @param Offset - The offset to access the value.
		* 
		* @returns Value at the specified offset.
		*/
		constexpr RefType operator[](const ptrdiff_t Offset) const noexcept
		{
			return Pointer[Offset];
		}

		/*
		* Equality operator for iterators: Checks if two iterators are pointing to the same location.
		*
		* @param Other - The iterator to compare.
		* 
		* @returns True if the iterators are pointing to the same location, false otherwise.
		*/
		constexpr bool operator==(const DynArrayIterator& Other) const noexcept
		{
			return Other.Pointer == Pointer;
		}

		/*
		* Inequality operator for iterators: Checks if two iterators are not pointing to the same location.
		*
		* @param Other - The iterator to compare.
		* 
		* @returns True if the iterators are not pointing to the same location, false otherwise.
		*/
		constexpr bool operator!=(const DynArrayIterator& Other) const noexcept
		{
			return Other.Pointer != Pointer;
		}

		/*
		* Function to retrieve the pointer stored in the iterator.
		* 
		* @returns Pointer stored in the iterator.
		*/
		constexpr PtrType Get() const noexcept
		{
			return Pointer;
		}
	private:
		/*
		* Pointer for the Array Elements for the iterator.
		*/
		PtrType Pointer;
	};

	template<typename T>
	class AA_ENGINE_API TArray
	{
#define DEFAULT_RESIZE_MULTIPLIER 2
#define NEW_RESIZE_CAPACITY (static_cast<size_t>(Capacity * DEFAULT_RESIZE_MULTIPLIER) + 1)
	public:
		using Iterator = DynArrayIterator<T>;
		using ConstIterator = DynArrayIterator<const T>;

		/*
		* Default constructor for TArray.
		* Initializes Size, Capacity, and the array pointer to nullptr.
		*/
		TArray()
			: Size(0), Capacity(0), InArray(nullptr) {}

		/*
		* Copy constructor for TArray.
		* Copies elements from the given NewArray to the current array.
		*
		* @param NewArray - The array to copy from.
		*/
		TArray(const TArray& NewArray)
		{
			ReallocateArray(NewArray.Capacity);
			for (size_t i = 0; i < NewArray.Size; i++)
			{
				new(&InArray[i]) T(NewArray[i]);
			}
			Size = NewArray.Size;
		}

		/*
		* Move constructor for TArray.
		* Moves elements from the given NewArray to the current array.
		*
		* @param NewArray - The array to move from.
		*/
		TArray(TArray&& NewArray)
		{
			ReallocateArray(NewArray.Capacity);
			for (size_t i = 0; i < NewArray.Size; i++)
			{
				new(&InArray[i]) T(Move(NewArray[i]));
			}
			Size = NewArray.Size;
		}

		/*
		* Assignment operator for TArray (copy assignment).
		* Copies elements from the given NewArray to the current array.
		*
		* @param NewArray - The array to copy from.
		* 
		* @returns Reference to the updated array.
		*/
		TArray& operator=(const TArray& NewArray)
		{
			AssignArray(NewArray);
			return *this;
		}

		/*
		* Move assignment operator for TArray.
		* Moves elements from the given NewArray to the current array.
		*
		* @param NewArray - The array to move from.
		* 
		* @returns Reference to the updated array.
		*/
		TArray& operator=(TArray&& NewArray)
		{
			AssignArray(Move(NewArray));
			return *this;
		}

		/*
		* Destructor for TArray.
		* Clears the array by calling the Clear() function and deletes the memory allocated for the array.
		*/
		~TArray()
		{
			Clear();
			if (InArray)
			{
				::operator delete(InArray, Capacity * sizeof(T));
			}
		}

		/*
		* Inserts a copy of the given element at the end of the array.
		*
		* @param Element - The element to insert.
		*/
		void PushBack(const T& Element)
		{
			if (Size >= Capacity)
			{
				ReallocateArray(NEW_RESIZE_CAPACITY);
			}
			new(&InArray[Size]) T(Element);
			Size++;
		}

		/*
		* Moves the given element to the end of the array.
		*
		* @param Element - The element to move.
		*/
		void PushBack(T&& Element)
		{
			if (Size >= Capacity)
			{
				ReallocateArray(NEW_RESIZE_CAPACITY);
			}
			new(&InArray[Size]) T(Move(Element));
			Size++;
		}

		/*
		* Constructs an element in place at the end of the array using perfect forwarding.
		*
		* @param Args - The arguments to forward to the element's constructor.
		* 
		* @returns Reference to the newly emplaced element.
		*/
		template<typename... DirectArgs>
		T& EmplaceBack(DirectArgs&&... Args)
		{
			return Emplace(Size, Args...);
		}

		/*
		* Constructs an element in place at the specified position using perfect forwarding.
		*
		* @param Position - The position where the element should be constructed.
		* @param Args - The arguments to forward to the element's constructor.
		* 
		* @returns Reference to the newly emplaced element.
		*/
		template<typename... DirectArgs>
		T& Emplace(size_t Position, DirectArgs&&... Args)
		{
			if (Size >= Capacity)
			{
				ReallocateArray(NEW_RESIZE_CAPACITY);
			}

			// Should we clamp?
			Position = Position < 0 ? 0 : (Position >= Size ? Size : Position);
			if (Position >= Size)
			{
				new(&InArray[Size]) T(Forward<DirectArgs>(Args)...);
				return InArray[Size++];
			}
			else
			{
				FMemory::MemCopy(InArray + Position + 1, InArray + Position, sizeof(T) * (Size - Position));
				new(&InArray[Position]) T(Forward<DirectArgs>(Args)...);
				Size++;
				return InArray[Position];
			}
		}

		/*
		 * Constructs an element in place at the position specified by the iterator using perfect forwarding.
		 *
		 * @param It - The iterator pointing to the position to insert the element.
		 * @param Args - The arguments to forward to the element's constructor.
		 * 
		 * @returns Iterator pointing to the newly emplaced element.
		 */
		template<typename... DirectArgs>
		Iterator Emplace(Iterator It, DirectArgs&&... Args)
		{
			if (Size >= Capacity)
			{
				ptrdiff_t DiffToPos = It - end();
				ReallocateArray(NEW_RESIZE_CAPACITY);
				It = end() + DiffToPos;
			}

			if (It - end() >= (ptrdiff_t)0)
			{
				new(end().Get()) T(Forward<DirectArgs>(Args)...);
				Size++;
				return MakeIterator(end().Get());
			}
			else
			{
				FMemory::MemCopy(It.Get() + 1, It.Get(), sizeof(T) * (end() - It));
				new(It.Get()) T(Forward<DirectArgs>(Args)...);
				Size++;
				return MakeIterator(It.Get());
			}
		}

		/*
		* Inserts a copy of the given element at the specified position in the array.
		*
		* @param Position - The position where the element should be inserted.
		* @param Element - The element to insert.
		*/
		void InsertAt(size_t Position, const T& Element)
		{
			if (Size >= Capacity)
			{
				ReallocateArray(NEW_RESIZE_CAPACITY);
			}

			// Should we clamp?
			Position = Position < 0 ? 0 : (Position >= Size ? Size : Position);
			if (Position >= Size)
			{
				new(&InArray[Size]) T(Element);
			}
			else
			{
				FMemory::MemCopy(InArray + Position + 1, InArray + Position, sizeof(T) * (Size - Position));
				new(&InArray[Position]) T(Element);
			}
			Size++;
		}

		/*
		* Moves the given element to the specified position in the array.
		*
		* @param Position - The position where the element should be inserted.
		* @param Element - The element to move.
		*/
		void InsertAt(size_t Position, T&& Element)
		{
			if (Size >= Capacity)
			{
				ReallocateArray(NEW_RESIZE_CAPACITY);
			}

			// Should we clamp?
			Position = Position < 0 ? 0 : (Position >= Size ? Size : Position);
			if (Position >= Size)
			{
				new(&InArray[Size]) T(Move(Element));
			}
			else
			{
				FMemory::MemCopy(InArray + Position + 1, InArray + Position, sizeof(T) * (Size - Position));
				new(&InArray[Position]) T(Move(Element));
			}
			Size++;
		}

		/*
		* Inserts a copy of the given element at the position specified by the iterator.
		*
		* @param It - The iterator pointing to the position to insert the element.
		* @param Element - The element to insert.
		* 
		* @returns Iterator pointing to the newly inserted element.
		*/
		Iterator InsertAt(Iterator It, const T& Element)
		{
			return Emplace(It, Element);
		}

		/*
		* Moves the given element to the position specified by the iterator.
		*
		* @param It - The iterator pointing to the position to insert the element.
		* @param Element - The element to move.
		* 
		* @returns Iterator pointing to the newly inserted element.
		*/
		Iterator InsertAt(Iterator It, T&& Element)
		{
			return Emplace(It, Move(Element));
		}


		/**
 * Removes an element from the specified position in the array.
 *
 * @param Position - The position of the element to remove.
 */
		void RemoveAt(size_t Position)
		{
			if (Size <= 1)
			{
				PopBack();
				return;
			}
			if (Position >= Size - 1)
			{
				PopBack();
			}
			else
			{
				FMemory::MemCopy(InArray + Position, InArray + Position + 1, sizeof(T) * (Size - Position - 1));
				InArray[Position].~T();
				Size--;
			}
		}

		/*
		* Removes an element from the specified iterator position in the array.
		*
		* @param It - The iterator pointing to the element to remove.
		*/
		void RemoveAt(Iterator It)
		{
			auto Pos = It - begin();
			RemoveAt(Pos);
		}

		/*
		* Removes the last element from the array.
		*/
		void PopBack()
		{
			if (Size > 0)
			{
				Size--;
				InArray[Size].~T();
			}
		}

		/*
		* Reserves memory for the array to accommodate the specified capacity.
		*
		* @param NewCapacity - The new capacity to reserve.
		*/
		void Reserve(size_t NewCapacity)
		{
			if (NewCapacity > Capacity)
			{
				ReallocateArray(NewCapacity);
			}
		}

		/*
		* Reduces the capacity of the array to match its size.
		*/
		void ShrinkToFit()
		{
			if (Capacity > Size)
			{
				// TO DO: Don't reallocate
				ReallocateArray(Size);
			}
		}

		/*
		* Clears the array by destructing all elements.
		*/
		void Clear()
		{
			for (size_t i = 0; i < Size; i++)
			{
				InArray[i].~T();
			}
			Size = 0;
		}

		/*
		* Finds the specified element in the array and returns an iterator pointing to it.
		*
		* @param ToFind - The element to find.
		* @return Iterator - Iterator pointing to the found element. If not found, returns end().
		*/
		constexpr Iterator Find(const T& ToFind) noexcept
		{
			for (Iterator it = begin(); it != end(); it++)
			{
				if (*it == ToFind)
				{
					return it;
				}
			}
			return end();
		}

		/*
		* Provides non-const access to the element at the specified index.
		*
		* @param Index - The index of the element to access.
		* @return T& - Reference to the element at the specified index.
		*/
		constexpr T& operator[](size_t Index) noexcept
		{
			AA_CORE_ASSERT(int(Index < Size), "Index Out of Bounds: %d when Size is %d", Index, Size);
			return InArray[Index];
		}

		/*
		* Provides const access to the element at the specified index.
		*
		* @param Index - The index of the element to access.
		* @return const T& - Const reference to the element at the specified index.
		*/
		constexpr const T& operator[](size_t Index) const noexcept
		{
			AA_CORE_ASSERT(int(Index < Size), "Index Out of Bounds: %d when Size is %d", Index, Size);
			return InArray[Index];
		}

		/*
		* Returns the number of elements in the array.
		*
		* @return size_t - Number of elements in the array.
		*/
		constexpr size_t Num() const noexcept
		{
			return Size;
		}

		/*
		* Checks if the array is empty.
		*
		* @return bool - True if the array is empty, false otherwise.
		*/
		constexpr bool IsEmpty() const noexcept
		{
			return Size == 0;
		}

		/*
		* Returns a reference to the first element in the array.
		*
		* @return T& - Reference to the first element.
		*/
		constexpr T& Data() noexcept
		{
			AA_CORE_ASSERT(Size > 0, "Empty Array! Cannot get data.");
			return InArray[0];
		}

		/*
		* Returns a const reference to the first element in the array.
		*
		* @return const T& - Const reference to the first element.
		*/
		constexpr const T& Data() const noexcept
		{
			AA_CORE_ASSERT(Size > 0, "Empty Array! Cannot get data.");
			return InArray[0];
		}

		/*
		* Returns a reference to the first element in the array.
		*
		* @return T& - Reference to the first element.
		*/
		constexpr T& Front() noexcept
		{
			AA_CORE_ASSERT(Size > 0, "Empty Array! Cannot get front.");
			return InArray[0];
		}

		/*
		* Returns a const reference to the first element in the array.
		*
		* @return const T& - Const reference to the first element.
		*/
		constexpr const T& Front() const noexcept
		{
			AA_CORE_ASSERT(Size > 0, "Empty Array! Cannot get front.");
			return InArray[0];
		}

		/*
		* Returns a reference to the last element in the array.
		*
		* @return T& - Reference to the last element.
		*/
		constexpr T& Back() noexcept
		{
			AA_CORE_ASSERT(Size > 0, "Empty Array! Cannot get back.");
			return InArray[Size - 1];
		}

		/*
		* Returns a const reference to the last element in the array.
		*
		* @return const T& - Const reference to the last element.
		*/
		constexpr const T& Back() const noexcept
		{
			AA_CORE_ASSERT(Size > 0, "Empty Array! Cannot get back.");
			return InArray[Size - 1];
		}


	private:
		/*
		* Pointer to the array of the TArray.
		*/
		T* InArray{ nullptr };

		/*
		* Number of elements in the TArray.
		*/
		size_t Size{ 0 };

		/*
		* Capacity of the TArray.
		*/
		size_t Capacity{ 0 };

		/*
		* Reallocates the array with the specified capacity.
		* Moves existing elements if the new capacity is less than the current size.
		*
		* @param NewCapacity - The new capacity for the array.
		*/
		void ReallocateArray(size_t NewCapacity)
		{
			T* NewArray = (T*)::operator new(NewCapacity * sizeof(T));

			if (NewCapacity < Size)
			{
				Size = NewCapacity;
			}

			for (size_t i = 0; i < Size; i++)
			{
				new(&NewArray[i]) T(Move(InArray[i]));
			}

			for (size_t i = 0; i < Size; i++)
			{
				InArray[i].~T();
			}

			::operator delete(InArray, Size * sizeof(T));

			InArray = NewArray;
			Capacity = NewCapacity;
		}

		/*
		* Assigns the array to be equal to another array.
		*
		* @param EqualsArray - The array to be assigned.
		*/
		void AssignArray(const TArray& EqualsArray)
		{
			if (EqualsArray.Capacity != Capacity)
			{
				T* NewArray = (T*)::operator new(EqualsArray.Capacity * sizeof(T));

				for (size_t i = 0; i < EqualsArray.Size; i++)
				{
					new(&NewArray[i]) T(EqualsArray[i]);
				}

				for (size_t i = 0; i < Size; i++)
				{
					InArray[i].~T();
				}

				::operator delete(InArray, Size * sizeof(T));

				InArray = NewArray;
				Capacity = EqualsArray.Capacity;
			}
			else
			{
				for (size_t i = 0; i < EqualsArray.Size; i++)
				{
					new(&InArray[i]) T(EqualsArray[i]);
				}
			}

			Size = EqualsArray.Size;
		}

		/*
		* Assigns the array to be equal to another array using move semantics.
		*
		* @param EqualsArray - The array to be assigned (using move semantics).
		*/
		void AssignArray(TArray&& EqualsArray)
		{
			if (EqualsArray.Capacity != Capacity)
			{
				T* NewArray = (T*)::operator new(EqualsArray.Capacity * sizeof(T));

				for (size_t i = 0; i < EqualsArray.Size; i++)
				{
					new(&NewArray[i]) T(Move(EqualsArray[i]));
				}

				for (size_t i = 0; i < Size; i++)
				{
					InArray[i].~T();
				}

				::operator delete(InArray, Size * sizeof(T));

				InArray = NewArray;
				Capacity = EqualsArray.Capacity;
			}
			else
			{
				for (size_t i = 0; i < EqualsArray.Size; i++)
				{
					new(&InArray[i]) T(Move(EqualsArray[i]));
				}
			}

			Size = EqualsArray.Size;
		}

		/*
		* Creates an iterator with the specified pointer.
		*
		* @param Pointer - Pointer to create the iterator.
		* 
		* @return Iterator - The created iterator.
		*/
		Iterator MakeIterator(T* Pointer)
		{
			return Iterator(Pointer);
		}


	public:
		// Functions for array iteration.
		FORCEINLINE Iterator			begin()				{ return Iterator(InArray); }
		FORCEINLINE ConstIterator		begin() const		{ return ConstIterator(InArray); }
		FORCEINLINE Iterator			end()				{ return Iterator(InArray, Size); }
		FORCEINLINE ConstIterator		end() const			{ return ConstIterator(InArray, Size); }
	};

	/*
	* Finds an element within a range defined by start and end iterators.
	*
	* @param Start - The start iterator of the range.
	* @param End - The end iterator of the range.
	* @param ToFind - The element to search for.
	* 
	* @return DynArrayIterator<T> - An iterator pointing to the found element or the end iterator if not found.
	*/
	template<typename T>
	DynArrayIterator<T> Find(DynArrayIterator<T> Start, DynArrayIterator<T> End, T ToFind)
	{
		// Ensure that the range is valid (End > Start)
		AA_CORE_ASSERT(End - Start > 0, "Find: End > Start. Invalid End Iterator!");

		// Iterate through the range defined by Start and End
		auto it = Start;
		for (it = Start; it != End; it++)
		{
			if (*it == ToFind)
			{
				return it;
			}
		}

		return it;
	}
}