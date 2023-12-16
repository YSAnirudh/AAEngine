#pragma once

#include "Core.h"

/*
* TIsReference - To check if T is a reference or not
*/
template<typename T> struct TIsReference { enum { Value = false }; };
template<typename T> struct TIsReference<T&> { enum { Value = true }; };
template<typename T> struct TIsReference<T&&> { enum { Value = true }; };

/*
* TIsLValueReference - To check if T is an lvalue reference or not
*/
template<typename T> struct TIsLValueReference { enum { Value = false }; };
template<typename T> struct TIsLValueReference<T&> { enum { Value = true }; };

/*
* TIsRValueReference - To check if T is an rvalue reference or not
*/
template<typename T> struct TIsRValueReference { enum { Value = false }; };
template<typename T> struct TIsRValueReference<T&&> { enum { Value = true }; };