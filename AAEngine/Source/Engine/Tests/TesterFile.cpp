#include "AA_PreCompiledHeaders.h"
#include "TesterFile.h"
#include "Profiling/Timer.h"
#include "Containers/StaticArray.h"
#include "Containers/Array.h"
#include "Math/IncludesMath.h"

#define GLM_FORCE_ALIGNED
//#define GLM_FORCE_AVX2
// Temporary GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
		AlgorithmTests();
	}

	void CTester::MatrixTests()
	{
		FMatrix44f Mat1({ 1,2,3,4 }, { 1,2,0,4 }, { 1,0,3,4 }, { 0,2,3,4 });
		glm::mat4 GMat({ 1,2,3,4 }, { 1,2,0,4 }, { 1,0,3,4 }, { 0,2,3,4 });
		FMatrix44f Mat2({ 1,2,3,4 }, { 1,2,0,4 }, { 1,0,3,4 }, { 0,2,3,4 });
		constexpr int TestSize = 10000000;
		constexpr ETimeResolution TestTimeResolution = MilliSeconds;
		{
			TTimer<TestTimeResolution> Timer("Mat Add");
			for (int i = 0; i < TestSize; i++)
			{
				GMat *= glm::mat4(float(rand()) / RAND_MAX);
				//Mat1 *= FMatrix44f(float(rand())/RAND_MAX);
			}
		}
		AA_CORE_LOG(Info, "Mat: \n%s\n", (Mat1 * Mat2).ToString().c_str());
		
	}

	void CTester::MatrixGLMTests()
	{
		FMatrix44f Mat({ 1,2,3,4 }, { 1,2,0,4 }, { 1,0,3,4 }, { 0,2,3,4 });
		//AA_CORE_LOG(Info, "Mat: \n%s\n", (Mat.GetInverseFast()).ToString().c_str());
		glm::mat4 GMat({ 1,2,3,4 }, { 1,2,0,4 }, { 1,0,3,4 }, { 0,2,3,4 });
		//PrintGLMMat(glm::inverse(GMat));
		glm::mat4 GNewMat({ 1,0,0,2 }, { 1,2,0,4 }, { 1,0,3,4 }, { 0,2,3,4 });
		
		glm::mat4 X = glm::mat4(1.0f);
		glm::mat4 Y = glm::mat4(1.0f);
		glm::mat4 Z = glm::mat4(1.0f);

		X = glm::rotate(X, 45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		Y = glm::rotate(Y, 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		Z = glm::rotate(Z, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));

		glm::mat4 FinalRot = X * Y * Z;
		FMatrix44f Rot = FMatrix44f::MakeFromRotationXYZ({ 45.f, 45.f, 45.f });
		FMatrix44f NewMat({ 1,0,0,2 }, { 1,2,0,4 }, { 1,0,3,4 }, { 0,2,3,4 });
		FMatrix44f Result;
		FVector4f NewVec(1.0f);
		FVector4f ResVec = NewVec * Mat * NewMat;
		glm::vec4 GNewVec(1.0f);
		glm::vec4 GResVec = GNewMat * GMat * GNewVec;
		glm::mat4 GProj = glm::perspective(1.5f, 1.0f, 0.01f, 100.f);
		FMatrix44f Proj = FMatrix44f::MakePerspective(1.5f, 1.0f, 0.01f, 100.f);
		TArray<FMatrix44f> MyArray;
		TArray<glm::mat4> GLMArray;
		AA_CORE_LOG(Info, "Mat: \n%s\n", (Proj).ToString().c_str());
		PrintGLMMat(GProj);

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

	void CTester::AlgorithmTests()
	{
		constexpr int TestSize = 10000000;
		constexpr int TestIter = 10;
		constexpr ETimeResolution TestTimeResolution = MilliSeconds;
		{
			long long Dur = 0;
			TTimer<TestTimeResolution> Timer("AA Sort", false);
			for (int i = 0; i < TestIter; i++)
			{
				TArray<float> ToSortAA(TestSize);
				for (int i = 0; i < TestSize; i++)
				{
					ToSortAA.EmplaceBack(/*float(TestSize - i)); */ float(rand()) / RAND_MAX);
				}
				Timer.Reset();
				ToSortAA.Sort();
				Dur += Timer.Reset();
				//AA_CORE_LOG(Info, "SortedArray: %s", (ToSortAA).ToString().c_str());
			}
			AA_CORE_LOG(Info, "Average Time AA: %f", (float)Dur / TestIter);
		}

		{
			long long Dur = 0;
			TTimer<TestTimeResolution> Timer("STD Sort", false);
			for (int i = 0; i < TestIter; i++)
			{
				std::vector<float> ToSort;
				for (int i = 0; i < TestSize; i++)
				{
					ToSort.emplace_back(float(rand()) / RAND_MAX);
				}
				Timer.Reset();
				std::sort(ToSort.begin(), ToSort.end());
				Dur += Timer.Reset();
			}
			AA_CORE_LOG(Info, "Average Time STD: %f", (float)Dur / TestIter);
		}
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
		/* Faster */
		constexpr int TestSize = 100000;
		constexpr ETimeResolution TestTimeResolution = MilliSeconds;

		{
			long long Dur = 0;
			TTimer<TestTimeResolution> Timer("STD Array", false);
			for (int testNum = 0; testNum < 10; testNum++)
			{
				std::vector<float> VectorOfUnique;
				Dur += Timer.Reset();
				for (int i = 0; i < TestSize; i++)
				{
					VectorOfUnique.emplace(VectorOfUnique.begin(), float(rand())/RAND_MAX);
				}
			}
			AA_CORE_LOG(Info, "Average Time STD: %f", (float)Dur * 0.01);
		}

		{
			long long Dur = 0;
			TTimer<TestTimeResolution> Timer("AA Array", false);
			for (int testNum = 0; testNum < 10; testNum++)
			{
				TArray<float> VectorOfUnique;
				Dur += Timer.Reset();
				for (int i = 0; i < TestSize; i++)
				{
					VectorOfUnique.Emplace(VectorOfUnique.begin(), float(rand()) / RAND_MAX);
				}
			}
			AA_CORE_LOG(Info, "Average Time AA: %f", (float)Dur * 0.01);
			//VectorOfUnique.ShrinkToFit();
			/*while (!VectorOfUnique.IsEmpty())
			{
				VectorOfUnique.PopBack();
			}*/
		}

		//TArray<Vector> VectorOfUnique;
		//VectorOfUnique.RemoveAt(0);
		//VectorOfUnique.EmplaceBack("Hello");
		////VectorOfUnique.EmplaceBack(1.f, 1.f, 3.f);
		//VectorOfUnique.Emplace(VectorOfUnique.end(), "Hello Sar cvaddu");
		//VectorOfUnique.Emplace(VectorOfUnique.end(), "Hello Sar cvaddu");
		//VectorOfUnique.Emplace(VectorOfUnique.end(), "Hello Sar cvaddu");
		//VectorOfUnique.Emplace(VectorOfUnique.end(), "Hello Sar cvaddu");
		//VectorOfUnique.Emplace(VectorOfUnique.begin(), "Hello Sar cvaddu");
		//VectorOfUnique.Emplace(VectorOfUnique.end(), "Hello Sar cvaddu");
		//VectorOfUnique.Emplace(VectorOfUnique.end(), "Hello Sar cvaddu");
		////VectorOfUnique.PushBack("Helloasdasd");

		////TArray<Vector> NewArray;


		//std::cout << "Old Array\n";
		//PrintArray(VectorOfUnique);

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