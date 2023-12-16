#pragma once

#include "Core.h"

// -- REFERENCE ----------------------------------------------------------------------
/*
* TIsReference - To check if T is a reference or not
*/
template<typename T> struct TIsReference					{ enum { Value = false }; };
template<typename T> struct TIsReference<T&>				{ enum { Value = true }; };
template<typename T> struct TIsReference<T&&>				{ enum { Value = true }; };

/*
* TIsLValueReference - To check if T is an lvalue reference or not
*/
template<typename T> struct TIsLValueReference				{ enum { Value = false }; };
template<typename T> struct TIsLValueReference<T&>			{ enum { Value = true }; };

/*
* TIsRValueReference - To check if T is an rvalue reference or not
*/
template<typename T> struct TIsRValueReference				{ enum { Value = false }; };
template<typename T> struct TIsRValueReference<T&&>			{ enum { Value = true }; };

// -----------------------------------------------------------------------------------
// 
// -- ARRAY --------------------------------------------------------------------------
/*
* TIsArray - To check if T is an array or not
*/
template<typename T> struct TIsArray						{ enum { Value = false }; };
template<typename T> struct TIsArray<T[]>					{ enum { Value = true }; };
template<typename T, int N> struct TIsArray<T[N]>			{ enum { Value = true }; };

/*
* TIsBoundedArray - To check if T is a bounded array or not
*/
template<typename T> struct TIsBoundedArray					{ enum { Value = false }; };
template<typename T, int N> struct TIsBoundedArray<T[N]>	{ enum { Value = true }; };

/*
* TIsUnBoundedArray - To check if T is an array or not
*/
template<typename T> struct TIsUnBoundedArray				{ enum { Value = false }; };
template<typename T> struct TIsUnBoundedArray<T[]>			{ enum { Value = true }; };

// -----------------------------------------------------------------------------------