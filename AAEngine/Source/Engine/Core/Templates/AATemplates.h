#pragma once

#include "Core.h"
#include "RemoveReference.h"
#include "AATypeTraits.h"


// ----- MEMORY RELATED TEMPALTES -----

/*
* std::move of AAEngine
* Converts a reference to an rValue reference
* 
* @param MoveThis - The variable that being cast
* 
* @returns rvalue reference of MoveThis
*/
template<typename T>
FORCEINLINE typename TRemoveReference<T>::Type&& Move(T&& MoveThis)
{
	typedef typename TRemoveReference<T>::Type CastType;

	AA_CORE_ASSERT(TIsLValueReference<T>::Value, "Trying to Move cast an lvalue reference");

	return static_cast<CastType&&>(MoveThis);
}

/*
* std::forward of AAEngine
*
* @param ForwardThis - rvalue ref
*
* @returns rvalue reference of MoveThis
*/
template<typename T>
FORCEINLINE T&& Forward(typename TRemoveReference<T>::Type&& ForwardThis)
{
	return static_cast<T&&>(ForwardThis);
}

/*
* std::forward of AAEngine
*
* @param ForwardThis - lvalue ref
*
* @returns rvalue reference of MoveThis
*/
template<typename T>
FORCEINLINE T&& Forward(typename TRemoveReference<T>::Type& ForwardThis)
{
	return (T&&)ForwardThis;
}
