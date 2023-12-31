#pragma once

#include "Core/Core.h"

#if AA_PLATFORM_ENABLE_SIMD_INTRINSICS_SSE2
#include "Memory/IncludesMemory.h"
#include "Math/MathForwards.h"

#include <immintrin.h>

namespace AAEngine {
namespace Math {

	typedef __m128 VectorRegister4Float;

	typedef __m128d VectorRegister2Double;

	struct alignas(16) VectorRegister4Double
	{
		VectorRegister2Double XY;
		VectorRegister2Double ZW;

		VectorRegister4Double() = default;

		VectorRegister4Double(const VectorRegister2Double& InXY, const VectorRegister2Double& InZW)
		{
			XY = InXY;
			ZW = InZW;
		}
	};

	FORCEINLINE VectorRegister4Float MakeVectorRegister4Float(float A, float B, float C, float D)
	{
		return _mm_setr_ps(A, B, C, D);
	}

	FORCEINLINE VectorRegister4Double MakeVectorRegister4Double(double A, double B, double C, double D)
	{
		return VectorRegister4Double(_mm_setr_pd(A, B), _mm_setr_pd(C, D));
	}

	FORCEINLINE VectorRegister4Float VectorLoadAligned(const float* Ptr)
	{
		return _mm_load_ps((const float*)Ptr);
	}

	FORCEINLINE VectorRegister4Double VectorLoadAligned(const double* Ptr)
	{
		return VectorRegister4Double(_mm_load_pd((const double*)Ptr), _mm_load_pd((const double*)(Ptr + 2)));
	}

	FORCEINLINE void VectorStoreAligned(const VectorRegister4Float& Reg, float* Dest)
	{
		_mm_store_ps(Dest, Reg);
	}

	FORCEINLINE void VectorStoreAligned(const VectorRegister4Double& Reg, double* Dest)
	{
		_mm_store_pd(Dest, Reg.XY);
		_mm_store_pd(Dest + 2, Reg.ZW);
	}

#define SHUFFLEMASK(A0,A1,B2,B3) ( (A0) | ((A1)<<2) | ((B2)<<4) | ((B3)<<6) )

#define SHUFFLEMASK2(A0,A1) ((A0) | ((A1)<<1))

	// TO DO: Double Support Later
	/*template<int Index1, int Index2, int Index3, int Index4>
	FORCEINLINE VectorRegister4Double VectorShuffleTemplate(const VectorRegister4Double& Vec1, const VectorRegister4Double& Vec2)
	{
		AA_CORE_ASSERT(int(Index0 >= 0 && Index0 <= 3 && Index1 >= 0 && Index1 <= 3 && Index2 >= 0 && Index2 <= 3 && Index3 >= 0 && Index3 <= 3), "Invalid Index");
		_mm_shuffle_pd(Vec1, Vec2, SHUFFLEMASK(Index1, Index2, Index3, Index4));
	}*/

	template<int Index>
	FORCEINLINE VectorRegister4Double VectorReplicateTemplate(const VectorRegister4Double& Vec)
	{
		static_assert(int(Index >= 0 && Index <= 3), "Invalid Index");
		return VectorShuffleTemplate<Index, Index, Index, Index>(Vec, Vec);
	}

	template<int Index0, int Index1, int Index2, int Index3>
	FORCEINLINE VectorRegister4Double VectorSwizzleTemplate(const VectorRegister4Double& Vec)
	{
		static_assert(int(Index0 >= 0 && Index0 <= 3 && Index1 >= 0 && Index1 <= 3 && Index2 >= 0 && Index2 <= 3 && Index3 >= 0 && Index3 <= 3), "Invalid Index");
		_mm_shuffle_pd(Vec.XY, Vec.XY, SHUFFLEMASK2(Index0, Index1));
		_mm_shuffle_pd(Vec.ZW, Vec.ZW, SHUFFLEMASK2(Index2, Index3));
		return MakeVectorRegister4Double(0.0, 0.0, 0.0, 0.0);
	}

