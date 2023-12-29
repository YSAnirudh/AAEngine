#include "AA_PreCompiledHeaders.h"
#include "TesterFile.h"
#include "Profiling/Timer.h"
#include "Containers/StaticArray.h"
#include "Containers/Array.h"
#include "Math/IncludesMath.h"

#define GLM_FORCE_ALIGNED
#define GLM_FORCE_SSE2
// Temporary GLM
#include <glm/matrix.hpp>

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

	void PrintGLMMat(const glm::mat4& Mat)
	{
		for (int i = 0; i < Mat.length(); i++)
		{
			std::cout << "[" << Mat[i].x << ", " << Mat[i].y << ", " << Mat[i].z << ", " << Mat[i].w << "]\n";
		}
	}

	void PrintGLMMat(const glm::vec4& Vec)
	{
		std::cout << "[" << Vec.x << ", " << Vec.y << ", " << Vec.z << ", " << Vec.w << "]\n";
	}

	void CTester::RunTester()
	{
		//DynamicArrayTests();
		//MatrixTests();
	}

	void CTester::MatrixTests()
	{
		FMatrix44f Mat({ 1,2,3,4 }, { 1,2,0,4 }, { 1,0,3,4 }, { 0,2,3,4 });
		//AA_CORE_LOG(Info, "Mat: \n%s\n", (Mat.GetInverseFast()).ToString().c_str());
		glm::mat4 GMat({ 1,2,3,4 }, { 1,2,0,4 }, { 1,0,3,4 }, { 0,2,3,4 });
		//PrintGLMMat(glm::inverse(GMat));
		glm::mat4 GNewMat({ 1,0,0,2 }, { 1,2,0,4 }, { 1,0,3,4 }, { 0,2,3,4 });
		
		FMatrix44f NewMat({ 1,0,0,2 }, { 1,2,0,4 }, { 1,0,3,4 }, { 0,2,3,4 });
		FMatrix44f Result;
		FVector4f NewVec(1.0f);
		FVector4f ResVec = NewVec * Mat * NewMat;
		glm::vec4 GNewVec(1.0f);
		glm::vec4 GResVec = GNewVec * GMat * GNewMat;

		TArray<FMatrix44f> MyArray;
		TArray<glm::mat4> GLMArray;

		constexpr int TestSize = 10000000;
		constexpr ETimeResolution TestTimeResolution = MilliSeconds;
		/*{
			TTimer<TestTimeResolution> Timer("Mat Mult");
			for (int i = 0; i < TestSize; i++)
			{
				MyArray.PushBack(Mat.GetInverseFast());
			}
		}*/
		NewMat *= Mat;
		//AA_CORE_LOG(Info, "Mat: \n%s\n", (ResVec).ToString().c_str());
		//std::cout << FMatrix44f({ 1,2,3,4 }, { 1,2,0,4 }, { 1,0,3,4 }, { 0,2,3,4 }).Determinant3x3() << std::endl;
		//std::cout << glm::determinant(glm::mat4({ 1,2,3,4 }, { 1,2,0,4 }, { 1,0,3,4 }, { 0,2,3,4 })) << std::endl;
		//glm::mat4 GResult;
		/*{
			TTimer<TestTimeResolution> Timer("GLM Mat Mult");
			for (int i = 0; i < TestSize; i++)
			{
				GLMArray.PushBack(glm::inverse(GMat));
			}
		}*/
		/*for (int i = 0; i < 16; i++)
		{
			std::cout << Mat.MLin[i] << " ";
		}
		std::cout << "\n";
		PrintGLMMat(GResVec);*/
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
				size_t temp = VectorOfUnique.size();
				VectorOfUnique[i] = temp;
			}
		}

		{
			TStaticArray<int, TestSize> VectorOfUnique;
			TTimer<TestTimeResolution> Timer("AA Array");
			for (auto i = VectorOfUnique.begin(); i != VectorOfUnique.end(); i++)
			{
				*i = 100;
				size_t temp = VectorOfUnique.Num();
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
			FVector4f V = FVector4f(1.0f) + FVector4f(4.0f);
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