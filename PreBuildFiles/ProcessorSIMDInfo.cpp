
// Check Compiler
#if defined (_MSC_VER)
	#include <intrin.h>
#elif defined (__INTEL_COMPILER)
	#error INTEL Compiler not supported
#elif defined(__GNUC__) || defined(__clang__)
	#error GNU/Clang Compilers not supported
#else
	#error Current Compiler not supported
#endif

// basic file operations
#include <iostream>
#include <fstream>
#include <stdexcept>

static inline void cpuidex(int* output, int function)
{
#if defined (_MSC_VER)
	__cpuidex(output, function, 0);
#elif defined (__INTEL_COMPILER)

#error INTEL Compiler not supported
	__cpuidex(output, function, 0);

#elif defined(__GNUC__) || defined(__clang__)

#error GNU/Clang Compilers not supported
	int a, b, c, d;
	__asm("cpuid" : "=a"(a), "=b"(b), "=c"(c), "=d"(d) : "a"(function), "c"(0) : );
	output[0] = a;
	output[1] = b;
	output[2] = c;
	output[3] = d;

#else
	// Assembly
	__asm {
		mov eax, function
		xor ecx, ecx
		cpuid;
		mov esi, output
			mov[esi], eax
			mov[esi + 4], ebx
			mov[esi + 8], ecx
			mov[esi + 12], edx
	}

#endif
}

