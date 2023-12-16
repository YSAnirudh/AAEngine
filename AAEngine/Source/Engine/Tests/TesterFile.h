#pragma once

namespace AAEngine {

	class CTester
	{
	public:
		static void RunTester();
	private:
		// Container Tests
		static void StaticArrayTests();
		static void DynamicArrayTests();

		// Memory Tests
		static void UniquePtrTests();
	};
}