#pragma once

#include "Memory/IncludesMemory.h"

namespace AAEngine {
namespace Algorithms {

	/*
	* Swaps the Values in A and B by reference
	* 
	* @param A - reference to the Value to be swapped
	* @param B - reference to the other Value to be swapped
	*/
	template<typename T>
	static void Swap(T& A, T& B)
	{
		T Temp = A;
		A = B;
		B = Temp;
	}

	/*
	* Merge Sort Helper Recursive function that uses an Auxilary Array to store merged sub arrays
	* Slow (O(2 * n * log(n)))
	* 
	* @param InArray - Pointer to the Start of the Array that needs to be sorted.
	* @param AuxArray - The Auxillary Array used to sort merged sub arrays
	* @param Left - The Left Index of the Sub Array to be MergeSorted.
	* @param Right - The Right Index of the Sub Array to be MergeSorted.
	*/
	template<typename T>
	static void MergeSortHelperTempArray(T* InArray, T* AuxArray, size_t Left, size_t Right)
	{
		if (Right - Left <= 1)
		{
			return;
		}
		if (Right - Left == 2)
		{
			if (InArray[Left] > InArray[Right - 1])
			{
				Swap(InArray[Right - 1], InArray[Left]);
			}
			return;
		}

		size_t Center = Left + (Right - Left) >> 1;

		MergeSortHelperTempArray(InArray, AuxArray, Left, Center + 1);
		MergeSortHelperTempArray(InArray, AuxArray, Center + 1, Right);

		size_t LeftI = Left;
		size_t RightI = Center + 1;

		size_t Index = Left;
		while (LeftI <= Center && RightI < Right)
		{
			if (InArray[LeftI] > InArray[RightI])
			{
				AuxArray[Index] = InArray[RightI];
				RightI++;
			}
			else
			{
				AuxArray[Index] = InArray[LeftI];
				LeftI++;
			}
			Index++;
		}

		while (LeftI <= Center)
		{
			AuxArray[Index] = InArray[LeftI];
			LeftI++;
			Index++;
		}

		while (RightI < Right)
		{
			AuxArray[Index] = InArray[RightI];
			RightI++;
			Index++;
		}

		FMemory::MemMove(InArray + Left, AuxArray + Left, (Right - Left) * sizeof(T));
	}

	/*
	* Merge Sort Helper Recursive function that sorts the Array in-place
	* n^2 because every element we try to arrange in the sorted array, we need to shift the rest of the left subarray with O(n)
	* Incredibly Slow O(n^2 * log(n))
	*
	* @param InArray - Pointer to the Start of the Array that needs to be sorted.
	* @param Left - The Left Index of the Sub Array to be MergeSorted.
	* @param Right - The Right Index of the Sub Array to be MergeSorted.
	*/
	template<typename T>
	static void MergeSortHelperInPlace(T* InArray, size_t Left, size_t Right)
	{
		if (Right - Left <= 1)
		{
			return;
		}
		if (Right - Left == 2)
		{
			if (InArray[Left] > InArray[Right - 1])
			{
				Swap(InArray[Right - 1], InArray[Left]);
			}
			return;
		}

		size_t Center = Left + (Right - Left) >> 1;

		MergeSortHelperInPlace(InArray, Left, Center + 1);
		MergeSortHelperInPlace(InArray, Center + 1, Right);

		size_t LeftI = Left;
		size_t RightI = Center + 1;

		while (LeftI <= Center && RightI < Right)
		{
			if (InArray[LeftI] > InArray[RightI])
			{
				T Temp = InArray[RightI];
				for (size_t i = RightI; i > LeftI; i--)
				{
					InArray[i] = InArray[i - 1];
				}
				InArray[LeftI] = Temp;
				RightI++;
				LeftI++;
				Center++;
			}
			else
			{
				LeftI++;
			}
		}
	}

	/*
	* Merge Sort Recursive Function that calls the MergeSortHelper functions to sort the Array.
	* 
	* @param InArray - Pointer to the Start of the Array that needs to be sorted.
	* @param Size - Size of the Array
	*/
	template<typename T>
	static void MergeSortRecursive(T* InArray, size_t Size)
	{
		T* TempArray = new T[Size];
		MergeSortHelperTempArray(InArray, TempArray, 0, Size);
		delete[] TempArray;
	}

	/*
	* Merge Sort Helper Recursive function that finds a Median Pivot and then sorts the Sub-Arrays
	* O (n * log(n)) Average Case with a Median Pivot Point
	* Faster than Merge Sort.
	*
	* @param InArray - Pointer to the Start of the Array that needs to be sorted.
	* @param Left - The Left Index of the Sub Array to be QuickSorted.
	* @param Right - The Right Index of the Sub Array to be QuickSorted.
	*/
	template<typename T>
	static void QuickSortHelper(T* InArray, size_t Left, size_t Right)
	{
		if (Right - Left <= 1)
		{
			return;
		}
		else if (Right - Left == 2)
		{
			if (InArray[Right - 1] < InArray[Left])
			{
				Swap(InArray[Right - 1], InArray[Left]);
			}
			return;
		}
		// O(1) - 2-3 Comparisions
		// Right - 1 = Last Element
		size_t PivotIndex = Left + (Right - Left) / 2;// FindMedianPivot(InArray, Left, Right - 1);
		
		T PivotValue = InArray[PivotIndex];

		size_t LeftStart = Left;
		size_t RightStart = Right - 1;

		// O(n)
		while (RightStart >= LeftStart && RightStart >= Left && LeftStart < Right)
		{
			while (InArray[LeftStart] < PivotValue)
			{
				LeftStart++;
			}
			while (InArray[RightStart] > PivotValue)
			{
				RightStart--;
			}
			if (RightStart >= LeftStart)
			{
				Swap(InArray[LeftStart], InArray[RightStart]);
				LeftStart++;
				RightStart--;
			}
		}

		QuickSortHelper(InArray, Left, LeftStart);
		QuickSortHelper(InArray, LeftStart, Right);
	}

	/*
	* Finds a Median Pivot - Median of Left Value, Right Value, Center Value from the InArray
	* 
	* @param InArray - Pointer to the Start of the Array that needs to be sorted.
	* @param Left - The Left Index of the Sub Array to be QuickSorted.
	* @param Right - The Right Index of the Sub Array to be QuickSorted.
	*/
	template<typename T>
	static size_t FindMedianPivot(T* InArray, size_t Left, size_t Right)
	{
		size_t Center = Left + ((Right - Left) >> 1);
		if (InArray[Right] > InArray[Left])
		{
			if (InArray[Center] > InArray[Right])
			{
				return Right;
			}
			else if (InArray[Center] < InArray[Left])
			{
				return Left;
			}
			else
			{
				return Center;
			}
		}
		else
		{
			if (InArray[Center] < InArray[Right])
			{
				return Right;
			}
			else if (InArray[Center] > InArray[Left])
			{
				return Left;
			}
			else
			{
				return Center;
			}
		}
	}
	
	/*
	* Quick Sort Recursive Function that calls the QuickSortHelper functions to sort the Array.
	*
	* @param InArray - Pointer to the Start of the Array that needs to be sorted.
	* @param Size - Size of the Array
	*/
	template<typename T>
	static void QuickSort(T* InArray, size_t Size)
	{
		QuickSortHelper(InArray, 0, Size);
	}
}
}