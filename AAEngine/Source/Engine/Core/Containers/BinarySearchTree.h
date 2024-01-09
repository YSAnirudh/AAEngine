#pragma once

#include "Core/Core.h"
#include "Math/Math.h"

#include <functional>

namespace AAEngine {


	/*
	* Iterator used to iterate over the Tree values
	*
	* @tparam InDataType - Type of the Iterator - TBSTNode<T>
	*/
	template<typename InDataType>
	class TBSTIterator
	{
	public:
		using ValType = InDataType;
		using PtrType = ValType*;
		using RefType = ValType&;
		using PtrDiffType = ptrdiff_t;

		/*
		* Default constructor for TBSTIterator.
		*/
		FORCEINLINE constexpr TBSTIterator() noexcept
			: Pointer(nullptr)
		{
		}

		/*
		* Constructor for TBSTIterator.
		*
		* @param Data - Pointer to the data.
		*/
		FORCEINLINE constexpr TBSTIterator(PtrType Data) noexcept
			: Pointer(Data)
		{
		}

		/*
		* Constructor for TBSTIterator.
		*
		* @param Data - Reference to the data.
		*/
		FORCEINLINE constexpr TBSTIterator(RefType Data) noexcept
			: Pointer(&Data)
		{
		}

		/*
		* Dereferencing operator to get the value at the iterator.
		*
		* @returns Reference to the value at the iterator.
		*/
		FORCEINLINE constexpr RefType operator*() const noexcept
		{
			return *Pointer;
		}

		/*
		* Member access operator to access methods/properties of the value at the iterator.
		*
		* @returns Pointer to the value at the iterator.
		*/
		FORCEINLINE constexpr PtrType operator->() const noexcept
		{
			return Pointer;
		}

		/*
		* Pre-increment operator: Moves the iterator to the next element in the Tree => Next element greater that this.
		*
		* @returns Reference to the updated iterator.
		*/
		FORCEINLINE constexpr TBSTIterator& operator++() noexcept
		{
			Pointer = GetNextElement();
			return *this;
		}

		/*
		* Post-increment operator: Creates a copy of the current iterator, moves the original to the next element, and returns the copy.
		*
		* @returns Copy of the current iterator before increment.
		*/
		FORCEINLINE constexpr TBSTIterator operator++(int) noexcept
		{
			TBSTIterator It = *this;
			Pointer = GetNextElement();
			return It;
		}

		/*
		* Pre-decrement operator: Moves the iterator to the previous element in the Tree => Next element less that this.
		*
		* @returns Reference to the updated iterator.
		*/
		FORCEINLINE constexpr TBSTIterator& operator--() noexcept
		{
			Pointer = GetPreviousElement();
			return *this;
		}

		/*
		* Post-decrement operator: Creates a copy of the current iterator, moves the original to the previous element, and returns the copy.
		*
		* @returns Copy of the current iterator before decrement.
		*/
		FORCEINLINE constexpr TBSTIterator operator--(int) noexcept
		{
			TBSTIterator It = *this;
			Pointer = GetPreviousElement();
			return It;
		}

		/*
		* Equality operator for iterators: Checks if two iterators are pointing to the same location.
		*
		* @param Other - The iterator to compare.
		*
		* @returns True if the iterators are pointing to the same location, false otherwise.
		*/
		FORCEINLINE constexpr bool operator==(const TBSTIterator& Other) const noexcept
		{
			return Other.Pointer == Pointer;
		}

		/*
		* Inequality operator for iterators: Checks if two iterators are not pointing to the same location.
		*
		* @param Other - The iterator to compare.
		*
		* @returns True if the iterators are not pointing to the same location, false otherwise.
		*/
		FORCEINLINE constexpr bool operator!=(const TBSTIterator& Other) const noexcept
		{
			return Other.Pointer != Pointer;
		}

		/*
		* Function to retrieve the pointer stored in the iterator.
		*
		* @returns Pointer stored in the iterator.
		*/
		FORCEINLINE constexpr PtrType Get() const noexcept
		{
			return Pointer;
		}