	template<int Index0, int Index1, int Index2, int Index3>
	FORCEINLINE VectorRegister4Double VectorShuffleTemplate(const VectorRegister4Double& Vec1, const VectorRegister4Double& Vec2)
	{
		static_assert(int(Index0 >= 0 && Index0 <= 3 && Index1 >= 0 && Index1 <= 3 && Index2 >= 0 && Index2 <= 3 && Index3 >= 0 && Index3 <= 3), "Invalid Index");
		_mm_shuffle_pd(Vec1.XY, Vec2.XY, SHUFFLEMASK2(Index0, Index1));
		_mm_shuffle_pd(Vec1.ZW, Vec2.ZW, SHUFFLEMASK2(Index2, Index3));
		return MakeVectorRegister4Double(0.0, 0.0, 0.0, 0.0);
	}

	template<int Index>
	FORCEINLINE VectorRegister4Float VectorReplicateTemplate(const VectorRegister4Float& Vec)
	{
		static_assert(int(Index >= 0 && Index <= 3), "Invalid Index");
		return VectorShuffleTemplate<Index, Index, Index, Index>(Vec, Vec);
	}

	template<int Index0, int Index1, int Index2, int Index3>
	FORCEINLINE VectorRegister4Float VectorSwizzleTemplate(const VectorRegister4Float& Vec)
	{
		static_assert(int(Index0 >= 0 && Index0 <= 3 && Index1 >= 0 && Index1 <= 3 && Index2 >= 0 && Index2 <= 3 && Index3 >= 0 && Index3 <= 3), "Invalid Index");
		return _mm_shuffle_ps(Vec, Vec, SHUFFLEMASK(Index0, Index1, Index2, Index3));
	}

	template<int Index0, int Index1, int Index2, int Index3>
	FORCEINLINE VectorRegister4Float VectorShuffleTemplate(const VectorRegister4Float& Vec1, const VectorRegister4Float& Vec2)
	{
		//static_assert(int(Index0 >= 0 && Index0 <= 3 && Index1 >= 0 && Index1 <= 3 && Index2 >= 0 && Index2 <= 3 && Index3 >= 0 && Index3 <= 3), "Invalid Index");
		return _mm_shuffle_ps(Vec1, Vec2, SHUFFLEMASK(Index0, Index1, Index2, Index3));
	}

	/**
	* Replicates one element into all four elements and returns the new vector.
	*
	* @param Vec			Source vector
	* @param ElementIndex	Index (0-3) of the element to replicate
	* @return				VectorRegister( Vec[ElementIndex], Vec[ElementIndex], Vec[ElementIndex], Vec[ElementIndex] )
	*/
#define VectorReplicate(Vec, ElementIndex)			VectorShuffleTemplate<ElementIndex, ElementIndex, ElementIndex, ElementIndex>(Vec, Vec)

	/**
	* Swizzles the 4 components of a vector and returns the result.
	*
	* @param Vec		Source vector
	* @param X			Index for which component to use for X (literal 0-3)
	* @param Y			Index for which component to use for Y (literal 0-3)
	* @param Z			Index for which component to use for Z (literal 0-3)
	* @param W			Index for which component to use for W (literal 0-3)
	* @return			The swizzled vector
	*/
#define VectorSwizzle(Vec, X, Y, Z, W)				VectorSwizzleTemplate<X, Y, Z, W>(Vec)

	/**
	* Creates a vector through selecting two components from each vector via a shuffle mask.
	*
	* @param Vec1		Source vector1
	* @param Vec2		Source vector2
	* @param X			Index for which component of Vector1 to use for X (literal 0-3)
	* @param Y			Index for which component to Vector1 to use for Y (literal 0-3)
	* @param Z			Index for which component to Vector2 to use for Z (literal 0-3)
	* @param W			Index for which component to Vector2 to use for W (literal 0-3)
	* @return			The swizzled vector
	*/
#define VectorShuffle(Vec1, Vec2, X, Y, Z, W)		VectorShuffleTemplate<X, Y, Z, W>(Vec1, Vec2)



	FORCEINLINE VectorRegister4Float VectorAdd(const VectorRegister4Float& VecReg1, const VectorRegister4Float& VecReg2)
	{
		return _mm_add_ps(VecReg1, VecReg2);
	}

