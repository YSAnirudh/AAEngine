#pragma once

#include "Containers/RedBlackTree.h"
#include "Containers/KeyValuePair.h"

namespace AAEngine {

	template<typename KeyType, typename ValueType, typename Predicate = std::less<KeyType>, typename KeyCompare = std::equal_to<KeyType>>
	class TOrderedMap : private TRedBlackTree<TPair<KeyType, ValueType>, Predicate>
	{
		using MapType = TPair<const KeyType, ValueType>;

	};
}