	private:
		/*
		* Function to get the Next element => Greater element in the tree.
		*
		* @returns Pointer to the Next Element
		*/
		FORCEINLINE constexpr PtrType GetNextElement() const noexcept
		{
			if (Pointer == nullptr)
			{
				return nullptr;
			}

			PtrType Temp = Pointer;

			if (Temp->Right != nullptr)
			{
				Temp = Temp->Right;

				while (Temp->Left != nullptr)
				{
					Temp = Temp->Left;
				}
				return Temp;
			}

			while (Temp->Parent != nullptr && Temp->Parent->Right == Temp)
			{
				Temp = Temp->Parent;
			}
			Temp = Temp->Parent;
			return Temp;
		}

		/*
		* Function to get the Previous element => Lesser element in the tree.
		*
		* @returns Pointer to the Previous Element
		*/
		FORCEINLINE constexpr PtrType GetPreviousElement() const noexcept
		{
			if (Pointer == nullptr)
			{
				return nullptr;
			}

			PtrType Temp = Pointer;

			if (Temp->Left != nullptr)
			{
				Temp = Temp->Left;

				while (Temp->Right != nullptr)
				{
					Temp = Temp->Right;
				}
				return Temp;
			}

			while (Temp->Parent != nullptr && Temp->Parent->Left == Temp)
			{
				Temp = Temp->Parent;
			}
			Temp = Temp->Parent;
			return Temp;
		}

	private:
		/*
		* Pointer for the Array Elements for the iterator.
		*/
		PtrType Pointer;
	};
	
	/*
	* Templated Struct for storing Data about a Binary Search Tree Node
	*
	* @tparam - T - Type of the Value stored in the Node.
	* Node -	Left Node
	*			Right Node
	*			Parent Node
	*			Node Value
	*/
	template<typename T>
	struct TBSTNode
	{
	public:
		/*
		* Deleted Default Constructor => Needs value to construct a node
		*/
		TBSTNode() = delete;

		/*
		* Constructor taking in ref to the Value of the node, and Left, Right, Parent = nullptr
		*
		* @param Val - const L value ref to Value of the Current Node
		*/
		FORCEINLINE constexpr TBSTNode(const T& Val) noexcept
			: Value(Val), Left(nullptr), Right(nullptr), Parent(nullptr)
		{
		}

		/*
		* Constructor taking in the ref to Value of the node, and Left, Right, Parent node pointers
		*
		* @param Val - const L value ref to Value of the Current Node
		* @param InLeft - Pointer to the new Left Node Value
		* @param InRight - Pointer to the new Right Node Value
		* @param InParent - Pointer to the new Parent Node Value
		*/
		FORCEINLINE constexpr TBSTNode(const T& Val, TBSTNode<T>* InLeft, TBSTNode<T>* InRight, TBSTNode<T>* InParent) noexcept
			: Value(Val), Left(InLeft), Right(InRight), Parent(InParent)
		{
		}

		/*
		* Constructor taking in the r value ref to Value of the node, and Left, Right, Parent = nullptr
		*
		* @param Val - R Value ref of Value of the Current Node
		*/
		FORCEINLINE constexpr TBSTNode(T&& Val) noexcept
			: Value(Move(Val)), Left(nullptr), Right(nullptr), Parent(nullptr)
		{
		}

		/*
		* Constructor taking in the r value ref to Value of the node, and Left, Right, Parent node pointers
		*
		* @param Val - R Value ref of Value of the Current Node
		* @param InLeft - Pointer to the new Left Node Value
		* @param InRight - Pointer to the new Right Node Value
		* @param InParent - Pointer to the new Parent Node Value
		*/
		FORCEINLINE constexpr TBSTNode(T&& Val, TBSTNode<T>* InLeft, TBSTNode<T>* InRight, TBSTNode<T>* InParent) noexcept
			: Value(Move(Val)), Left(InLeft), Right(InRight), Parent(InParent)
		{
		}

