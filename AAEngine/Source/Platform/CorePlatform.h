#pragma once

#include "PlatformProcessorDefines.h"

// Whether the CPU is x86/x64 (i.e. both 32 and 64-bit variants)
#ifndef AA_PLATFORM_CPU_X86_FAMILY
	#if (defined(_M_IX86) || defined(__i386__) || defined(_M_X64) || defined(__amd64__) || defined(__x86_64__)) && !defined(_M_ARM64EC)
		#define AA_PLATFORM_CPU_X86_FAMILY	1
	#else
		#define AA_PLATFORM_CPU_X86_FAMILY	0
	#endif
#endif

// Whether the CPU is AArch32/AArch64 (i.e. both 32 and 64-bit variants)
#ifndef PLATFORM_CPU_ARM_FAMILY
	#if (defined(__arm__) || defined(_M_ARM) || defined(__aarch64__) || defined(_M_ARM64) || defined(_M_ARM64EC))
		#define PLATFORM_CPU_ARM_FAMILY	1
	#else
		#define PLATFORM_CPU_ARM_FAMILY	0
	#endif
#endif

// MSVC COMPILER
#ifndef PLATFORM_COMPILER_MSVC
	#if defined(_MSC_VER)
		#include <intrin.h>
		#define PLATFORM_COMPILER_MSVC 1
	#else
		#define PLATFORM_COMPILER_MSVC 0
	#endif
#endif

// CLANG COMPILER - Not supported yet
#ifndef PLATFORM_COMPILER_CLANG
	#if defined(__clang__)
		#error Clang is not supported
		#define PLATFORM_COMPILER_CLANG 0
	#else
		#define PLATFORM_COMPILER_CLANG 0
	#endif
#endif

// Whether we want SIMD Enabled
#ifndef AA_PLATFORM_ENABLE_SIMD_INTRINSICS
	#define AA_PLATFORM_ENABLE_SIMD_INTRINSICS 1
#endif

#ifndef AA_PLATFORM_COMPILER_MAYBE_SUPPORTS_SIMD
	#if defined(AA_PLATFORM_CPU_X86_FAMILY)
		#define AA_PLATFORM_COMPILER_MAYBE_SUPPORTS_SIMD AA_PLATFORM_CPU_X86_FAMILY
	#else
		#define AA_PLATFORM_COMPILER_MAYBE_SUPPORTS_SIMD 0
	#endif
#endif

/*
* Compiler Support for SIMD is not related to the availability of simd.
* They are functions that are fast.
* TO DO:
* Fix #defines
* Add SSE to Vectors and measure
* Improve SSE support for both float and doubles
* 
*/

// SIMD Defines
#if 1
	#if AA_PROCESSOR_SUPPORT_SSE42
		#define AA_PLATFORM_HAS_SSE4_2 1
		#define AA_PLATFORM_HAS_SSE4_1 1
		#define AA_PLATFORM_HAS_SSE4 1
		#define AA_PLATFORM_HAS_SSE3 1
		#define AA_PLATFORM_HAS_SSE2 1
		#define AA_PLATFORM_HAS_SSE 1
	#elif AA_PROCESSOR_SUPPORT_SSE41
		#define AA_PLATFORM_HAS_SSE4_2 0
		#define AA_PLATFORM_HAS_SSE4_1 1
		#define AA_PLATFORM_HAS_SSE4 1
		#define AA_PLATFORM_HAS_SSE3 1
		#define AA_PLATFORM_HAS_SSE2 1
		#define AA_PLATFORM_HAS_SSE 1
	#elif AA_PROCESSOR_SUPPORT_SSE4
		#define AA_PLATFORM_HAS_SSE4_2 0
		#define AA_PLATFORM_HAS_SSE4_1 0
		#define AA_PLATFORM_HAS_SSE4 1
		#define AA_PLATFORM_HAS_SSE3 1
		#define AA_PLATFORM_HAS_SSE2 1
		#define AA_PLATFORM_HAS_SSE 1
	#elif AA_PROCESSOR_SUPPORT_SSE3
		#define AA_PLATFORM_HAS_SSE4_2 0
		#define AA_PLATFORM_HAS_SSE4_1 0
		#define AA_PLATFORM_HAS_SSE4 0
		#define AA_PLATFORM_HAS_SSE3 1
		#define AA_PLATFORM_HAS_SSE2 1
		#define AA_PLATFORM_HAS_SSE 1
	#elif AA_PROCESSOR_SUPPORT_SSE2
		#define AA_PLATFORM_HAS_SSE4_2 0
		#define AA_PLATFORM_HAS_SSE4_1 0
		#define AA_PLATFORM_HAS_SSE4 0
		#define AA_PLATFORM_HAS_SSE3 0
		#define AA_PLATFORM_HAS_SSE2 1
		#define AA_PLATFORM_HAS_SSE 1
	#else
		#error AAEngine needs SSE2 processors!
	#endif
#endif

/*
* __MMX__		x86 MMX
* __SSE__		x86 SSE
* __SSE2__		x86 SSE 2
* __AVX__		x86 AVX
* __VEC__		Alti Vec
* __ARM_NEON__	ARM NEON
* 
*/

#ifndef AA_PLATFORM_USING_SIMD
	#if AA_PLATFORM_COMPILER_MAYBE_SUPPORTS_SIMD && AA_PLATFORM_ENABLE_SIMD_INTRINSICS && (AA_PLATFORM_HAS_SSE || AA_PLATFORM_HAS_SSE2 || AA_PLATFORM_HAS_SSE3 || AA_PLATFORM_HAS_SSE4 || AA_PLATFORM_HAS_SSE4_1 || AA_PLATFORM_HAS_SSE4_2)
		#define AA_PLATFORM_USING_SIMD	1
	#else
		#define AA_PLATFORM_USING_SIMD 0
	#endif
#endif


#ifndef AA_PLATFORM_ENABLE_SIMD_INTRINSICS_SSE2
	#if AA_PLATFORM_HAS_SSE2 && AA_PLATFORM_COMPILER_MAYBE_SUPPORTS_SIMD && AA_PLATFORM_ENABLE_SIMD_INTRINSICS
		#define AA_PLATFORM_ENABLE_SIMD_INTRINSICS_SSE2	1
	#else
		#define AA_PLATFORM_ENABLE_SIMD_INTRINSICS_SSE2 0
	#endif
#endif