	FORCEINLINE VectorRegister4Double VectorAdd(const VectorRegister4Double& VecReg1, const VectorRegister4Double& VecReg2)
	{
		VectorRegister4Double ResultVec;
		ResultVec.XY = _mm_add_pd(VecReg1.XY, VecReg2.XY);
		ResultVec.ZW = _mm_add_pd(VecReg1.ZW, VecReg2.ZW);
		return ResultVec;
	}

	FORCEINLINE VectorRegister4Float VectorScalarAdd(const VectorRegister4Float& VecReg1, float Val)
	{
		return _mm_add_ps(VecReg1, _mm_set1_ps(Val));
	}

	FORCEINLINE VectorRegister4Double VectorScalarAdd(const VectorRegister4Double& VecReg1, float Val)
	{
		VectorRegister4Double ResultVec;
		VectorRegister2Double ValVec = _mm_set1_pd(Val);
		ResultVec.XY = _mm_add_pd(VecReg1.XY, ValVec);
		ResultVec.ZW = _mm_add_pd(VecReg1.ZW, ValVec);
		return ResultVec;
	}

	FORCEINLINE VectorRegister4Float VectorSubtract(const VectorRegister4Float& VecReg1, const VectorRegister4Float& VecReg2)
	{
		return _mm_sub_ps(VecReg1, VecReg2);
	}

	FORCEINLINE VectorRegister4Double VectorSubtract(const VectorRegister4Double& VecReg1, const VectorRegister4Double& VecReg2)
	{
		VectorRegister4Double ResultVec;
		ResultVec.XY = _mm_sub_pd(VecReg1.XY, VecReg2.XY);
		ResultVec.ZW = _mm_sub_pd(VecReg1.ZW, VecReg2.ZW);
		return ResultVec;
	}

	FORCEINLINE VectorRegister4Float VectorScalarSubtract(const VectorRegister4Float& VecReg1, float Val)
	{
		return _mm_sub_ps(VecReg1, _mm_set1_ps(Val));
	}

	FORCEINLINE VectorRegister4Double VectorScalarSubtract(const VectorRegister4Double& VecReg1, float Val)
	{
		VectorRegister4Double ResultVec;
		VectorRegister2Double ValVec = _mm_set1_pd(Val);
		ResultVec.XY = _mm_sub_pd(VecReg1.XY, ValVec);
		ResultVec.ZW = _mm_sub_pd(VecReg1.ZW, ValVec);
		return ResultVec;
	}

	FORCEINLINE VectorRegister4Float VectorMultiply(const VectorRegister4Float& VecReg1, const VectorRegister4Float& VecReg2)
	{
		return _mm_mul_ps(VecReg1, VecReg2);
	}

	FORCEINLINE VectorRegister4Double VectorMultiply(const VectorRegister4Double& VecReg1, const VectorRegister4Double& VecReg2)
	{
		VectorRegister4Double ResultVec;
		ResultVec.XY = _mm_mul_pd(VecReg1.XY, VecReg2.XY);
		ResultVec.ZW = _mm_mul_pd(VecReg1.ZW, VecReg2.ZW);
		return ResultVec;
	}

	FORCEINLINE VectorRegister4Float VectorMultiplyAdd(const VectorRegister4Float& VecReg1, const VectorRegister4Float& VecReg2, const VectorRegister4Float& VecReg3)
	{
#if AA_PROCESSOR_SUPPORT_FMA3
		return _mm_fmadd_ps(VecReg1, VecReg2, VecReg3);
#else
		return VectorAdd(VectorMultiply(VecReg1, VecReg2), VecReg3);
#endif
	}

	FORCEINLINE VectorRegister4Double VectorMultiplyAdd(const VectorRegister4Double& VecReg1, const VectorRegister4Double& VecReg2, const VectorRegister4Double& VecReg3)
	{
#if AA_PROCESSOR_SUPPORT_FMA3
		VectorRegister4Double ResultVec;
		ResultVec.XY = _mm_fmadd_pd(VecReg1.XY, VecReg2.XY, VecReg3.XY);
		ResultVec.ZW = _mm_fmadd_pd(VecReg1.ZW, VecReg2.ZW, VecReg3.ZW);
		return ResultVec;
#else
		return VectorAdd(VectorMultiply(VecReg1, VecReg2), VecReg3);
#endif

	}

