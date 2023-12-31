#pragma once

#include "Core/Core.h"

#if !AA_PLATFORM_USING_SIMD
#include "Memory/IncludesMemory.h"
#include "Math/MathForwards.h"

namespace AAEngine {
namespace Math {

	struct alignas(16) VectorRegister4Float
	{
		float V[4];
	};

	struct alignas(16) VectorRegister4Double
	{
		double V[4];
	};

	FORCEINLINE VectorRegister4Float MakeVectorRegister4Float(float A, float B, float C, float D)
	{
		VectorRegister4Float Res;
		Res.V[0] = A;
		Res.V[1] = B;
		Res.V[2] = C;
		Res.V[3] = D;
		return Res;
	}

	FORCEINLINE VectorRegister4Double MakeVectorRegister4Double(double A, double B, double C, double D)
	{
		VectorRegister4Double Res;
		Res.V[0] = A;
		Res.V[1] = B;
		Res.V[2] = C;
		Res.V[3] = D;
		return Res;
	}

	FORCEINLINE VectorRegister4Float VectorLoadAligned(const float* Ptr)
	{
		return MakeVectorRegister4Float(Ptr[0], Ptr[1], Ptr[2], Ptr[3]);
	}

	FORCEINLINE VectorRegister4Double VectorLoadAligned(const double* Ptr)
	{
		return MakeVectorRegister4Double(Ptr[0], Ptr[1], Ptr[2], Ptr[3]);
	}

	FORCEINLINE void VectorStoreAligned(const VectorRegister4Float& Reg, float* Dest)
	{
		FMemory::MemCopy(Dest, &Reg, 4 * sizeof(float));
	}

	FORCEINLINE void VectorStoreAligned(const VectorRegister4Double& Reg, double* Dest)
	{
		FMemory::MemCopy(Dest, &Reg, 4 * sizeof(double));
	}

/**
* Replicates one element into all four elements and returns the new vector.
*
* @param Vec			Source vector
* @param ElementIndex	Index (0-3) of the element to replicate
* @return				VectorRegister( Vec[ElementIndex], Vec[ElementIndex], Vec[ElementIndex], Vec[ElementIndex] )
*/
#define VectorReplicate(Vec, ElementIndex)			MakeVectorRegister((Vec).V[ElementIndex], (Vec).V[ElementIndex], (Vec).V[ElementIndex], (Vec).V[ElementIndex])

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
#define VectorSwizzle(Vec, X, Y, Z, W)				MakeVectorRegister((Vec).V[X], (Vec).V[Y], (Vec).V[Z], (Vec).V[W])

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
#define VectorShuffle(Vec1, Vec2, X, Y, Z, W)		MakeVectorRegister((Vec1).V[X], (Vec1).V[Y], (Vec2).V[Z], (Vec2).V[W])



	FORCEINLINE VectorRegister4Float VectorAdd(const VectorRegister4Float& VecReg1, const VectorRegister4Float& VecReg2)
	{
		VectorRegister4Float ResultVec;
		ResultVec.V[0] = VecReg1.V[0] + VecReg2.V[0];
		ResultVec.V[1] = VecReg1.V[1] + VecReg2.V[1];
		ResultVec.V[2] = VecReg1.V[2] + VecReg2.V[2];
		ResultVec.V[3] = VecReg1.V[3] + VecReg2.V[3];

		return ResultVec;
	}

	FORCEINLINE VectorRegister4Double VectorAdd(const VectorRegister4Double& VecReg1, const VectorRegister4Double& VecReg2)
	{
		VectorRegister4Double ResultVec;
		ResultVec.V[0] = VecReg1.V[0] + VecReg2.V[0];
		ResultVec.V[1] = VecReg1.V[1] + VecReg2.V[1];
		ResultVec.V[2] = VecReg1.V[2] + VecReg2.V[2];
		ResultVec.V[3] = VecReg1.V[3] + VecReg2.V[3];

		return ResultVec;
	}