		/*
		* Constructor taking in the r value ref to arguments to construct Value of the node, and Left, Right, Parent node pointers
		*
		* @param InLeft - Pointer to the new Left Node Value
		* @param InRight - Pointer to the new Right Node Value
		* @param InParent - Pointer to the new Parent Node Value
		* @param InArgs - R Value ref to the variadic arguments to construct the Value of the Node
		*/
		template<typename... Args>
		FORCEINLINE constexpr TBSTNode(TBSTNode<T>* InLeft, TBSTNode<T>* InRight, TBSTNode<T>* InParent, Args&&... InArgs) noexcept
			: Left(InLeft), Right(InRight), Parent(InParent)
		{
			new(&Value) T(Forward<Args>(InArgs)...);
		}

		/*
		* Copy Constructor taking another Node
		*
		* @param Other - const L Value ref to the Other Node
		*/
		FORCEINLINE constexpr TBSTNode(const TBSTNode& Other) noexcept
		{
			new(&Value) T(Other.Value);
			Left = Other.Left;
			Right = Other.Right;
			Parent = Other.Parent;
		}

		/*
		* Move Constructor taking another Node
		*
		* @param Other - R Value ref to the Other Node
		*/
		FORCEINLINE constexpr TBSTNode(TBSTNode&& Other) noexcept
		{
			new(&Value) T(Move(Other.Value));
			Left = Other.Left;
			Right = Other.Right;
			Parent = Other.Parent;
		}

		/*
		* Copy Assignment Operator taking another Node
		*
		* @param Other - const L Value ref to the Other Node
		*/
		FORCEINLINE constexpr TBSTNode& operator=(const TBSTNode& Other) noexcept
		{
			new(&Value) T(Other.Value);
			Left = Other.Left;
			Right = Other.Right;
			Parent = Other.Parent;
			return *this;
		}

		/*
		* Move Assignment Operator taking another Node
		*
		* @param Other - R Value ref to the Other Node
		*/
		FORCEINLINE constexpr TBSTNode& operator=(TBSTNode&& Other) noexcept
		{
			new(&Value) T(Move(Other.Value));
			Left = Other.Left;
			Right = Other.Right;
			Parent = Other.Parent;
			return *this;
		}

		/*
		* Default destructor
		*/
		FORCEINLINE ~TBSTNode()
		{
			Parent = nullptr;
			Left = nullptr;
			Right = nullptr;
		}

		/*
		* Allocates memory to the New Node, Copies the Value and returns it
		*
		* @param Val - const L Value ref to the New Node
		* @param Left - Pointer to the Left node for the New Node, defaulted to nullptr
		* @param Right - Pointer to the Right node for the New Node, defaulted to nullptr
		* @param Parent - Pointer to the Parent node for the New Node, defaulted to nullptr
		*
		* @returns Pointer to the New Node
		*/
		FORCEINLINE constexpr static TBSTNode<T>* MakeNewNode(const T& Val, TBSTNode<T>* Left = nullptr, TBSTNode<T>* Right = nullptr, TBSTNode<T>* Parent = nullptr) noexcept
		{
			return new TBSTNode<T>(Val, Left, Right, Parent);
		}

		/*
		* Allocates memory to the New Node, Moves the value and returns it
		*
		* @param Val - const L Value ref to the New Node
		* @param Left - Pointer to the Left node for the New Node, defaulted to nullptr
		* @param Right - Pointer to the Right node for the New Node, defaulted to nullptr
		* @param Parent - Pointer to the Parent node for the New Node, defaulted to nullptr
		*
		* @returns Pointer to the New Node
		*/
		FORCEINLINE constexpr static TBSTNode<T>* MakeNewNode(T&& Val, TBSTNode<T>* Left = nullptr, TBSTNode<T>* Right = nullptr, TBSTNode<T>* Parent = nullptr) noexcept
		{
			return new TBSTNode<T>(Left, Right, Parent, Move(Val));
		}

