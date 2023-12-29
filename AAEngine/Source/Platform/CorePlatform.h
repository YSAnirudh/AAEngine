#pragma once

#ifndef AA_PLATFORM_CPU_X86_FAMILY
	#if (defined(_M_IX86) || defined(__i386__) || defined(_M_X64) || defined(__amd64__) || defined(__x86_64__)) && !defined(_M_ARM64EC)
		#define AA_PLATFORM_CPU_X86_FAMILY	1
	#else
		#define AA_PLATFORM_CPU_X86_FAMILY	0
	#endif
#endif

#ifndef AA_PLATFORM_ENABLE_SIMD_INTRINSICS
	#define AA_PLATFORM_ENABLE_SIMD_INTRINSICS 0
#endif

#ifndef AA_PLATFORM_ENABLE_SIMD_INTRINSICS_SSE
#define AA_PLATFORM_ENABLE_SIMD_INTRINSICS_SSE	AA_PLATFORM_CPU_X86_FAMILY
#endif