	FORCEINLINE VectorRegister4Float VectorScalarAdd(const VectorRegister4Float& VecReg1, float Val)
	{
		VectorRegister4Float ResultVec;
		ResultVec.V[0] = VecReg1.V[0] + Val;
		ResultVec.V[1] = VecReg1.V[1] + Val;
		ResultVec.V[2] = VecReg1.V[2] + Val;
		ResultVec.V[3] = VecReg1.V[3] + Val;

		return ResultVec;
	}

	FORCEINLINE VectorRegister4Double VectorScalarAdd(const VectorRegister4Double& VecReg1, float Val)
	{
		VectorRegister4Double ResultVec;
		ResultVec.V[0] = VecReg1.V[0] + Val;
		ResultVec.V[1] = VecReg1.V[1] + Val;
		ResultVec.V[2] = VecReg1.V[2] + Val;
		ResultVec.V[3] = VecReg1.V[3] + Val;

		return ResultVec;
	}

	FORCEINLINE VectorRegister4Float VectorSubtract(const VectorRegister4Float& VecReg1, const VectorRegister4Float& VecReg2)
	{
		VectorRegister4Float ResultVec;
		ResultVec.V[0] = VecReg1.V[0] - VecReg2.V[0];
		ResultVec.V[1] = VecReg1.V[1] - VecReg2.V[1];
		ResultVec.V[2] = VecReg1.V[2] - VecReg2.V[2];
		ResultVec.V[3] = VecReg1.V[3] - VecReg2.V[3];

		return ResultVec;
	}

	FORCEINLINE VectorRegister4Double VectorSubtract(const VectorRegister4Double& VecReg1, const VectorRegister4Double& VecReg2)
	{
		VectorRegister4Double ResultVec;
		ResultVec.V[0] = VecReg1.V[0] - VecReg2.V[0];
		ResultVec.V[1] = VecReg1.V[1] - VecReg2.V[1];
		ResultVec.V[2] = VecReg1.V[2] - VecReg2.V[2];
		ResultVec.V[3] = VecReg1.V[3] - VecReg2.V[3];

		return ResultVec;
	}

	FORCEINLINE VectorRegister4Float VectorScalarSubtract(const VectorRegister4Float& VecReg1, float Val)
	{
		VectorRegister4Float ResultVec;
		ResultVec.V[0] = VecReg1.V[0] - Val;
		ResultVec.V[1] = VecReg1.V[1] - Val;
		ResultVec.V[2] = VecReg1.V[2] - Val;
		ResultVec.V[3] = VecReg1.V[3] - Val;

		return ResultVec;
	}

	FORCEINLINE VectorRegister4Double VectorScalarSubtract(const VectorRegister4Double& VecReg1, float Val)
	{
		VectorRegister4Double ResultVec;
		ResultVec.V[0] = VecReg1.V[0] - Val;
		ResultVec.V[1] = VecReg1.V[1] - Val;
		ResultVec.V[2] = VecReg1.V[2] - Val;
		ResultVec.V[3] = VecReg1.V[3] - Val;

		return ResultVec;
	}

	FORCEINLINE VectorRegister4Float VectorMultiply(const VectorRegister4Float& VecReg1, const VectorRegister4Float& VecReg2)
	{
		VectorRegister4Float ResultVec;
		ResultVec.V[0] = VecReg1.V[0] * VecReg2.V[0];
		ResultVec.V[1] = VecReg1.V[1] * VecReg2.V[1];
		ResultVec.V[2] = VecReg1.V[2] * VecReg2.V[2];
		ResultVec.V[3] = VecReg1.V[3] * VecReg2.V[3];

		return ResultVec;
	}

	FORCEINLINE VectorRegister4Double VectorMultiply(const VectorRegister4Double& VecReg1, const VectorRegister4Double& VecReg2)
	{
		VectorRegister4Double ResultVec;
		ResultVec.V[0] = VecReg1.V[0] * VecReg2.V[0];
		ResultVec.V[1] = VecReg1.V[1] * VecReg2.V[1];
		ResultVec.V[2] = VecReg1.V[2] * VecReg2.V[2];
		ResultVec.V[3] = VecReg1.V[3] * VecReg2.V[3];

		return ResultVec;
	}

