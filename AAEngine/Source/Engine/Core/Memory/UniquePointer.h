#pragma once

#include "Core/Core.h"
#include "Templates/RemoveReference.h"
#include "Templates/EnableIf.h"
#include "Templates/AATemplates.h"
#include "Templates/AATypeTraits.h"

namespace AAEngine {

	/*
	* Templated Deleter class to handle custom Deletion logic when freeing memory
	*/
	template<typename T>
	struct AA_ENGINE_API TDefaultDeleter
	{
		TDefaultDeleter() = default;
		TDefaultDeleter(const TDefaultDeleter&) = default;
		TDefaultDeleter& operator=(const TDefaultDeleter&) = default;
		~TDefaultDeleter() = default;

		template<typename U>
		TDefaultDeleter(const TDefaultDeleter<U>&) {}

		template<typename U>
		TDefaultDeleter& operator=(const TDefaultDeleter<U>&) { return *this; }

		void operator()(T* Pointer)
		{
			delete Pointer;
		}

		template<typename U>
		void operator()(U* Pointer)
		{
			delete Pointer;
		}
	};

	/*
	* Templated Unique Pointer class with Templated Deleter
	* This class acts as a Scoped Pointer
	* After construction, memory is allocated, when out of scope, it is destroyed and memory is freed
	*/
	template<typename T, typename Deleter = TDefaultDeleter<T>>
	class AA_ENGINE_API TUniquePtr : private Deleter
	{
	public:
		/*
		* Default constructor initializing Deleter and Pointer = nullptr
		*/
		constexpr FORCEINLINE TUniquePtr() noexcept
			: Deleter(), Pointer(nullptr)
		{
		}

		/*
		* Constructor that takes in nullptr and initializes Deleter and Pointer = nullptr
		*/
		constexpr FORCEINLINE TUniquePtr(NULLPTR_TYPE) noexcept
			: Deleter(), Pointer(nullptr)
		{
		}

		/*
		* Templated Constructor that takes in Implicitly comvertable U*
		* Initializes Deleter and Pointer = InPointer
		* 
		* @param Implicitly convertable U* to T*
		*/
		template<typename U>
		constexpr FORCEINLINE TUniquePtr(U* InPointer) noexcept
			: Deleter(), Pointer(InPointer)
		{
		}

		/*
		* Templated Constructor that takes in Implicitly comvertable U* and a rvalue reference of a Deleter
		* Initializes Deleter = Move(InDeleter) and Pointer = InPointer
		*
		* @param Implicitly convertable U* to T*
		* @param rvalue reference of the Custom Deleter
		*/
		template<typename U>
		constexpr FORCEINLINE TUniquePtr(U* InPointer, Deleter&& InDeleter) noexcept
			: Deleter(Move(InDeleter)), Pointer(InPointer)
		{
		}

		/*
		* Templated Constructor that takes in Implicitly comvertable U* and a lvalue reference of a Deleter
		* Initializes Deleter = InDeleter (Copy) and Pointer = InPointer
		*
		* @param Implicitly convertable U* to T*
		* @param lvalue reference of the Custom Deleter
		*/
		template<typename U>
		constexpr FORCEINLINE TUniquePtr(U* InPointer, Deleter& InDeleter) noexcept
			: Deleter(InDeleter), Pointer(InPointer)
		{
		}

		/*
		* Deleted Copy Constructor
		* Deleted Copy Assignment Operator
		* 
		* We shouldn't allow copies of the same Unique Pointer
		* Copying means the ownership is split between this and the copy which is wrong
		*/
		TUniquePtr(const TUniquePtr&) = delete;
		TUniquePtr& operator=(const TUniquePtr&) = delete;

		/*
		* Move Constructor that takes in Another Unique Pointer
		* Initializes Deleter = Move(OtherPointer.GetDeleter()) and Pointer = OtherPointer.Pointer, 
		* and we make sure to set the OtherPointer's Pointer to nullptr. (Ownership transfer)
		*
		* @param rvalue reference of another TUniquePtr
		*/
		constexpr FORCEINLINE TUniquePtr(TUniquePtr&& OtherPointer)
			: Deleter(Move(OtherPointer.GetDeleter())), Pointer(OtherPointer) noexcept
		{
			OtherPointer.Pointer = nullptr;
		}