// CHECKING SIMD
static inline void ShowCPUIDOutput()
{
	int Result = 0x00000000;

	int info[4];
	cpuidex(info, 0);
	int nIds = info[0];

	cpuidex(info, 0x80000000);
	unsigned nExIds = info[0];

	//  Detect Features
	if (nIds >= 0x00000001) {
		cpuidex(info, 0x00000001);
		Result |= int((info[3] & ((int)1 << 23)) != 0) << 0;
		Result |= int((info[3] & ((int)1 << 25)) != 0) << 1;
		Result |= int((info[3] & ((int)1 << 26)) != 0) << 2;
		Result |= int((info[2] & ((int)1 << 0)) != 0) << 3;
		Result |= int((info[2] & ((int)1 << 9)) != 0) << 4;
		Result |= int((info[2] & ((int)1 << 19)) != 0) << 5;
		Result |= int((info[2] & ((int)1 << 20)) != 0) << 6;
		Result |= int((info[2] & ((int)1 << 25)) != 0) << 7;
		Result |= int((info[2] & ((int)1 << 12)) != 0) << 8;
		Result |= int((info[2] & ((int)1 << 28)) != 0) << 9;
		Result |= int((info[2] & ((int)1 << 30)) != 0) << 10;
	}
	if (nIds >= 0x00000007) {
		cpuidex(info, 0x00000007);
		Result |= int((info[1] & ((int)1 << 5)) != 0) << 11;
		Result |= int((info[1] & ((int)1 << 3)) != 0) << 12;
		Result |= int((info[1] & ((int)1 << 8)) != 0) << 13;
		Result |= int((info[1] & ((int)1 << 19)) != 0) << 14;
		Result |= int((info[1] & ((int)1 << 29)) != 0) << 15;
		Result |= int((info[2] & ((int)1 << 0)) != 0) << 16;
		Result |= int((info[1] & ((int)1 << 16)) != 0) << 17;
		Result |= int((info[1] & ((int)1 << 28)) != 0) << 18;
		Result |= int((info[1] & ((int)1 << 26)) != 0) << 19;
		Result |= int((info[1] & ((int)1 << 27)) != 0) << 20;
		Result |= int((info[1] & ((int)1 << 31)) != 0) << 21;
		Result |= int((info[1] & ((int)1 << 30)) != 0) << 22;
		Result |= int((info[1] & ((int)1 << 17)) != 0) << 23;
		Result |= int((info[1] & ((int)1 << 21)) != 0) << 24;
		Result |= int((info[2] & ((int)1 << 1)) != 0) << 25;
	}
	if (nExIds >= 0x80000001) {
		cpuidex(info, 0x80000001);
		Result |= int((info[3] & ((int)1 << 29)) != 0) << 26;
		Result |= int((info[2] & ((int)1 << 5)) != 0) << 27;
		Result |= int((info[2] & ((int)1 << 6)) != 0) << 28;
		Result |= int((info[2] & ((int)1 << 16)) != 0) << 29;
		Result |= int((info[2] & ((int)1 << 11)) != 0) << 30;
	}

	std::ofstream OutFile;
	OutFile.open("../AAEngine/Source/Platform/PlatformProcessorDefines.h");
	if (!OutFile.is_open())
	{
		throw std::runtime_error("Could not open file");
	}
	OutFile << "//******************************************************\n";
	OutFile << "//** AA ENGINE Processor SIMD Support Information File *\n";
	OutFile << "//**  DO NOT CHANGE THIS FILE (Pre-Build Time File).   *\n";
	OutFile << "//******************************************************\n\n\n\n";


	//					Miscellaneous.
	OutFile << "//******************************************************\n";
	OutFile << "//********* MISCELLANEOUS ******************************\n";
	OutFile << "//******************************************************\n\n";
	//                  AA_PROCESSOR_SUPPORT_MMX;
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_MMX\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_MMX " << ((Result & (0x01 << 0)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_x64;
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_x64\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_x64 " << ((Result & (0x01 << 1)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_ABM;      // Advanced Bit Manipulation
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_ABM\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_ABM " << ((Result & (0x01 << 2)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_RDRAND;
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_RDRAND\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_RDRAND " << ((Result & (0x01 << 3)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_BMI1;
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_BMI1\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_BMI1 " << ((Result & (0x01 << 4)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_BMI2;
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_BMI2\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_BMI2 " << ((Result & (0x01 << 5)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_ADX;
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_ADX\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_ADX " << ((Result & (0x01 << 6)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_PREFETCHWT1;
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_PREFETCHWT1\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_PREFETCHWT1 " << ((Result & (0x01 << 7)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";


	//					SIMD: 128-bit
	OutFile << "//******************************************************\n";
	OutFile << "//********* SIMD - 128-Bit *****************************\n";
	OutFile << "//******************************************************\n\n";
	//                  AA_PROCESSOR_SUPPORT_SSE;
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_SSE\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_SSE " << ((Result & (0x01 << 8)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_SSE2;
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_SSE2\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_SSE2 " << ((Result & (0x01 << 9)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_SSE3;
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_SSE3\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_SSE3 " << ((Result & (0x01 << 10)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_SSSE3;
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_SSSE3\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_SSSE3 " << ((Result & (0x01 << 11)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_SSE41;
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_SSE41\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_SSE41 " << ((Result & (0x01 << 12)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_SSE42;
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_SSE42\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_SSE42 " << ((Result & (0x01 << 13)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_SSE4a;
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_SSE4a\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_SSE4a " << ((Result & (0x01 << 14)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_AES;
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_AES\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_AES " << ((Result & (0x01 << 15)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_SHA;
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_SHA\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_SHA " << ((Result & (0x01 << 16)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";

	//					SIMD: 256-bit
	OutFile << "//******************************************************\n";
	OutFile << "//********* SIMD - 256-Bit *****************************\n";
	OutFile << "//******************************************************\n\n";
	//                  AA_PROCESSOR_SUPPORT_AVX;
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_AVX\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_AVX " << ((Result & (0x01 << 17)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_XOP;
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_XOP\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_XOP " << ((Result & (0x01 << 18)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_FMA3;
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_FMA3\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_FMA3 " << ((Result & (0x01 << 19)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_FMA4;
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_FMA4\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_FMA4 " << ((Result & (0x01 << 20)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_AVX2;
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_AVX2\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_AVX2 " << ((Result & (0x01 << 21)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";

	//					SIMD: 512-bit
	OutFile << "//******************************************************\n";
	OutFile << "//********* SIMD - 512-Bit *****************************\n";
	OutFile << "//******************************************************\n\n";
	//                  AA_PROCESSOR_SUPPORT_AVX512F;    //  AVX512 Foundation
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_AVX512F\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_AVX512F " << ((Result & (0x01 << 22)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_AVX512CD;   //  AVX512 Conflict Detection
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_AVX512CD\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_AVX512CD " << ((Result & (0x01 << 23)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_AVX512PF;   //  AVX512 Prefetch
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_AVX512PF\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_AVX512PF " << ((Result & (0x01 << 24)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_AVX512ER;   //  AVX512 Exponential + Reciprocal
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_AVX512ER\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_AVX512ER " << ((Result & (0x01 << 25)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_AVX512VL;   //  AVX512 Vector Length Extensions
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_AVX512VL\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_AVX512VL " << ((Result & (0x01 << 26)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_AVX512BW;   //  AVX512 Byte + Word
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_AVX512BW\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_AVX512BW " << ((Result & (0x01 << 27)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_AVX512DQ;   //  AVX512 Doubleword + Quadword
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_AVX512DQ\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_AVX512DQ " << ((Result & (0x01 << 28)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_AVX512IFMA; //  AVX512 Integer 52-bit Fused Multiply-Add
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_AVX512IFMA\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_AVX512IFMA " << ((Result & (0x01 << 29)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n\n";
	//                  AA_PROCESSOR_SUPPORT_AVX512VBMI; //  AVX512 Vector Byte Manipulation Instructions
	OutFile << "#ifndef AA_PROCESSOR_SUPPORT_AVX512VBMI\n";
	OutFile << "	#define AA_PROCESSOR_SUPPORT_AVX512VBMI " << ((Result & (0x01 << 30)) > 0 ? "1" : "0") << "\n";
	OutFile << "#endif\n";

	OutFile.close();
}

int main()
{
	try {
		ShowCPUIDOutput();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << "\n";
		return -1;
	}

	return 0;
}