	FORCEINLINE VectorRegister4Float VectorScalarMultiply(const VectorRegister4Float& VecReg1, float Val)
	{
		VectorRegister4Float ResultVec;
		ResultVec.V[0] = VecReg1.V[0] * Val;
		ResultVec.V[1] = VecReg1.V[1] * Val;
		ResultVec.V[2] = VecReg1.V[2] * Val;
		ResultVec.V[3] = VecReg1.V[3] * Val;

		return ResultVec;
	}

	FORCEINLINE VectorRegister4Double VectorScalarMultiply(const VectorRegister4Double& VecReg1, float Val)
	{
		VectorRegister4Double ResultVec;
		ResultVec.V[0] = VecReg1.V[0] * Val;
		ResultVec.V[1] = VecReg1.V[1] * Val;
		ResultVec.V[2] = VecReg1.V[2] * Val;
		ResultVec.V[3] = VecReg1.V[3] * Val;

		return ResultVec;
	}

	FORCEINLINE VectorRegister4Float VectorDivide(const VectorRegister4Float& VecReg1, const VectorRegister4Float& VecReg2)
	{
		VectorRegister4Float ResultVec;
		ResultVec.V[0] = VecReg1.V[0] / VecReg2.V[0];
		ResultVec.V[1] = VecReg1.V[1] / VecReg2.V[1];
		ResultVec.V[2] = VecReg1.V[2] / VecReg2.V[2];
		ResultVec.V[3] = VecReg1.V[3] / VecReg2.V[3];

		return ResultVec;
	}

	FORCEINLINE VectorRegister4Double VectorDivide(const VectorRegister4Double& VecReg1, const VectorRegister4Double& VecReg2)
	{
		VectorRegister4Double ResultVec;
		ResultVec.V[0] = VecReg1.V[0] / VecReg2.V[0];
		ResultVec.V[1] = VecReg1.V[1] / VecReg2.V[1];
		ResultVec.V[2] = VecReg1.V[2] / VecReg2.V[2];
		ResultVec.V[3] = VecReg1.V[3] / VecReg2.V[3];

		return ResultVec;
	}

	FORCEINLINE VectorRegister4Float VectorScalarDivide(const VectorRegister4Float& VecReg1, float Val)
	{
		VectorRegister4Float ResultVec;
		ResultVec.V[0] = VecReg1.V[0] / Val;
		ResultVec.V[1] = VecReg1.V[1] / Val;
		ResultVec.V[2] = VecReg1.V[2] / Val;
		ResultVec.V[3] = VecReg1.V[3] / Val;

		return ResultVec;
	}

	FORCEINLINE VectorRegister4Double VectorScalarDivide(const VectorRegister4Double& VecReg1, float Val)
	{
		VectorRegister4Double ResultVec;
		ResultVec.V[0] = VecReg1.V[0] / Val;
		ResultVec.V[1] = VecReg1.V[1] / Val;
		ResultVec.V[2] = VecReg1.V[2] / Val;
		ResultVec.V[3] = VecReg1.V[3] / Val;

		return ResultVec;
	}

	FORCEINLINE VectorRegister4Float VectorMatrixMultiply(const VectorRegister4Float& VecReg, const FMatrix44f* Mat)
	{
		typedef float Float4x4[4][4];
		const Float4x4& M = *((const Float4x4*)Mat);

		VectorRegister4Float ResultVec;
		ResultVec.V[0] = VecReg.V[0] * M[0][0] + VecReg.V[1] * M[1][0] + VecReg.V[2] * M[2][0] + VecReg.V[3] * M[3][0];
		ResultVec.V[1] = VecReg.V[0] * M[0][1] + VecReg.V[1] * M[1][1] + VecReg.V[2] * M[2][1] + VecReg.V[3] * M[3][1];
		ResultVec.V[2] = VecReg.V[0] * M[0][2] + VecReg.V[1] * M[1][2] + VecReg.V[2] * M[2][2] + VecReg.V[3] * M[3][2];
		ResultVec.V[3] = VecReg.V[0] * M[0][3] + VecReg.V[1] * M[1][3] + VecReg.V[2] * M[2][3] + VecReg.V[3] * M[3][3];

		return ResultVec;
	}