		/*
		* Allocates memory to the New Node, Constructs the Value inplace and returns it
		*
		* @tparam Args - Variadic Arguments used to construct the Value inplace
		*
		* @param Left - Pointer to the Left node for the New Node
		* @param Right - Pointer to the Right node for the New Node
		* @param Parent - Pointer to the Parent node for the New Node
		* @param Val - Variadic Arguments used to construct the Value inplace
		*
		* @returns Pointer to the New Node
		*/
		template<typename... Args>
		FORCEINLINE constexpr static void EmplaceNewNode(TBSTNode<T>* EmplaceTo, TBSTNode<T>* Left, TBSTNode<T>* Right, TBSTNode<T>* Parent, Args&&... Val) noexcept
		{
			EmplaceTo = (TBSTNode<T>*)::operator new(sizeof(TBSTNode<T>));
			new(EmplaceTo) TBSTNode<T>(Left, Right, Parent, Forward<Args>(Val)...);
		}

	public:
		/*
		* Pointer to the Parent node of this node
		*/
		TBSTNode* Parent;
		/*
		* Pointer to the Left node of this node
		*/
		TBSTNode* Left;
		/*
		* Pointer to the Right node of this node
		*/
		TBSTNode* Right;
		/*
		* Value of the Node
		*/
		T Value;
	};

	/*
	* Templated class for representing a Binary Search Tree
	* 
	* @tparam - T - Type of the Values stored in the Binary Search Tree.
	* @tparam - Predicate - The way for compare 2 values
	*/
	template<typename T, typename Predicate = std::less<T>>
	class TBinarySearchTree
	{
	private:
	public:
		/*
		* Default constructor initializes Root to nullptr => No Elements
		*/
		FORCEINLINE constexpr TBinarySearchTree() noexcept
			: Root(nullptr)
		{
		}

		/*
		* Copy Constructor initializes Root to Other.Root 
		* 
		* @param Other - const L Value ref to Other BST
		*/
		FORCEINLINE constexpr TBinarySearchTree(const TBinarySearchTree& Other) noexcept
			: Root(Other.Root)
		{
		}

		/*
		* Move Constructor initializes Root to Other.Root
		* 
		* @param Other - R Value ref to Other BST
		*/
		FORCEINLINE constexpr TBinarySearchTree(TBinarySearchTree&& Other) noexcept
			: Root(Move(Other.Root))
		{
		}

		/*
		* Copy Assignment Operator initializes Root to Other.Root
		*
		* @param Other - const L Value ref to Other BST
		*/
		FORCEINLINE constexpr TBinarySearchTree& operator=(const TBinarySearchTree& Other) noexcept
		{
			Root = Other.Root;
			return *this;
		}

		/*
		* Move Assignment Operator initializes Root to Other.Root
		*
		* @param Other - R Value ref to Other BST
		*/
		FORCEINLINE constexpr TBinarySearchTree& operator=(TBinarySearchTree&& Other) noexcept
		{
			Root = Move(Other.Root);
			return *this;
		}

		/*
		* Inserts a node into the Binary Search Tree
		* 
		* @param NewVal - const L Value Ref to the Value to be inserted into the BST
		*/
		FORCEINLINE constexpr void Insert(const T& NewVal) noexcept
		{
			InsertHelper(Root, NewVal);
		}

		/*
		* Inserts a node into the Binary Search Tree
		*
		* @param NewVal - R Value Ref to the Value to be inserted into the BST
		*/
		FORCEINLINE constexpr void Insert(T&& NewVal) noexcept
		{
			InsertHelper(Root, Move(NewVal));
		}

		/*
		* Removes a node from the Binary Search Tree
		*
		* @param NewVal - const L Value Ref to the Value to be removed from the BST
		* 
		* @returns true if Node with NewVal has been removed, false if Node doesn't exist and hasn't been removed
		* TO DO: Add Remove with Move Value (R Value Ref)??
		*/
		FORCEINLINE constexpr bool Remove(const T& NewVal) noexcept
		{
			return RemoveHelper(Root, NewVal);
		}

