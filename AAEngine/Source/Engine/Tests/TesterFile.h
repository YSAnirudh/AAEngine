#pragma once

namespace AAEngine {

	class CTester
	{
	public:
		static void RunTester();
	private:
		// Math Lib tests
		static void MatrixTests();
		static void MatrixGLMTests();

		// Container Tests
		static void AlgorithmTests();
		static void StaticArrayTests();
		static void DynamicArrayTests();

		// Memory Tests
		static void UniquePtrTests();
	};
}