	FORCEINLINE VectorRegister4Double VectorMatrixMultiply(const VectorRegister4Double& VecReg, const FMatrix44d* Mat)
	{
		typedef double Double4x4[4][4];
		const Double4x4& M = *((const Double4x4*)Mat);

		VectorRegister4Double ResultVec;
		ResultVec.V[0] = VecReg.V[0] * M[0][0] + VecReg.V[1] * M[1][0] + VecReg.V[2] * M[2][0] + VecReg.V[3] * M[3][0];
		ResultVec.V[1] = VecReg.V[0] * M[0][1] + VecReg.V[1] * M[1][1] + VecReg.V[2] * M[2][1] + VecReg.V[3] * M[3][1];
		ResultVec.V[2] = VecReg.V[0] * M[0][2] + VecReg.V[1] * M[1][2] + VecReg.V[2] * M[2][2] + VecReg.V[3] * M[3][2];
		ResultVec.V[3] = VecReg.V[0] * M[0][3] + VecReg.V[1] * M[1][3] + VecReg.V[2] * M[2][3] + VecReg.V[3] * M[3][3];

		return ResultVec;
	}

	FORCEINLINE void MatrixMultiply(FMatrix44f* Result, const FMatrix44f* Mat1, const FMatrix44f* Mat2)
	{
		typedef float Float4x4[4][4];
		const Float4x4& M1 = *((const Float4x4*)Mat1);
		const Float4x4& M2 = *((const Float4x4*)Mat2);
		Float4x4 ResultMat;

		ResultMat[0][0] = M1[0][0] * M2[0][0] + M1[0][1] * M2[1][0] + M1[0][2] * M2[2][0] + M1[0][3] * M2[3][0];
		ResultMat[0][1] = M1[0][0] * M2[0][1] + M1[0][1] * M2[1][1] + M1[0][2] * M2[2][1] + M1[0][3] * M2[3][1];
		ResultMat[0][2] = M1[0][0] * M2[0][2] + M1[0][1] * M2[1][2] + M1[0][2] * M2[2][2] + M1[0][3] * M2[3][2];
		ResultMat[0][3] = M1[0][0] * M2[0][3] + M1[0][1] * M2[1][3] + M1[0][2] * M2[2][3] + M1[0][3] * M2[3][3];

		ResultMat[1][0] = M1[1][0] * M2[0][0] + M1[1][1] * M2[1][0] + M1[1][2] * M2[2][0] + M1[1][3] * M2[3][0];
		ResultMat[1][1] = M1[1][0] * M2[0][1] + M1[1][1] * M2[1][1] + M1[1][2] * M2[2][1] + M1[1][3] * M2[3][1];
		ResultMat[1][2] = M1[1][0] * M2[0][2] + M1[1][1] * M2[1][2] + M1[1][2] * M2[2][2] + M1[1][3] * M2[3][2];
		ResultMat[1][3] = M1[1][0] * M2[0][3] + M1[1][1] * M2[1][3] + M1[1][2] * M2[2][3] + M1[1][3] * M2[3][3];

		ResultMat[2][0] = M1[2][0] * M2[0][0] + M1[2][1] * M2[1][0] + M1[2][2] * M2[2][0] + M1[2][3] * M2[3][0];
		ResultMat[2][1] = M1[2][0] * M2[0][1] + M1[2][1] * M2[1][1] + M1[2][2] * M2[2][1] + M1[2][3] * M2[3][1];
		ResultMat[2][2] = M1[2][0] * M2[0][2] + M1[2][1] * M2[1][2] + M1[2][2] * M2[2][2] + M1[2][3] * M2[3][2];
		ResultMat[2][3] = M1[2][0] * M2[0][3] + M1[2][1] * M2[1][3] + M1[2][2] * M2[2][3] + M1[2][3] * M2[3][3];

		ResultMat[3][0] = M1[3][0] * M2[0][0] + M1[3][1] * M2[1][0] + M1[3][2] * M2[2][0] + M1[3][3] * M2[3][0];
		ResultMat[3][1] = M1[3][0] * M2[0][1] + M1[3][1] * M2[1][1] + M1[3][2] * M2[2][1] + M1[3][3] * M2[3][1];
		ResultMat[3][2] = M1[3][0] * M2[0][2] + M1[3][1] * M2[1][2] + M1[3][2] * M2[2][2] + M1[3][3] * M2[3][2];
		ResultMat[3][3] = M1[3][0] * M2[0][3] + M1[3][1] * M2[1][3] + M1[3][2] * M2[2][3] + M1[3][3] * M2[3][3];

		FMemory::MemCopy(Result, &ResultMat, 16 * sizeof(float));
	}