		/*
		* Searches a node into the Binary Search Tree
		*
		* @param NewVal - const L Value Ref to the Value to be inserted into the BST
		* 
		* @returns true if Node of NewVal exists, false otherwise
		* TO DO: Add Search with Move Value (R Value Ref)??
		*/
		FORCEINLINE constexpr bool Search(const T& NewVal) noexcept
		{
			return SearchHelper(Root, NewVal);
		}

		/*
		* Counts the number of nodes in the Binary Search Tree
		*
		* @returns Count of the number of nodes in the Binary Search Tree
		*/
		FORCEINLINE constexpr size_t Num() const noexcept
		{
			size_t Count = 0;
			for (const auto& Node : *this)
			{
				Count++;
			}
			return Count;
		}

		/*
		* Height of the Binary Search Tree
		*
		* @returns Height of the Binary Search Tree
		*/
		FORCEINLINE constexpr size_t Height() const noexcept
		{
			return HeightHelper(Root);
		}

		/*
		* Prints the Tree InOrder
		* Root = [R] and the R - Go Right, L - Go Left.
		* 
		* => Value 5 in the Right Subtree would look similar to => 5 [R]RLRLRLRRRL
		*/
		FORCEINLINE constexpr void InOrderPrint() noexcept
		{
			InOrderPrintHelper(Root, "[R]");
			std::cout << "\n";
		}

		/*
		* Prints the Tree PreOrder
		* Root = [R] and the R - Go Right, L - Go Left.
		*
		* => Value 5 in the Right Subtree would look similar to => 5 [R]RLRLRLRRRL
		*/
		FORCEINLINE constexpr void PreOrderPrint() noexcept
		{
			PreOrderPrintHelper(Root, "[R]");
			std::cout << "\n";
		}

		/*
		* Prints the Tree PostOrder
		* Root = [R] and the R - Go Right, L - Go Left.
		*
		* => Value 5 in the Right Subtree would look similar to => 5 [R]RLRLRLRRRL
		*/
		FORCEINLINE constexpr void PostOrderPrint() noexcept
		{
			PostOrderPrintHelper(Root, "[R]");
			std::cout << "\n";
		}

		/*
		* Destructor that frees memory from the Binary Search Tree and sets the Root to nullptr
		*/
		FORCEINLINE ~TBinarySearchTree()
		{
			FreeBSTHelper(Root);
			Root = nullptr;
		}

		/*
		* Clear Function that frees memory from the Binary Search Tree and sets the Root to nullptr
		*/
		FORCEINLINE constexpr void Clear() noexcept
		{
			FreeBSTHelper(Root);
			Root = nullptr;
		}

	private:
		/*
		* Height Helper that gets the height of the Binary Search Tree recursively
		*
		* @param Current - Currently looked at node to perform Height getting opertation
		* @return Height of the Binary Search Tree
		*/
		FORCEINLINE constexpr size_t HeightHelper(TBSTNode<T>* Current) noexcept
		{
			if (Current == nullptr)
			{
				return 0;
			}

			size_t LeftHeight = 0, RightHeight = 0;
			if (Current->Left != nullptr)
			{
				LeftHeight = HeightHelper(Current->Left);
			}
			if (Current->Right != nullptr)
			{
				RightHeight = HeightHelper(Current->Right);
			}

			return FMath::Max(LeftHeight, RightHeight) + 1;
		}

		/*
		* Insert Helper that Inserts a node into the Binary Search Tree recursively
		*
		* @param Current - Currently looked at node to perform insertion
		* @param NewVal - const L Value Ref to the Value to be inserted into the BST
		*/
		FORCEINLINE constexpr void InsertHelper(TBSTNode<T>* Current, const T& NewVal) noexcept
		{
			if (Current == Root)
			{
				// If Tree is empty insert at root.
				if (Root == nullptr)
				{
					Root = TBSTNode<T>::MakeNewNode(NewVal);
					return;
				}
			}

			if (NewVal == Current->Value)
			{
				// Dont insert value
				return;
			}
			else if (Pred(NewVal, Current->Value))
			{
				// Look to the Left
				if (Current->Left == nullptr)
				{
					Current->Left = TBSTNode<T>::MakeNewNode(NewVal, nullptr, nullptr, Current);
				}
				else
				{
					InsertHelper(Current->Left, NewVal);
				}
			}
			else if (Pred(Current->Value, NewVal))
			{
				// Look to the Right
				if (Current->Right == nullptr)
				{
					Current->Right = TBSTNode<T>::MakeNewNode(NewVal, nullptr, nullptr, Current);
				}
				else
				{
					InsertHelper(Current->Right, NewVal);
				}
			}
			return;
		}