		/*
		* Templated Move Constructor that takes in Another Unique Pointer with Implicitly comvertable OtherT* and OtherDeleter
		* Initializes Deleter = Move(OtherPointer.GetDeleter()) and Pointer = OtherPointer.Pointer, 
		* and we make sure to set the OtherPointer's Pointer to nullptr. (Ownership transfer)
		*
		* @param rvalue reference of another TUniquePtr with Implicitly comvertable OtherT* and OtherDeleter
		*/
		template<typename OtherT, typename OtherDeleter>
		constexpr FORCEINLINE TUniquePtr(TUniquePtr<OtherT, OtherDeleter>&& OtherPointer) noexcept
			: Deleter(Move(OtherPointer.GetDeleter())), Pointer(OtherPointer)
		{
			OtherPointer.Pointer = nullptr;
		}

		/*
		* Move Assignment Operator that takes in Another Unique Pointer
		* If &OtherPointer != this, only then we assign the pointer of the OtherPointer to this and call Deleter on our OldPointer.
		* Otherwise we continue and assign the deleter of the OtherPointer to this one as that can be different
		*
		* @param rvalue reference of another TUniquePtr
		* 
		* @returns *this - reference to this
		*/
		constexpr FORCEINLINE TUniquePtr& operator=(TUniquePtr&& OtherPointer) noexcept
		{
			if (this != &OtherPointer)
			{
				T* OldPointer = Pointer;
				Pointer = OtherPointer.Pointer;
				OtherPointer.Pointer = nullptr;
				GetDeleter()(OldPointer);
			}

			GetDeleter() = Move(OtherPointer.GetDeleter());

			return *this;
		}

		/*
		* Templated Move Constructor that takes in Another Unique Pointer with Implicitly comvertable OtherT* and OtherDeleter
		* Here we know &OtherPointer != this as the Type is deferrent, so we assign the pointer of the OtherPointer to this and call Deleter on our OldPointer.
		* Then we continue and assign the deleter of the OtherPointer to this one as that can be different
		*
		* @param rvalue reference of another TUniquePtr with Implicitly comvertable OtherT* and OtherDeleter
		* 
		* @returns *this - reference to this
		*/
		template<typename OtherT, typename OtherDeleter>
		constexpr FORCEINLINE TUniquePtr& operator=(TUniquePtr<OtherT, OtherDeleter>&& OtherPointer) noexcept
		{
			T* OldPointer = Pointer;
			Pointer = OtherPointer.Pointer;
			OtherPointer.Pointer = nullptr;
			GetDeleter()(OldPointer);

			GetDeleter() = Move(OtherPointer.GetDeleter());

			return *this;
		}

		/*
		* Destructor calling the Deleter's version of freeing memory
		*/
		FORCEINLINE ~TUniquePtr() noexcept
		{
			GetDeleter()(Pointer);
		}

		/*
		* Pointer Release function
		* Sets the current Pointer to nullptr and returns it's Old Pointer Value
		*
		* @returns T* - Pointer to the Old Data of the TUniquePtr
		*/
		constexpr FORCEINLINE T* Release() noexcept
		{
			T* OldPointer = Pointer;
			Pointer = nullptr;
			return OldPointer;
		}

		/*
		* Pointer Reset function
		* If Pointer != NewPointer, sets the current Pointer to NewPointer and returns it's Old Pointer Value
		*/
		constexpr FORCEINLINE void Reset(T* NewPointer = nullptr) noexcept
		{
			if (Pointer != NewPointer)
			{
				T* OldPointer = Pointer;
				Pointer = NewPointer;
				GetDeleter()(OldPointer);
			}
		}

		/*
		* Pointer IsValid function
		* Checks whether the Pointer is not a nullptr
		*
		* @returns true if Pointer != nullptr, false otherwise
		*/
		constexpr FORCEINLINE bool IsValid() const noexcept
		{
			return Pointer != nullptr;
		}

		/*
		* bool cast operator
		* Helps casting this Pointer to a bool
		* Essentially returns whether this Pointer is a nullptr or not
		*
		* @returns true if Pointer != nullptr, false otherwise
		*/
		constexpr explicit FORCEINLINE operator bool() const noexcept
		{
			return IsValid();
		}