	FORCEINLINE void MatrixMultiply(FMatrix44d* Result, const FMatrix44d* Mat1, const FMatrix44d* Mat2)
	{
		typedef double Double4x4[4][4];
		const Double4x4& M1 = *((const Double4x4*)Mat1);
		const Double4x4& M2 = *((const Double4x4*)Mat2);
		Double4x4 ResultMat;

		ResultMat[0][0] = M1[0][0] * M2[0][0] + M1[0][1] * M2[1][0] + M1[0][2] * M2[2][0] + M1[0][3] * M2[3][0];
		ResultMat[0][1] = M1[0][0] * M2[0][1] + M1[0][1] * M2[1][1] + M1[0][2] * M2[2][1] + M1[0][3] * M2[3][1];
		ResultMat[0][2] = M1[0][0] * M2[0][2] + M1[0][1] * M2[1][2] + M1[0][2] * M2[2][2] + M1[0][3] * M2[3][2];
		ResultMat[0][3] = M1[0][0] * M2[0][3] + M1[0][1] * M2[1][3] + M1[0][2] * M2[2][3] + M1[0][3] * M2[3][3];

		ResultMat[1][0] = M1[1][0] * M2[0][0] + M1[1][1] * M2[1][0] + M1[1][2] * M2[2][0] + M1[1][3] * M2[3][0];
		ResultMat[1][1] = M1[1][0] * M2[0][1] + M1[1][1] * M2[1][1] + M1[1][2] * M2[2][1] + M1[1][3] * M2[3][1];
		ResultMat[1][2] = M1[1][0] * M2[0][2] + M1[1][1] * M2[1][2] + M1[1][2] * M2[2][2] + M1[1][3] * M2[3][2];
		ResultMat[1][3] = M1[1][0] * M2[0][3] + M1[1][1] * M2[1][3] + M1[1][2] * M2[2][3] + M1[1][3] * M2[3][3];

		ResultMat[2][0] = M1[2][0] * M2[0][0] + M1[2][1] * M2[1][0] + M1[2][2] * M2[2][0] + M1[2][3] * M2[3][0];
		ResultMat[2][1] = M1[2][0] * M2[0][1] + M1[2][1] * M2[1][1] + M1[2][2] * M2[2][1] + M1[2][3] * M2[3][1];
		ResultMat[2][2] = M1[2][0] * M2[0][2] + M1[2][1] * M2[1][2] + M1[2][2] * M2[2][2] + M1[2][3] * M2[3][2];
		ResultMat[2][3] = M1[2][0] * M2[0][3] + M1[2][1] * M2[1][3] + M1[2][2] * M2[2][3] + M1[2][3] * M2[3][3];

		ResultMat[3][0] = M1[3][0] * M2[0][0] + M1[3][1] * M2[1][0] + M1[3][2] * M2[2][0] + M1[3][3] * M2[3][0];
		ResultMat[3][1] = M1[3][0] * M2[0][1] + M1[3][1] * M2[1][1] + M1[3][2] * M2[2][1] + M1[3][3] * M2[3][1];
		ResultMat[3][2] = M1[3][0] * M2[0][2] + M1[3][1] * M2[1][2] + M1[3][2] * M2[2][2] + M1[3][3] * M2[3][2];
		ResultMat[3][3] = M1[3][0] * M2[0][3] + M1[3][1] * M2[1][3] + M1[3][2] * M2[2][3] + M1[3][3] * M2[3][3];

		FMemory::MemCopy(Result, &ResultMat, 16 * sizeof(double));
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