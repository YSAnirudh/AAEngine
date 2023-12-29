#pragma once

#include <memory>

namespace AAEngine {

	template<typename T>
	using TSharedPtr = std::shared_ptr<T>;

#define MakeShared(...) std::make_shared(##__VA_ARGS__) 
}