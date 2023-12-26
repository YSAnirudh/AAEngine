#pragma once

namespace AAEngine {

	class CTester
	{
	public:
		static void RunTester();
	private:
		// Math Lib tests
		static void MatrixTests();

		// Container Tests
		static void StaticArrayTests();
		static void DynamicArrayTests();

		// Memory Tests
		static void UniquePtrTests();
	};
}