	FORCEINLINE VectorRegister4Float VectorScalarMultiply(const VectorRegister4Float& VecReg1, float Val)
	{
		return _mm_mul_ps(VecReg1, _mm_set1_ps(Val));
	}

	FORCEINLINE VectorRegister4Double VectorScalarMultiply(const VectorRegister4Double& VecReg1, float Val)
	{
		VectorRegister4Double ResultVec;
		VectorRegister2Double ValVec = _mm_set1_pd(Val);
		ResultVec.XY = _mm_mul_pd(VecReg1.XY, ValVec);
		ResultVec.ZW = _mm_mul_pd(VecReg1.ZW, ValVec);
		return ResultVec;
	}

	FORCEINLINE VectorRegister4Float VectorDivide(const VectorRegister4Float& VecReg1, const VectorRegister4Float& VecReg2)
	{
		return _mm_div_ps(VecReg1, VecReg2);
	}

	FORCEINLINE VectorRegister4Double VectorDivide(const VectorRegister4Double& VecReg1, const VectorRegister4Double& VecReg2)
	{
		VectorRegister4Double ResultVec;
		ResultVec.XY = _mm_div_pd(VecReg1.XY, VecReg2.XY);
		ResultVec.ZW = _mm_div_pd(VecReg1.ZW, VecReg2.ZW);
		return ResultVec;
	}

	FORCEINLINE VectorRegister4Float VectorScalarDivide(const VectorRegister4Float& VecReg1, float Val)
	{
		return _mm_div_ps(VecReg1, _mm_set1_ps(Val));
	}

	FORCEINLINE VectorRegister4Double VectorScalarDivide(const VectorRegister4Double& VecReg1, float Val)
	{
		VectorRegister4Double ResultVec;
		VectorRegister2Double ValVec = _mm_set1_pd(Val);
		ResultVec.XY = _mm_div_pd(VecReg1.XY, ValVec);
		ResultVec.ZW = _mm_div_pd(VecReg1.ZW, ValVec);
		return ResultVec;
	}

	FORCEINLINE VectorRegister4Float VectorMatrixMultiply(const VectorRegister4Float& VecReg, const FMatrix44f* Mat)
	{
		typedef float Float4x4[4][4];
		const Float4x4& M = *((const Float4x4*)Mat);

		VectorRegister4Float MatRow[4];

		MatRow[0] = VectorLoadAligned(M[0]);
		MatRow[1] = VectorLoadAligned(M[1]);
		MatRow[2] = VectorLoadAligned(M[2]);
		MatRow[3] = VectorLoadAligned(M[3]);

		VectorRegister4Float ResultVec;

		ResultVec = VectorMultiply(VectorReplicate(VecReg, 0), MatRow[0]);
		ResultVec = VectorMultiplyAdd(VectorReplicate(VecReg, 1), MatRow[1], ResultVec);
		ResultVec = VectorMultiplyAdd(VectorReplicate(VecReg, 2), MatRow[2], ResultVec);
		ResultVec = VectorMultiplyAdd(VectorReplicate(VecReg, 3), MatRow[3], ResultVec);

		return ResultVec;
	}

	FORCEINLINE VectorRegister4Double VectorMatrixMultiply(const VectorRegister4Double& VecReg, const FMatrix44d* Mat)
	{
		typedef double Double4x4[4][4];
		const Double4x4& M = *((const Double4x4*)Mat);

		VectorRegister4Double MatRow[4];

		MatRow[0] = VectorLoadAligned(M[0]);
		MatRow[1] = VectorLoadAligned(M[1]);
		MatRow[2] = VectorLoadAligned(M[2]);
		MatRow[3] = VectorLoadAligned(M[3]);

		VectorRegister4Double ResultVec;

		ResultVec = VectorMultiply(VectorReplicate(VecReg, 0), MatRow[0]);
		ResultVec = VectorMultiplyAdd(VectorReplicate(VecReg, 1), MatRow[1], ResultVec);
		ResultVec = VectorMultiplyAdd(VectorReplicate(VecReg, 2), MatRow[2], ResultVec);
		ResultVec = VectorMultiplyAdd(VectorReplicate(VecReg, 3), MatRow[3], ResultVec);

		return ResultVec;
	}