		/*
		* Insert Helper that Inserts a node into the Binary Search Tree recursively
		*
		* @param Current - Currently looked at node to perform insertion
		* @param NewVal - R Value Ref to the Value to be inserted into the BST
		*/
		FORCEINLINE constexpr void InsertHelper(TBSTNode<T>* Current, T&& NewVal) noexcept
		{
			if (Current == Root)
			{
				// If Tree is empty insert at root.
				if (Root == nullptr)
				{
					Root = TBSTNode<T>::MakeNewNode(Move(NewVal));
					return;
				}
			}

			if (NewVal == Current->Value)
			{
				// Dont insert value
				return;
			}
			else if (Pred(NewVal, Current->Value))
			{
				// Look to the Left
				if (Current->Left == nullptr)
				{
					Current->Left = TBSTNode<T>::MakeNewNode(Move(NewVal), nullptr, nullptr, Current);
				}
				else
				{
					InsertHelper(Current->Left, Move(NewVal));
				}
			}
			else if (Pred(Current->Value, NewVal))
			{
				// Look to the Right
				if (Current->Right == nullptr)
				{
					Current->Right = TBSTNode<T>::MakeNewNode(Move(NewVal), nullptr, nullptr, Current);
				}
				else
				{
					InsertHelper(Current->Right, Move(NewVal));
				}
			}
			return;
		}

		/*
		* Remove Helper that Removes a node from the Binary Search Tree recursively
		*
		* @param Current - Currently looked at node to perform deletion
		* @param NewVal - const L Value Ref to the Value to be removed from the BST
		* 
		* @returns true if Node with NewVal has been removed, false if Node doesn't exist and hasn't been removed
		*/
		FORCEINLINE constexpr bool RemoveHelper(TBSTNode<T>* Current, const T& NewVal) noexcept
		{
			if (Current == nullptr)
			{
				return false;
			}
			else
			{
				if (NewVal == Current->Value)
				{
					if (Current->Left == nullptr && Current->Right == nullptr)
					{
						if (Current == Root)
						{
							Root = nullptr;
						}
						else
						{
							ReconnectParent(Current, nullptr);
						}
					}
					else if (Current->Left == nullptr && Current->Right != nullptr)
					{
						if (Current == Root)
						{
							Root = Current->Right;
							Root->Parent = nullptr;
						}
						else
						{
							Current->Right->Parent = Current->Parent;
							ReconnectParent(Current, Current->Right);
						}
					}
					else if (Current->Left != nullptr && Current->Right == nullptr)
					{
						if (Current == Root)
						{
							Root = Current->Left;
							Root->Parent = nullptr;
						}
						else
						{
							Current->Left->Parent = Current->Parent;
							ReconnectParent(Current, Current->Left);
						}
					}
					else
					{
						TBSTNode<T>* MinNodeInRightSubTree = FindMinInSubTree(Current->Right);
						if (MinNodeInRightSubTree->Right)
						{
							MinNodeInRightSubTree->Right->Parent = MinNodeInRightSubTree->Parent;
						}
						ReconnectParent(MinNodeInRightSubTree, MinNodeInRightSubTree->Right);
						if (Current == Root)
						{
							MinNodeInRightSubTree->Right = Current->Right;
							MinNodeInRightSubTree->Left = Current->Left;
							MinNodeInRightSubTree->Parent = nullptr;
							if (Current->Right)
							{
								Current->Right->Parent = MinNodeInRightSubTree;
							}
							if (Current->Left)
							{
								Current->Left->Parent = MinNodeInRightSubTree;
							}
						}
						else
						{
							MinNodeInRightSubTree->Right = Current->Right;
							MinNodeInRightSubTree->Left = Current->Left;
							MinNodeInRightSubTree->Parent = Current->Parent;
							if (Current->Right)
							{
								Current->Right->Parent = MinNodeInRightSubTree;
							}
							if (Current->Left)
							{
								Current->Left->Parent = MinNodeInRightSubTree;
							}
							ReconnectParent(Current, MinNodeInRightSubTree);
						}
					}
					delete Current;
					Current = nullptr;
					return true;
				}
				else if (Pred(NewVal, Current->Value))
				{
					// Look to the Left
					if (Current->Left != nullptr)
					{
						return RemoveHelper(Current->Left, NewVal);
					}
					else
					{
						return false;
					}
				}
				else if (Pred(Current->Value, NewVal))
				{
					// Look to the Right
					if (Current->Right != nullptr)
					{
						return RemoveHelper(Current->Right, NewVal);
					}
					else
					{
						return false;
					}
				}
				return false;
			}
		}

