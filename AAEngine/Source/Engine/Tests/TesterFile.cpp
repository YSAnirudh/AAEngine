#include "AA_PreCompiledHeaders.h"
#include "TesterFile.h"
#include "Profiling/Timer.h"

namespace AAEngine {
	void CTester::RunTester()
	{
		
	}

	void CTester::StaticArrayTests()
	{
	}

	void CTester::DynamicArrayTests()
	{
	}

	void CTester::UniquePtrTests()
	{
		// Much faster than std::unique_ptr

		/*
		* TEST RESULTS
		* 
		* 1) std::make_unique
		* Size = 1000
		* Speed (Avg) = 68 ns
		* Speed (Fastest) = 62 ns
		* 
		* 2) AA - MakeUnique
		* Size = 1000
		* Speed (Avg) = 47 ns
		* Speed (Fastest) = 45 ns
		* 
		* 3) AA - new TUniquePtr
		* Size = 1000
		* Speed (Avg) = 49 ns
		* Speed (Fastest) = 47 ns
		* 
		* 4) Raw new
		* Size = 1000
		* Speed (Avg) = 46 ns
		* Speed (Fastest) = 45 ns
		* 
		*/
		constexpr int TestSize = 0;
		constexpr ETimeResolution TestTimeResolution = MicroSeconds;
		{
			std::array<std::unique_ptr<int>, TestSize> VectorOfUnique;
			CTimer<TestTimeResolution> Timer("STD Make Unique");
			for (int i = 0; i < TestSize; i++)
			{
				VectorOfUnique[i] = std::make_unique<int>();
			}
		}

		{
			std::array<std::unique_ptr<int>, TestSize> VectorOfUnique;
			CTimer<TestTimeResolution> Timer("STD New");
			for (int i = 0; i < TestSize; i++)
			{
				VectorOfUnique[i] = std::unique_ptr<int>(new int);
			}
		}

		{
			std::array<TUniquePtr<int>, TestSize> VectorOfUnique;
			CTimer<TestTimeResolution> Timer("AA Make Unique");
			for (int i = 0; i < TestSize; i++)
			{
				VectorOfUnique[i] = MakeUnique<int>();
			}
		}

		{
			std::array<TUniquePtr<int>, TestSize> VectorOfUnique;
			CTimer<TestTimeResolution> Timer("AA New");
			for (int i = 0; i < TestSize; i++)
			{
				VectorOfUnique[i] = TUniquePtr<int>(new int);
			}
		}

		{
			std::array<TUniquePtr<int>, TestSize> VectorOfUnique;
			CTimer<TestTimeResolution> Timer("Raw New");
			for (int i = 0; i < TestSize; i++)
			{
				VectorOfUnique[i] = new int;
			}
		}
	}
}