	FORCEINLINE void MatrixMultiply(FMatrix44f* Result, const FMatrix44f* Mat1, const FMatrix44f* Mat2)
	{

		const VectorRegister4Float* M1 = ((const VectorRegister4Float*)Mat1);
		const VectorRegister4Float* M2 = ((const VectorRegister4Float*)Mat2);
		VectorRegister4Float* ResultMat = (VectorRegister4Float*)Result;

		VectorRegister4Float ResRow, R0, R1, R2;
		ResRow = VectorMultiply	  (M2[0], VectorReplicate(M1[0], 0));
		ResRow = VectorMultiplyAdd(M2[1], VectorReplicate(M1[0], 1), ResRow);
		ResRow = VectorMultiplyAdd(M2[2], VectorReplicate(M1[0], 2), ResRow);
		R0 = VectorMultiplyAdd(M2[3], VectorReplicate(M1[0], 3), ResRow);


		ResRow = VectorMultiply   (M2[0], VectorReplicate(M1[1], 0));
		ResRow = VectorMultiplyAdd(M2[1], VectorReplicate(M1[1], 1), ResRow);
		ResRow = VectorMultiplyAdd(M2[2], VectorReplicate(M1[1], 2), ResRow);
		R1 = VectorMultiplyAdd(M2[3], VectorReplicate(M1[1], 3), ResRow);


		ResRow = VectorMultiply   (M2[0], VectorReplicate(M1[2], 0));
		ResRow = VectorMultiplyAdd(M2[1], VectorReplicate(M1[2], 1), ResRow);
		ResRow = VectorMultiplyAdd(M2[2], VectorReplicate(M1[2], 2), ResRow);
		R2 = VectorMultiplyAdd(M2[3], VectorReplicate(M1[2], 3), ResRow);


		ResRow = VectorMultiply   (M2[0], VectorReplicate(M1[3], 0));
		ResRow = VectorMultiplyAdd(M2[1], VectorReplicate(M1[3], 1), ResRow);
		ResRow = VectorMultiplyAdd(M2[2], VectorReplicate(M1[3], 2), ResRow);
		ResRow = VectorMultiplyAdd(M2[3], VectorReplicate(M1[3], 3), ResRow);

		ResultMat[0] = R0;
		ResultMat[1] = R1;
		ResultMat[2] = R2;
		ResultMat[3] = ResRow;
	}

	FORCEINLINE void MatrixMultiply(FMatrix44d* Result, const FMatrix44d* Mat1, const FMatrix44d* Mat2)
	{
		const VectorRegister4Double* A = (const VectorRegister4Double*)Mat1;
		const VectorRegister4Double* B = (const VectorRegister4Double*)Mat2;
		VectorRegister4Double* R = (VectorRegister4Double*)Result;
		VectorRegister4Double Temp, R0, R1, R2;

		// First row of result (Matrix1[0] * Matrix2).
		Temp = VectorMultiply(VectorReplicate(A[0], 0), B[0]);
		Temp = VectorMultiplyAdd(VectorReplicate(A[0], 1), B[1], Temp);
		Temp = VectorMultiplyAdd(VectorReplicate(A[0], 2), B[2], Temp);
		R0 = VectorMultiplyAdd(VectorReplicate(A[0], 3), B[3], Temp);

		// Second row of result (Matrix1[1] * Matrix2).
		Temp = VectorMultiply(VectorReplicate(A[1], 0), B[0]);
		Temp = VectorMultiplyAdd(VectorReplicate(A[1], 1), B[1], Temp);
		Temp = VectorMultiplyAdd(VectorReplicate(A[1], 2), B[2], Temp);
		R1 = VectorMultiplyAdd(VectorReplicate(A[1], 3), B[3], Temp);

		// Third row of result (Matrix1[2] * Matrix2).
		Temp = VectorMultiply(VectorReplicate(A[2], 0), B[0]);
		Temp = VectorMultiplyAdd(VectorReplicate(A[2], 1), B[1], Temp);
		Temp = VectorMultiplyAdd(VectorReplicate(A[2], 2), B[2], Temp);
		R2 = VectorMultiplyAdd(VectorReplicate(A[2], 3), B[3], Temp);

		// Fourth row of result (Matrix1[3] * Matrix2).
		Temp = VectorMultiply(VectorReplicate(A[3], 0), B[0]);
		Temp = VectorMultiplyAdd(VectorReplicate(A[3], 1), B[1], Temp);
		Temp = VectorMultiplyAdd(VectorReplicate(A[3], 2), B[2], Temp);
		Temp = VectorMultiplyAdd(VectorReplicate(A[3], 3), B[3], Temp);

		// Store result. Must not be done during steps above in case source and destination are the same.
		R[0] = R0;
		R[1] = R1;
		R[2] = R2;
		R[3] = Temp;
	}