		/*
		* Search Helper that Searches a node from the Binary Search Tree recursively
		*
		* @param Current - Currently looked at node to perform deletion
		* @param NewVal - const L Value Ref to the Value to be searched for in the BST
		* 
		* @returns true if Node with NewVal exists, false otherwise
		*/
		FORCEINLINE constexpr bool SearchHelper(TBSTNode<T>* Current, const T& NewVal) noexcept
		{
			if (Current == nullptr)
			{
				return false;
			}
			else
			{
				if (NewVal == Current->Value)
				{
					return true;
				}
				else if (Pred(NewVal, Current->Value))
				{
					// Look to the Left
					return SearchHelper(Current->Left, NewVal);
				}
				else if (Pred(Current->Value, NewVal))
				{
					// Look to the Right
					return SearchHelper(Current->Right, NewVal);
				}
			}
			return false;
		}

		FORCEINLINE constexpr void ReconnectParent(TBSTNode<T>* Current, TBSTNode<T>* NewConnection) noexcept
		{
			if (Current == nullptr)
			{
				return;
			}
			if (Current->Parent)
			{
				if (Current->Parent->Right == Current)
				{
					Current->Parent->Right = NewConnection;
				}
				else if (Current->Parent->Left == Current)
				{
					Current->Parent->Left = NewConnection;
				}
			}
		}

		/*
		* Find Min Value node in Subtree
		* 
		* @param SubTreeRoot - Root node of the Subtree
		* 
		* @returns Pointer to the Node with the Min Value
		*/
		FORCEINLINE constexpr TBSTNode<T>* FindMinInSubTree(TBSTNode<T>* SubTreeRoot) noexcept
		{
			if (SubTreeRoot == nullptr)
			{
				return nullptr;
			}

			if (SubTreeRoot->Left == nullptr)
			{
				return SubTreeRoot;
			}
			else
			{
				// Keep going left to find the min value
				return FindMinInSubTree(SubTreeRoot->Left);
			}
		}

		/*
		* Find Max Value node in Subtree
		*
		* @param SubTreeRoot - Root node of the Subtree
		*
		* @returns Pointer to the Node with the Max Value
		*/
		FORCEINLINE constexpr TBSTNode<T>* FindMaxInSubTree(TBSTNode<T>* SubTreeRoot) noexcept
		{
			if (SubTreeRoot == nullptr)
			{
				return nullptr;
			}

			if (SubTreeRoot->Right == nullptr)
			{
				return SubTreeRoot;
			}
			else
			{
				// Keep going right to find the max value
				return FindMaxInSubTree(SubTreeRoot->Right);
			}
		}

		/*
		* Helper that frees memory form the Binary Search Tree recursively
		*
		* @param Current - Currently looked at node to perform freeing on the Node and it's subtree
		*/
		FORCEINLINE constexpr void FreeBSTHelper(TBSTNode<T>* Current) noexcept
		{
			if (Current == nullptr)
			{
				return;
			}
			if (Current->Left != nullptr)
			{
				FreeBSTHelper(Current->Left);
				Current->Left = nullptr;
			}

			if (Current->Right != nullptr)
			{
				FreeBSTHelper(Current->Right);
				Current->Right = nullptr;
			}

			delete Current;
		}

