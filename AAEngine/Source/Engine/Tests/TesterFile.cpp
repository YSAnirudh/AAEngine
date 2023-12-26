#include "AA_PreCompiledHeaders.h"
#include "TesterFile.h"
#include "Profiling/Timer.h"
#include "Containers/StaticArray.h"
#include "Containers/Array.h"
#include "Math/MathForwards.h"

namespace AAEngine {

	struct Vector
	{
		float x;
		std::string Hello;
		float y, z;
		Vector() = default;
		Vector(float x, float y, float z) : x(x), y(y), z(z), Hello("Hello")
		{
		}

		Vector(const std::string& NewString) : x(0.0f), y(0.0f), z(0.0f), Hello(NewString)
		{
		}

		Vector(const Vector& NewVec)
			: x(NewVec.x), y(NewVec.y), z(NewVec.z), Hello(NewVec.Hello)
		{
			//std::cout << "Copy\n";
		}

		Vector(Vector&& NewVec) noexcept
			: x(NewVec.x), y(NewVec.y), z(NewVec.z), Hello(NewVec.Hello)
		{
			//std::cout << "Move\n";
		}

		~Vector()
		{
			//std::cout << "Destroy\n";
		}

		Vector& operator=(const Vector& NewVec)
		{
			//std::cout << "Copy\n";
			x = NewVec.x;
			y = NewVec.y;
			z = NewVec.z;
			Hello = NewVec.Hello;
			return *this;
		}

		Vector& operator=(Vector&& NewVec) noexcept
		{
			//std::cout << "Move\n";
			x = NewVec.x;
			y = NewVec.y;
			z = NewVec.z;
			Hello = NewVec.Hello;
			return *this;
		}

	};
	std::ostream& operator<<(std::ostream& Out, const Vector& OutVec)
	{
		Out << OutVec.x << " " << OutVec.y << " " << OutVec.z << " " << OutVec.Hello;
		return Out;
	}

	template<typename T>
	void PrintArray(const TArray<T>& Array)
	{
		for (int i = 0; i < Array.Num(); i++)
		{
			std::cout << Array[i] << "\n";
		}
	}

	void CTester::RunTester()
	{
		//DynamicArrayTests();
		MatrixTests();
	}

	void CTester::MatrixTests()
	{
		FMatrix44f Mat(1.0f);
		FMatrix44f NewMat(0.0f);

		AA_CORE_LOG(Info, "Mat: \n%s", Mat.ToString().c_str());
		AA_CORE_LOG(Info, "New Mat: \n%s", NewMat.ToString().c_str());

		FMatrix44f ExtraMat(Mat);

		AA_CORE_LOG(Info, "Mat: \n%s", ExtraMat.ToString().c_str());
	}

	void CTester::StaticArrayTests()
	{
		constexpr int TestSize = 1;
		constexpr ETimeResolution TestTimeResolution = NanoSeconds;
		/*{
			std::array<int, TestSize> VectorOfUnique;
			TTimer<TestTimeResolution> Timer("STD Array");
			for (int i = 0; i < TestSize; i++)
			{
				VectorOfUnique[i] = 100;
				int temp = VectorOfUnique.size();
				VectorOfUnique[i] = temp;
			}
		}

		{
			TStaticArray<int, TestSize> VectorOfUnique;
			TTimer<TestTimeResolution> Timer("AA Array");
			for (auto i = VectorOfUnique.Begin(); i != VectorOfUnique.End(); i++)
			{
				*i = 100;
				int temp = VectorOfUnique.Num();
				*i = temp;

			}
		}*/

		/*{
			std::array<TUniquePtr<int>, TestSize> VectorOfUnique;
			TTimer<TestTimeResolution> Timer("STD Make Unique");
			for (int i = 0; i < TestSize; i++)
			{
				VectorOfUnique[i] = MakeUnique<int>();
			}
		}

		{
			TStaticArray<TUniquePtr<int>, TestSize> VectorOfUnique;
			TTimer<TestTimeResolution> Timer("STD New");
			for (int i = 0; i < TestSize; i++)
			{
				VectorOfUnique[i] = MakeUnique<int>();
			}
		}*/
	}

