#pragma once


/*
* Includes a function to be instaniated only if predicate is true
* 
* TEnableIf<TIsLValueReference<T>, ReturnType>::Type Function(const T& Obj)
* {
* ...
* }
* 
* ReturnType is the return type of the Function
*/
template <bool Predicate, typename Result = void>
class TEnableIf;

template <typename Result>
class TEnableIf<true, Result>
{
public:
	typedef Result Type;
};