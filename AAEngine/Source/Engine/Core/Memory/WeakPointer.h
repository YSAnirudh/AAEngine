#pragma once

#include <memory>

namespace AAEngine {

	template<typename T>
	using TWeakPtr = std::weak_ptr<T>;
}