#pragma once

namespace AAEngine {

	template<typename DataType>
	class TStack
	{
	public:

	private:
		T* InternalStack{ nullptr };
		size_t Size;
		size_t Top;
	};
}