	FORCEINLINE void MatrixInverse(FMatrix44f* Result, const FMatrix44f* Mat1)
	{
		typedef float Float4x4[4][4];
		const Float4x4& M = *((const Float4x4*)Mat1);
		Float4x4 Res;

		Float4x4 Temp;
		Temp[0][0] = M[2][2] * M[3][3] - M[2][3] * M[3][2];
		Temp[0][1] = M[2][1] * M[3][3] - M[2][3] * M[3][1];
		Temp[0][2] = M[2][1] * M[3][2] - M[2][2] * M[3][1];

		Temp[1][0] = M[2][2] * M[3][3] - M[2][3] * M[3][2];
		Temp[1][1] = M[2][0] * M[3][3] - M[2][3] * M[3][0];
		Temp[1][2] = M[2][0] * M[3][2] - M[2][2] * M[3][0];

		Temp[2][0] = M[2][1] * M[3][3] - M[2][3] * M[3][1];
		Temp[2][1] = M[2][0] * M[3][3] - M[2][3] * M[3][0];
		Temp[2][2] = M[2][0] * M[3][1] - M[2][1] * M[3][0];

		Temp[3][0] = M[2][1] * M[3][2] - M[2][2] * M[3][1];
		Temp[3][1] = M[2][0] * M[3][2] - M[2][2] * M[3][0];
		Temp[3][2] = M[2][0] * M[3][1] - M[2][1] * M[3][0];

		float Det[4];
		Det[0] = ((M[1][1] * Temp[0][0]) - (M[1][2] * Temp[0][1]) + (M[1][3] * Temp[0][2]));
		Det[1] = ((M[1][0] * Temp[1][0]) - (M[1][2] * Temp[1][1]) + (M[1][3] * Temp[1][2]));
		Det[2] = ((M[1][0] * Temp[2][0]) - (M[1][1] * Temp[2][1]) + (M[1][3] * Temp[2][2]));
		Det[3] = ((M[1][0] * Temp[3][0]) - (M[1][1] * Temp[3][1]) + (M[1][2] * Temp[3][2]));

		float Determinant = Det[0] * M[0][0] - Det[1] * M[0][1] + Det[2] * M[0][2] - Det[3] * M[0][3];

		float OneByDet = 1.0f / Determinant;

		Res[0][0] = OneByDet * Det[0];
		Res[1][0] = -OneByDet * Det[1];
		Res[2][0] = OneByDet * Det[2];
		Res[3][0] = -OneByDet * Det[3];

		Res[0][1] = -OneByDet * ((M[0][1] * Temp[0][0]) - (M[0][2] * Temp[0][1]) + (M[0][3] * Temp[0][2]));
		Res[1][1] = OneByDet * ((M[0][0] * Temp[1][0]) - (M[0][2] * Temp[1][1]) + (M[0][3] * Temp[1][2]));
		Res[2][1] = -OneByDet * ((M[0][0] * Temp[2][0]) - (M[0][1] * Temp[2][1]) + (M[0][3] * Temp[2][2]));
		Res[3][1] = OneByDet * ((M[0][0] * Temp[3][0]) - (M[0][1] * Temp[3][1]) + (M[0][2] * Temp[3][2]));

		Res[0][2] = OneByDet * ((M[0][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2])) - (M[0][2] * (M[1][1] * M[3][3] - M[1][3] * M[3][1])) + (M[0][3] * (M[1][1] * M[3][2] - M[1][2] * M[3][1])));
		Res[1][2] = -OneByDet * (((M[0][0] * (M[1][2] * M[3][3] - M[1][3] * M[3][2])) - (M[0][2] * (M[1][0] * M[3][3] - M[1][3] * M[3][0])) + (M[0][3] * (M[1][0] * M[3][2] - M[1][2] * M[3][0]))));
		Res[2][2] = OneByDet * ((M[0][0] * (M[1][1] * M[3][3] - M[1][3] * M[3][1])) - (M[0][1] * (M[1][0] * M[3][3] - M[1][3] * M[3][0])) + (M[0][3] * (M[1][0] * M[3][1] - M[1][1] * M[3][0])));
		Res[3][2] = -OneByDet * (((M[0][0] * (M[1][1] * M[3][2] - M[1][2] * M[3][1])) - (M[0][1] * (M[1][0] * M[3][2] - M[1][2] * M[3][0])) + (M[0][2] * (M[1][0] * M[3][1] - M[1][1] * M[3][0]))));