	void CTester::DynamicArrayTests()
	{
		/* ~2-5 Times Faster */
		constexpr int TestSize = 10000000;
		constexpr ETimeResolution TestTimeResolution = MicroSeconds;

		{
			std::vector<Math::TVector3<float>> VectorOfUnique;
			/*for (int i = 0; i < TestSize; i++)
			{
				VectorOfUnique.emplace(VectorOfUnique.end());
			}
			TTimer<TestTimeResolution> Timer("STD Array");
			VectorOfUnique.shrink_to_fit();*/
			/*while (VectorOfUnique.size() != 0)
			{
				VectorOfUnique.pop_back();
			}*/
		}

		//{
		//	TArray<Vector> VectorOfUnique;
		//	for (int i = 0; i < TestSize; i++)
		//	{
		//		VectorOfUnique.Emplace(VectorOfUnique.Num());
		//	}
		//	TTimer<TestTimeResolution> Timer("AA Array");
		//	VectorOfUnique.ShrinkToFit();
		//	/*while (!VectorOfUnique.IsEmpty())
		//	{
		//		VectorOfUnique.PopBack();
		//	}*/
		//}

		TArray<Vector> VectorOfUnique;
		VectorOfUnique.RemoveAt(0);
		VectorOfUnique.EmplaceBack("Hello");
		//VectorOfUnique.EmplaceBack(1.f, 1.f, 3.f);
		VectorOfUnique.Emplace(VectorOfUnique.end(), "Hello Sar cvaddu");
		VectorOfUnique.Emplace(VectorOfUnique.end(), "Hello Sar cvaddu");
		VectorOfUnique.Emplace(VectorOfUnique.end(), "Hello Sar cvaddu");
		VectorOfUnique.Emplace(VectorOfUnique.end(), "Hello Sar cvaddu");
		VectorOfUnique.Emplace(VectorOfUnique.begin(), "Hello Sar cvaddu");
		VectorOfUnique.Emplace(VectorOfUnique.end(), "Hello Sar cvaddu");
		VectorOfUnique.Emplace(VectorOfUnique.end(), "Hello Sar cvaddu");
		//VectorOfUnique.PushBack("Helloasdasd");

		//TArray<Vector> NewArray;


		std::cout << "Old Array\n";
		PrintArray(VectorOfUnique);

		//std::cout << "New Array\n";
		//PrintArray(NewArray);
		
	}

	void CTester::UniquePtrTests()
	{
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
		* 10000 size, similar results
		* 100000 size, similar results
		*/
		constexpr int TestSize = 1;
		constexpr ETimeResolution TestTimeResolution = MicroSeconds;
		{
			std::array<std::unique_ptr<int>, TestSize> VectorOfUnique;
			TTimer<TestTimeResolution> Timer("STD Make Unique");
			for (int i = 0; i < TestSize; i++)
			{
				VectorOfUnique[i] = std::make_unique<int>();
			}
		}

		{
			std::array<std::unique_ptr<int>, TestSize> VectorOfUnique;
			TTimer<TestTimeResolution> Timer("STD New");
			for (int i = 0; i < TestSize; i++)
			{
				VectorOfUnique[i] = std::unique_ptr<int>(new int);
			}
		}

		{
			std::array<TUniquePtr<int>, TestSize> VectorOfUnique;
			TTimer<TestTimeResolution> Timer("AA Make Unique");
			for (int i = 0; i < TestSize; i++)
			{
				VectorOfUnique[i] = MakeUnique<int>();
			}
		}

		{
			std::array<TUniquePtr<int>, TestSize> VectorOfUnique;
			TTimer<TestTimeResolution> Timer("AA New");
			for (int i = 0; i < TestSize; i++)
			{
				VectorOfUnique[i] = TUniquePtr<int>(new int);
			}
		}

		{
			std::array<TUniquePtr<int>, TestSize> VectorOfUnique;
			TTimer<TestTimeResolution> Timer("Raw New");
			for (int i = 0; i < TestSize; i++)
			{
				VectorOfUnique[i] = new int;
			}
		}
	}
}