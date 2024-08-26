#pragma once

#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>

namespace AAEngine {

	// TO DO: Search for TMap/others and replace with AA Engine function calls when AA Engine containers are made.

	template<typename KeyType, typename ValType> 
	using TMap = std::unordered_map<KeyType, ValType>;

	template<typename KeyType, typename ValType>
	using TOrderedMap = std::map<KeyType, ValType>;

	template<typename ElemType>
	using TSet = std::unordered_set<ElemType>;

	template<typename ElemType>
	using TOrderedSet = std::set<ElemType>;
}