		Res[0][3] = -OneByDet * (((M[0][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2])) - (M[0][2] * (M[1][1] * M[2][3] - M[1][3] * M[2][1])) + (M[0][3] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]))));
		Res[1][3] = OneByDet * ((M[0][0] * (M[1][2] * M[2][3] - M[1][3] * M[2][2])) - (M[0][2] * (M[1][0] * M[2][3] - M[1][3] * M[2][0])) + (M[0][3] * (M[1][0] * M[2][2] - M[1][2] * M[2][0])));
		Res[2][3] = -OneByDet * (((M[0][0] * (M[1][1] * M[2][3] - M[1][3] * M[2][1])) - (M[0][1] * (M[1][0] * M[2][3] - M[1][3] * M[2][0])) + (M[0][3] * (M[1][0] * M[2][1] - M[1][1] * M[2][0]))));
		Res[3][3] = OneByDet * ((M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1])) - (M[0][1] * (M[1][0] * M[2][2] - M[1][2] * M[2][0])) + (M[0][2] * (M[1][0] * M[2][1] - M[1][1] * M[2][0])));

		FMemory::MemCopy(Result, &Res, 16 * sizeof(float));
	}

	FORCEINLINE void MatrixInverse(FMatrix44d* Result, const FMatrix44d* Mat1)
	{
		typedef double Double4x4[4][4];
		const Double4x4& M = *((const Double4x4*)Mat1);
		Double4x4 Res;

		Double4x4 Temp;
		Temp[0][0] = M[2][2] * M[3][3] - M[2][3] * M[3][2];
		Temp[0][1] = M[2][1] * M[3][3] - M[2][3] * M[3][1];
		Temp[0][2] = M[2][1] * M[3][2] - M[2][2] * M[3][1];

		Temp[1][0] = M[2][2] * M[3][3] - M[2][3] * M[3][2];
		Temp[1][1] = M[2][0] * M[3][3] - M[2][3] * M[3][0];
		Temp[1][2] = M[2][0] * M[3][2] - M[2][2] * M[3][0];

		Temp[2][0] = M[2][1] * M[3][3] - M[2][3] * M[3][1];
		Temp[2][1] = M[2][0] * M[3][3] - M[2][3] * M[3][0];
		Temp[2][2] = M[2][0] * M[3][1] - M[2][1] * M[3][0];

		Temp[3][0] = M[2][1] * M[3][2] - M[2][2] * M[3][1];
		Temp[3][1] = M[2][0] * M[3][2] - M[2][2] * M[3][0];
		Temp[3][2] = M[2][0] * M[3][1] - M[2][1] * M[3][0];

		double Det[4];
		Det[0] = ((M[1][1] * Temp[0][0]) - (M[1][2] * Temp[0][1]) + (M[1][3] * Temp[0][2]));
		Det[1] = ((M[1][0] * Temp[1][0]) - (M[1][2] * Temp[1][1]) + (M[1][3] * Temp[1][2]));
		Det[2] = ((M[1][0] * Temp[2][0]) - (M[1][1] * Temp[2][1]) + (M[1][3] * Temp[2][2]));
		Det[3] = ((M[1][0] * Temp[3][0]) - (M[1][1] * Temp[3][1]) + (M[1][2] * Temp[3][2]));

		double Determinant = Det[0] * M[0][0] - Det[1] * M[0][1] + Det[2] * M[0][2] - Det[3] * M[0][3];

		double OneByDet = 1.0f / Determinant;

		Res[0][0] = OneByDet * Det[0];
		Res[1][0] = -OneByDet * Det[1];
		Res[2][0] = OneByDet * Det[2];
		Res[3][0] = -OneByDet * Det[3];

		Res[0][1] = -OneByDet * ((M[0][1] * Temp[0][0]) - (M[0][2] * Temp[0][1]) + (M[0][3] * Temp[0][2]));
		Res[1][1] = OneByDet * ((M[0][0] * Temp[1][0]) - (M[0][2] * Temp[1][1]) + (M[0][3] * Temp[1][2]));
		Res[2][1] = -OneByDet * ((M[0][0] * Temp[2][0]) - (M[0][1] * Temp[2][1]) + (M[0][3] * Temp[2][2]));
		Res[3][1] = OneByDet * ((M[0][0] * Temp[3][0]) - (M[0][1] * Temp[3][1]) + (M[0][2] * Temp[3][2]));

		Res[0][2] = ((M[0][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2])) - (M[0][2] * (M[1][1] * M[3][3] - M[1][3] * M[3][1])) + (M[0][3] * (M[1][1] * M[3][2] - M[1][2] * M[3][1])));
		Res[1][2] = -(((M[0][0] * (M[1][2] * M[3][3] - M[1][3] * M[3][2])) - (M[0][2] * (M[1][0] * M[3][3] - M[1][3] * M[3][0])) + (M[0][3] * (M[1][0] * M[3][2] - M[1][2] * M[3][0]))));
		Res[2][2] = ((M[0][0] * (M[1][1] * M[3][3] - M[1][3] * M[3][1])) - (M[0][1] * (M[1][0] * M[3][3] - M[1][3] * M[3][0])) + (M[0][3] * (M[1][0] * M[3][1] - M[1][1] * M[3][0])));
		Res[3][2] = -(((M[0][0] * (M[1][1] * M[3][2] - M[1][2] * M[3][1])) - (M[0][1] * (M[1][0] * M[3][2] - M[1][2] * M[3][0])) + (M[0][2] * (M[1][0] * M[3][1] - M[1][1] * M[3][0]))));

		Res[0][3] = -(((M[0][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2])) - (M[0][2] * (M[1][1] * M[2][3] - M[1][3] * M[2][1])) + (M[0][3] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]))));
		Res[1][3] = ((M[0][0] * (M[1][2] * M[2][3] - M[1][3] * M[2][2])) - (M[0][2] * (M[1][0] * M[2][3] - M[1][3] * M[2][0])) + (M[0][3] * (M[1][0] * M[2][2] - M[1][2] * M[2][0])));
		Res[2][3] = -(((M[0][0] * (M[1][1] * M[2][3] - M[1][3] * M[2][1])) - (M[0][1] * (M[1][0] * M[2][3] - M[1][3] * M[2][0])) + (M[0][3] * (M[1][0] * M[2][1] - M[1][1] * M[2][0]))));
		Res[3][3] = ((M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1])) - (M[0][1] * (M[1][0] * M[2][2] - M[1][2] * M[2][0])) + (M[0][2] * (M[1][0] * M[2][1] - M[1][1] * M[2][0])));

		FMemory::MemCopy(Result, &Res, 16 * sizeof(double));
	}

}
}
#endif