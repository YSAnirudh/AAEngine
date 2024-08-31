#pragma once

#include "CorePlatform.h"

//#if (AA_PLATFORM_HAS_AVX || AA_PLATFORM_HAS_AVX2 || AA_PLATFORM_HAS_FMA3 || AA_PLATFORM_HAS_FMA4)
//#include <immintrin.h> // AVX, AVX2, FMA
////#if AA_PLATFORM_HAS_SSE
//// #include <wmmintrin.h> // AES (NOT SUPPORTED)
////#endif
//#elif AA_PLATFORM_HAS_SSE4A
//#include <ammintrin.h> // SSE4A
//#elif AA_PLATFORM_HAS_SSE42
//#include <nmmintrin.h> // SSE4.2
//#elif AA_PLATFORM_HAS_SSE41
//#include <smmintrin.h> // SSE4.1
//#elif AA_PLATFORM_HAS_SSSE3
//#include <tmmintrin.h> // SSSE3
//#elif AA_PLATFORM_HAS_SSE3
//#include <pmmintrin.h> // SSE3
//#elif AA_PLATFORM_HAS_SSE2
//#include <emmintrin.h> // SSE2
//#endif

#include <immintrin.h>