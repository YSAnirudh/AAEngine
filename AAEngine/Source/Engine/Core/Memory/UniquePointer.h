#pragma once

#include "Core/Core.h"
#include "Templates/RemoveReference.h"
#include "Templates/AATemplates.h"

namespace AAEngine {

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

	template<typename T, typename Deleter = TDefaultDeleter<T>>
	class AA_ENGINE_API TUniquePtr : private Deleter
	{
	public:
		FORCEINLINE TUniquePtr()
			: Deleter(), Pointer(nullptr)
		{
		}

		FORCEINLINE TUniquePtr(NULLPTR_TYPE)
			: Deleter(), Pointer(nullptr)
		{
		}

		template<typename U>
		explicit FORCEINLINE TUniquePtr(U* InPointer)
			: Deleter(), Pointer(InPointer)
		{
		}

		template<typename U>
		explicit FORCEINLINE TUniquePtr(U* InPointer, Deleter&& InDeleter)
			: Deleter(Move(InDeleter)), Pointer(InPointer)
		{
		}

		template<typename U>
		explicit FORCEINLINE TUniquePtr(U* InPointer, Deleter& InDeleter)
			: Deleter(InDeleter), Pointer(InPointer)
		{
		}

		FORCEINLINE ~TUniquePtr()
		{
			GetDeleter()(Pointer);
		}

		TUniquePtr(const TUniquePtr&) = delete;
		TUniquePtr& operator=(const TUniquePtr&) = delete;

		FORCEINLINE TUniquePtr(TUniquePtr&& OtherPointer)
			: Deleter(Move(OtherPointer.GetDeleter())), Pointer(OtherPointer)
		{
			OtherPointer.Pointer = nullptr;
		}

		template<typename OtherT, typename OtherDeleter>
		explicit FORCEINLINE TUniquePtr(TUniquePtr<OtherT, OtherDeleter>&& OtherPointer)
			: Deleter(Move(OtherPointer.GetDeleter())), Pointer(OtherPointer)
		{
			OtherPointer.Pointer = nullptr;
		}

		FORCEINLINE TUniquePtr& operator=(TUniquePtr&& OtherPointer)
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

		template<typename OtherT, typename OtherDeleter>
		FORCEINLINE TUniquePtr& operator=(TUniquePtr<OtherT, OtherDeleter>&& OtherPointer)
		{
			T* OldPointer = Pointer;
			Pointer = OtherPointer.Pointer;
			OtherPointer.Pointer = nullptr;
			GetDeleter()(OldPointer);

			GetDeleter() = Move(OtherPointer.GetDeleter());

			return *this;
		}

		FORCEINLINE T* Release()
		{
			T* OldPointer = Pointer;
			Pointer = nullptr;
			return OldPointer;
		}

		FORCEINLINE void Reset(T* NewPointer = nullptr)
		{
			if (Pointer != NewPointer)
			{
				T* OldPointer = Pointer;
				Pointer = NewPointer;
				GetDeleter()(OldPointer);
			}
		}

		FORCEINLINE bool IsValid() const
		{
			return Pointer != nullptr;
		}

		explicit FORCEINLINE operator bool() const
		{
			return IsValid();
		}

		FORCEINLINE bool operator!()
		{
			return !IsVaild();
		}

		template<typename RhsT>
		FORCEINLINE bool operator==(const TUniquePtr<RhsT>& RHS) const
		{
			return Get() == RHS.Get();
		}

		template<typename RhsT>
		FORCEINLINE bool operator==(NULLPTR_TYPE) const
		{
			return !IsValid();
		}

		FORCEINLINE T* operator->() const
		{
			return Pointer;
		}

		FORCEINLINE T& operator*() const
		{
			return *Pointer;
		}

		FORCEINLINE T* Get() const
		{
			return Pointer;
		}

		FORCEINLINE Deleter& GetDeleter() noexcept
		{
			return static_cast<Deleter&>(*this);
		}

		FORCEINLINE const Deleter& GetDeleter() const noexcept
		{
			return static_cast<Deleter&>(*this);
		}

	private:
		T* Pointer;
	};
}