		/*
		* NOT bit operator
		* operator to do things like !UniPtr instead of UniPtr != nullptr
		*
		* @returns true if Pointer == nullptr, false otherwise
		*/
		constexpr FORCEINLINE bool operator!() noexcept
		{
			return !IsVaild();
		}

		/*
		* EQUALS boolean operator
		* operator to do things like UniPtr == OtherUniPtr
		*
		* @returns true if Pointer == RHS.Pointer, false otherwise
		*/
		template<typename RhsT>
		constexpr FORCEINLINE bool operator==(const TUniquePtr<RhsT>& RHS) const noexcept
		{
			return Get() == RHS.Get();
		}

		/*
		* EQUALS boolean operator for Nullptr type
		* operator to do things like UniPtr == nullptr
		*
		* @returns true if Pointer == nullptr, false otherwise
		*/
		template<typename RhsT>
		constexpr FORCEINLINE bool operator==(NULLPTR_TYPE) const noexcept
		{
			return !IsValid();
		}

		/*
		* INDIRECTION operator
		* operator to do things like UniPtr->(SomeFunction of Pointer)
		*
		* @returns Pointer variable
		*/
		constexpr FORCEINLINE T* operator->() const noexcept
		{
			return Pointer;
		}

		/*
		* REFERNCE operator
		* operator to do things like &UniPtr and get an lvalue reference of the Pointer
		*
		* @returns De-Referenced Pointer variable
		*/
		constexpr FORCEINLINE T& operator*() const noexcept
		{
			return *Pointer;
		}

		/*
		* Pointer Get function
		*
		* @returns Pointer variable
		*/
		constexpr FORCEINLINE T* Get() const noexcept
		{
			return Pointer;
		}

		/*
		* GetDeleter function
		*
		* @returns lvalue ref of Deleter of the TUniquePtr
		*/
		constexpr FORCEINLINE Deleter& GetDeleter() noexcept
		{
			return static_cast<Deleter&>(*this);
		}

		/*
		* const version of GetDeleter function
		*
		* @returns const lvalue ref of Deleter of the TUniquePtr
		*/
		constexpr FORCEINLINE const Deleter& GetDeleter() const noexcept
		{
			return static_cast<Deleter&>(*this);
		}

	private:
		/*
		* The Pointer variable we are protecting and taking ownership of
		* Noob Pointer!
		*/
		T* Pointer;

	public:
#if !COMPILER_HAS_GENERATED_COMPARISION_OPERATORS
		/*
		* NOT EQUALS boolean operator
		* operator to do things like UniPtr == RHS
		*
		* @returns true if Pointer != RHS.Pointer, false otherwise
		*/
		template<typename T>
		FORCEINLINE bool operator!=(const TUniquePtr<T>& Rhs)
		{
			return Get() != Rhs.Get();
		}

		/*
		* NOT EQUALS boolean operator for Nullptr type
		* operator to do things like UniPtr == nullptr
		*
		* @returns true if Pointer != nullptr, false otherwise
		*/
		template<typename T>
		FORCEINLINE bool operator!=(NULLPTR_TYPE)
		{
			return !IsValid();
		}
#endif
	};
	// Non - Member functions for Unique Pointer

#if !COMPILER_HAS_GENERATED_COMPARISION_OPERATORS

	template<typename T>
	FORCEINLINE bool operator==(NULLPTR_TYPE, const TUniquePtr<T>& Rhs)
	{
		return Rhs.IsValid();
	}

	template<typename T>
	FORCEINLINE bool operator!=(NULLPTR_TYPE, const TUniquePtr<T>& Rhs)
	{
		return !Rhs.IsValid();
	}

#endif

	template<class T, class... ArgsT>
	FORCEINLINE typename TEnableIf<!TIsArray<T>::Value, TUniquePtr<T>>::Type MakeUnique(ArgsT&&... Args)
	{
		return TUniquePtr<T>(new T(Forward<ArgsT>(Args)...));
	}
	/*template<class T>
	TEnableIf<TIsUnBoundedArray<T>::Value, TUniquePtr<T>> make_unique(std::size_t n)
	{
		return std::unique_ptr<T>(new std::remove_extent_t<T>[n]());
	}*/

	//// No Array Unique Ptr - TO DO
	//template<class T, class... Args>
	//TEnableIf<TIsArray<T>::Value> MakeUnique(Args&&...) = delete;
}