		/*
		* BELOW = HELPER FUNCTIONS FOR TESTING. SHOULD NOT BE USED
		* \/\/\/
		*/
		template<typename FuncType = void()>
		FORCEINLINE constexpr void InOrderPrintHelper(TBSTNode<T>* Current, const std::string& AppendString = "")
		{
			if (Current == nullptr)
			{
				return;
			}
			if (!AppendString.empty())
			{
				InOrderPrintHelper(Current->Left, AppendString + "L");
				std::cout << "[CORE] " << Current->Value << " " << AppendString << "\n";
				InOrderPrintHelper(Current->Right, AppendString + "R");
			}
			else
			{
				InOrderPrintHelper(Current->Left, AppendString);
				std::cout << "[CORE] " << Current->Value << "\n";
				InOrderPrintHelper(Current->Right, AppendString);
			}
		}

		template<typename FuncType = void()>
		FORCEINLINE constexpr void PreOrderPrintHelper(TBSTNode<T>* Current, const std::string& AppendString = "")
		{
			if (Current == nullptr)
			{
				return;
			}
			if (!AppendString.empty())
			{
				std::cout << "[CORE] " << Current->Value << " " << AppendString << "\n";
				PreOrderPrintHelper(Current->Left, AppendString + "L");
				PreOrderPrintHelper(Current->Right, AppendString + "R");
			}
			else
			{
				std::cout << "[CORE] " << Current->Value << "\n";
				PreOrderPrintHelper(Current->Left, AppendString);
				PreOrderPrintHelper(Current->Right, AppendString);
			}
		}

		// Accepts function pointers so that the Helper can run a function for the PreOrder
		template<typename FuncType = void()>
		FORCEINLINE constexpr void PostOrderPrintHelper(TBSTNode<T>* Current, const std::string& AppendString = "")
		{
			if (Current == nullptr)
			{
				return;
			}

			if (!AppendString.empty())
			{
				PostOrderPrintHelper(Current->Left, AppendString + "L");
				PostOrderPrintHelper(Current->Right, AppendString + "R");
				std::cout << "[CORE] " << Current->Value << " " << AppendString << "\n";
			}
			else
			{
				PostOrderPrintHelper(Current->Left, AppendString);
				PostOrderPrintHelper(Current->Right, AppendString);
				std::cout << "[CORE] " << Current->Value << "\n";
			}
		}
		/*
		* /\/\/\
		* ABOVE = HELPER FUNCTIONS FOR TESTING. SHOULD NOT BE USED
		*/


	private:
		/*
		* Root Node for the Tree
		*/
		TBSTNode<T>* Root{ nullptr };
		/*
		* Predicate function used to compare values
		*/
		Predicate Pred;

	private:


	public:
		// Const and Non-Const Iterators
		using Iterator = TBSTIterator<TBSTNode<T>>;
		using ConstIterator = TBSTIterator<const TBSTNode<T>>;

		// Functions for Tree Iteration
		FORCEINLINE Iterator begin()
		{
			if (Root == nullptr)
			{
				return Iterator(nullptr);
			}
			TBSTNode<T>* Temp = Root;
			while (Temp->Left != nullptr)
			{
				Temp = Temp->Left;
			}
			return Iterator(*Temp);
		}
		FORCEINLINE ConstIterator begin() const
		{
			if (Root == nullptr)
			{
				return ConstIterator(nullptr);
			}
			TBSTNode<T>* Temp = Root;
			while (Temp->Left != nullptr)
			{
				Temp = Temp->Left;
			}
			return ConstIterator(*Temp);
		}
		FORCEINLINE Iterator			end() { return Iterator(nullptr); }
		FORCEINLINE ConstIterator		end() const { return ConstIterator(nullptr); }
	};
}