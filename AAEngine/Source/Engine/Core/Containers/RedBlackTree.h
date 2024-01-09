#pragma once

#include "Core/Core.h"
#include "Math/Math.h"

#include <functional>

namespace AAEngine {


	/*
	* Iterator used to iterate over the Tree values
	*
	* @tparam InDataType - Type of the Iterator - TRBNode<T>
	*/
	template<typename InDataType>
	class TRedBlackIterator
	{
	public:
		using ValType = InDataType;
		using PtrType = ValType*;
		using RefType = ValType&;
		using PtrDiffType = ptrdiff_t;

		/*
		* Default constructor for TRedBlackIterator.
		*/
		FORCEINLINE constexpr TRedBlackIterator() noexcept
			: Pointer(nullptr)
		{
		}

		/*
		* Constructor for TRedBlackIterator.
		*
		* @param Data - Pointer to the data.
		*/
		FORCEINLINE constexpr TRedBlackIterator(PtrType Data) noexcept
			: Pointer(Data)
		{
		}

		/*
		* Constructor for TRedBlackIterator.
		*
		* @param Data - Reference to the data.
		*/
		FORCEINLINE constexpr TRedBlackIterator(RefType Data) noexcept
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
		FORCEINLINE constexpr TRedBlackIterator& operator++() noexcept
		{
			Pointer = GetNextElement();
			return *this;
		}

		/*
		* Post-increment operator: Creates a copy of the current iterator, moves the original to the next element, and returns the copy.
		*
		* @returns Copy of the current iterator before increment.
		*/
		FORCEINLINE constexpr TRedBlackIterator operator++(int) noexcept
		{
			TRedBlackIterator It = *this;
			Pointer = GetNextElement();
			return It;
		}

		/*
		* Pre-decrement operator: Moves the iterator to the previous element in the Tree => Next element less that this.
		*
		* @returns Reference to the updated iterator.
		*/
		FORCEINLINE constexpr TRedBlackIterator& operator--() noexcept
		{
			Pointer = GetPreviousElement();
			return *this;
		}

		/*
		* Post-decrement operator: Creates a copy of the current iterator, moves the original to the previous element, and returns the copy.
		*
		* @returns Copy of the current iterator before decrement.
		*/
		FORCEINLINE constexpr TRedBlackIterator operator--(int) noexcept
		{
			TRedBlackIterator It = *this;
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
		FORCEINLINE constexpr bool operator==(const TRedBlackIterator& Other) const noexcept
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
		FORCEINLINE constexpr bool operator!=(const TRedBlackIterator& Other) const noexcept
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

			if (Temp->Right != nullptr && !Temp->Right->bIsNil)
			{
				Temp = Temp->Right;

				while (Temp->Left != nullptr && !Temp->Left->bIsNil)
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

			if (Temp->Left != nullptr && !Temp->Left->bIsNil)
			{
				Temp = Temp->Left;

				while (Temp->Right != nullptr && !Temp->Right->bIsNil)
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
	* Templated Struct for storing Data about a Red Black Tree Node
	*
	* @tparam - T - Type of the Value stored in the Node.
	* Node -	Left Node
	*			Right Node
	*			Parent Node
	*			Node Value
	*			bIsBlack - Black = true, Red = false
	*/
	template<typename T>
	struct TRBNode
	{
	public:
		/*
		* Deleted Default Constructor => Needs value to construct a node
		*/
		TRBNode() = delete;

		/*
		* Constructor taking in ref to the Value of the node, and Left, Right, Parent = nullptr, and Color = Red
		*
		* @param Val - const L value ref to Value of the Current Node
		*/
		FORCEINLINE constexpr TRBNode(const T& Val) noexcept
			: Value(Val), Left(nullptr), Right(nullptr), Parent(nullptr), bIsBlack(false)
		{
		}

		/*
		* Constructor taking in the ref to Value of the node, and Left, Right, Parent node pointers, and Color
		*
		* @param Val - const L value ref to Value of the Current Node
		* @param InLeft - Pointer to the new Left Node Value
		* @param InRight - Pointer to the new Right Node Value
		* @param InParent - Pointer to the new Parent Node Value
		* @param bInIsBlack - bool whether the Node is Black
		*/
		FORCEINLINE constexpr TRBNode(const T& Val, TRBNode<T>* InLeft, TRBNode<T>* InRight, TRBNode<T>* InParent, bool bInIsBlack = false) noexcept
			: Value(Val), Left(InLeft), Right(InRight), Parent(InParent), bIsBlack(bInIsBlack)
		{
		}

		/*
		* Constructor taking in the r value ref to Value of the node, and Left, Right, Parent = nullptr, and Color = Red
		*
		* @param Val - R Value ref of Value of the Current Node
		*/
		FORCEINLINE constexpr TRBNode(T&& Val) noexcept
			: Value(Move(Val)), Left(nullptr), Right(nullptr), Parent(nullptr), bIsBlack(false)
		{
		}

		/*
		* Constructor taking in the r value ref to Value of the node, and Left, Right, Parent node pointers, and Color
		*
		* @param Val - R Value ref of Value of the Current Node
		* @param InLeft - Pointer to the new Left Node Value
		* @param InRight - Pointer to the new Right Node Value
		* @param InParent - Pointer to the new Parent Node Value
		* @param bInIsBlack - bool whether the Node is Black
		*/
		FORCEINLINE constexpr TRBNode(T&& Val, TRBNode<T>* InLeft, TRBNode<T>* InRight, TRBNode<T>* InParent, bool bInIsBlack = false) noexcept
			: Value(Move(Val)), Left(InLeft), Right(InRight), Parent(InParent), bIsBlack(bInIsBlack)
		{
		}

		/*
		* Constructor taking in the r value ref to arguments to construct Value of the node, and Left, Right, Parent node pointers
		*
		* @param InLeft - Pointer to the new Left Node Value
		* @param InRight - Pointer to the new Right Node Value
		* @param InParent - Pointer to the new Parent Node Value
		* @param InColor - Color of the Node
		* @param InArgs - R Value ref to the variadic arguments to construct the Value of the Node
		*/
		template<typename... Args>
		FORCEINLINE constexpr TRBNode(TRBNode<T>* InLeft, TRBNode<T>* InRight, TRBNode<T>* InParent, bool bInIsBlack, Args&&... InArgs) noexcept
			: Left(InLeft), Right(InRight), Parent(InParent), bIsBlack(bInIsBlack)
		{
			new(&Value) T(Forward<Args>(InArgs)...);
		}

		/*
		* Copy Constructor taking another Node
		*
		* @param Other - const L Value ref to the Other Node
		*/
		FORCEINLINE constexpr TRBNode(const TRBNode& Other) noexcept
		{
			new(&Value) T(Other.Value);
			Left = Other.Left;
			Right = Other.Right;
			Parent = Other.Parent;
			bIsBlack = Other.bIsBlack;
		}

		/*
		* Move Constructor taking another Node
		*
		* @param Other - R Value ref to the Other Node
		*/
		FORCEINLINE constexpr TRBNode(TRBNode&& Other) noexcept
		{
			new(&Value) T(Move(Other.Value));
			Left = Other.Left;
			Right = Other.Right;
			Parent = Other.Parent;
			bIsBlack = Other.bIsBlack;
		}

		/*
		* Copy Assignment Operator taking another Node
		*
		* @param Other - const L Value ref to the Other Node
		*/
		FORCEINLINE constexpr TRBNode& operator=(const TRBNode& Other) noexcept
		{
			new(&Value) T(Other.Value);
			Left = Other.Left;
			Right = Other.Right;
			Parent = Other.Parent;
			bIsBlack = Other.bIsBlack;
			return *this;
		}

		/*
		* Move Assignment Operator taking another Node
		*
		* @param Other - R Value ref to the Other Node
		*/
		FORCEINLINE constexpr TRBNode& operator=(TRBNode&& Other) noexcept
		{
			new(&Value) T(Move(Other.Value));
			Left = Other.Left;
			Right = Other.Right;
			Parent = Other.Parent;
			bIsBlack = Other.bIsBlack;
			return *this;
		}

		/*
		* Default destructor
		*/
		FORCEINLINE ~TRBNode()
		{
			Parent = nullptr;
			Left = nullptr;
			Right = nullptr;
		}

		/*
		* Static Function that Allocates memory to the New Node, Copies the Value and returns it
		*
		* @param Val - const L Value ref to the New Node
		* @param Left - Pointer to the Left node for the New Node, defaulted to nullptr
		* @param Right - Pointer to the Right node for the New Node, defaulted to nullptr
		* @param Parent - Pointer to the Parent node for the New Node, defaulted to nullptr
		*
		* @returns Pointer to the New Node
		*/
		FORCEINLINE constexpr static TRBNode<T>* MakeNewNode(const T& Val, TRBNode<T>* Left = nullptr, TRBNode<T>* Right = nullptr, TRBNode<T>* Parent = nullptr, bool bIsBlack = false) noexcept
		{
			return new TRBNode<T>(Val, Left, Right, Parent, bIsBlack);
		}

		/*
		* Static Function that Allocates memory to the New Node, Moves the value and returns it
		*
		* @param Val - const L Value ref to the New Node
		* @param Left - Pointer to the Left node for the New Node, defaulted to nullptr
		* @param Right - Pointer to the Right node for the New Node, defaulted to nullptr
		* @param Parent - Pointer to the Parent node for the New Node, defaulted to nullptr
		*
		* @returns Pointer to the New Node
		*/
		FORCEINLINE constexpr static TRBNode<T>* MakeNewNode(T&& Val, TRBNode<T>* Left = nullptr, TRBNode<T>* Right = nullptr, TRBNode<T>* Parent = nullptr, bool bIsBlack = false) noexcept
		{
			return new TRBNode<T>(Left, Right, Parent, bIsBlack, Move(Val));
		}

		/*
		* Static Function that Allocates memory to the New Node, Constructs the Value inplace and returns it
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
		FORCEINLINE constexpr static void EmplaceNewNode(TRBNode<T>* EmplaceTo, TRBNode<T>* Left, TRBNode<T>* Right, TRBNode<T>* Parent, bool bIsBlack, Args&&... Val) noexcept
		{
			EmplaceTo = (TRBNode<T>*)::operator new(sizeof(TRBNode<T>));
			new(EmplaceTo) TRBNode<T>(Left, Right, Parent, bIsBlack, Forward<Args>(Val)...);
		}

	public:
		/*
		* Pointer to the Parent node of this node
		*/
		TRBNode* Parent;
		/*
		* Pointer to the Left node of this node
		*/
		TRBNode* Left;
		/*
		* Pointer to the Right node of this node
		*/
		TRBNode* Right;
		/*
		* Value of the Node
		*/
		T Value;
		/*
		* Boolean for the whether the node is black
		*/
		bool bIsBlack = false;
		/*
		* Boolean for checking if a Node is Nil
		*/
		bool bIsNil = false;
	};

	/*
	* Templated class for representing a Red Black Tree
	*
	* @tparam - T - Type of the Values stored in the Red Black Tree.
	* @tparam - Predicate - The way for compare 2 values
	* 
	* Red Black Tree Rules
	* 1) Nodes are Red or Black
	* 2) Root and Leaf Nodes (Nil) are Black
	* 3) A Red Node has only Black Children
	* 4) All paths from a Node to Nil Descendants contain the same number of Black Nodes
	* 
	* Additional notes:
	* 1) Shortest Path => All Black
	*	 Longest Path => Alternate between red and black
	* 
	* Left Rotation						      |  Right Rotation					
	* - Rotating Node - P				      |  - Rotating Node - P			
	* - Right Child - N					      |  - Left Child - N				
	* - Left Child of N - L				      |  - Right Child of N - R					
	* 									      |  								
	*         P		     ->        N	      |          P		     ->        N
	*       /   \	     ->      /   \	      |        /   \	     ->      /   \
	*      X     N	     ->     P     X	      |       N     X	     ->     X     P
	*           / \	     ->    / \ 		      |      / \	         ->          / \ 	
	*          L   X     ->   X   L           |     X   R		     ->         R   X     
	* 
	* Insertions
	* - Insert and Color Red and then
	*	1) Z is root						=> Color Z Black
	*	2) Z's Uncle is Red					=> Recolor Z's Parent = Black, GrandParent = Red, Uncle = Black
	*	3) Z's Uncle is Black (Triangle)	=> Rotate Z's GrandParent.	(Z's Parent = Left then Right Rotate and vice-versa)
	*	4) Z's Uncle is Black (Line)		=> Rotate Z's GrandParent and recolor Parent = Black and GrandParent = Red.	(Z's Parent = Left then Right Rotate and vice-versa)
	*/
	template<typename T, typename Predicate = std::less<T>>
	class TRedBlackTree
	{
	private:
	public:
		/*
		* Default constructor initializes Root to nullptr => No Elements
		*/
		FORCEINLINE constexpr TRedBlackTree() noexcept
			: Root(nullptr)
		{
			Nil = TRBNode<T>::MakeNewNode(T(), nullptr, nullptr, nullptr, true);
			Nil->bIsNil = true;
		}

		/*
		* Copy Constructor initializes Root to Other.Root
		*
		* @param Other - const L Value ref to Other RBTree
		*/
		FORCEINLINE constexpr TRedBlackTree(const TRedBlackTree& Other) noexcept
			: Root(Other.Root)
		{
		}

		/*
		* Move Constructor initializes Root to Other.Root
		*
		* @param Other - R Value ref to Other RBTree
		*/
		FORCEINLINE constexpr TRedBlackTree(TRedBlackTree&& Other) noexcept
			: Root(Move(Other.Root))
		{
		}

		/*
		* Copy Assignment Operator initializes Root to Other.Root
		*
		* @param Other - const L Value ref to Other RBTree
		*/
		FORCEINLINE constexpr TRedBlackTree& operator=(const TRedBlackTree& Other) noexcept
		{
			Root = Other.Root;
			return *this;
		}

		/*
		* Move Assignment Operator initializes Root to Other.Root
		*
		* @param Other - R Value ref to Other RBTree
		*/
		FORCEINLINE constexpr TRedBlackTree& operator=(TRedBlackTree&& Other) noexcept
		{
			Root = Move(Other.Root);
			return *this;
		}

		/*
		* Inserts a node into the Red Black Tree
		*
		* @param NewVal - const L Value Ref to the Value to be inserted into the RBTree
		*/
		FORCEINLINE constexpr void Insert(const T& NewVal) noexcept
		{
			TRBNode<T>* InsertedNode = InsertHelper(Root, NewVal);
			if (InsertedNode != nullptr)
			{
				InsertedNode->Left = Nil;
				InsertedNode->Right = Nil;
				FixInsertions(InsertedNode);
			}
		}

		/*
		* Inserts a node into the Red Black Tree
		*
		* @param NewVal - R Value Ref to the Value to be inserted into the RBTree
		*/
		FORCEINLINE constexpr void Insert(T&& NewVal) noexcept
		{
			TRBNode<T>* InsertedNode = InsertHelper(Root, Move(NewVal));
			if (InsertedNode != nullptr)
			{
				InsertedNode->Left = Nil;
				InsertedNode->Right = Nil;
				FixInsertions(InsertedNode);
			}
		}

		/*
		* Removes a node from the Red Black Tree
		*
		* @param NewVal - const L Value Ref to the Value to be removed from the RBTree
		*
		* @returns true if Node with NewVal has been removed, false if Node doesn't exist and hasn't been removed
		* TO DO: Add Remove with Move Value (R Value Ref)??
		*/
		FORCEINLINE constexpr bool Remove(const T& NewVal) noexcept
		{
			return RemoveHelper(Root, NewVal);
		}

		/*
		* Searches a node into the Red Black Tree
		*
		* @param NewVal - const L Value Ref to the Value to be inserted into the RBTree
		*
		* @returns true if Node of NewVal exists, false otherwise
		* TO DO: Add Search with Move Value (R Value Ref)??
		*/
		FORCEINLINE constexpr bool Search(const T& NewVal) noexcept
		{
			return SearchHelper(Root, NewVal);
		}

		/*
		* Counts the number of nodes in the Red Black Tree
		*
		* @returns Count of the number of nodes in the Red Black Tree
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
		* Height of the Red Black Tree
		*
		* @returns Height of the Red Black Tree
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
		* Destructor that frees memory from the Red Black Tree and sets the Root to nullptr
		*/
		FORCEINLINE ~TRedBlackTree()
		{
			FreeRBTreeHelper(Root);
			delete Nil;
			Root = nullptr;
			Nil = nullptr;
		}

		/*
		* Clear Function that frees memory from the Red Black Tree and sets the Root to nullptr
		*/
		FORCEINLINE constexpr void Clear() noexcept
		{
			FreeRBTreeHelper(Root);
			delete Nil;
			Root = nullptr;
			Nil = nullptr;
		}

	private:
		/*
		* Height Helper that gets the height of the Red Black Tree recursively
		*
		* @param Current - Currently looked at node to perform Height getting opertation
		* @return Height of the Red Black Tree
		*/
		FORCEINLINE constexpr size_t HeightHelper(TRBNode<T>* Current) noexcept
		{
			if (Current == nullptr)
			{
				return 0;
			}

			size_t LeftHeight = 0, RightHeight = 0;
			if (Current->Left != nullptr && !Current->Left->bIsNil)
			{
				LeftHeight = HeightHelper(Current->Left);
			}
			if (Current->Right != nullptr && !Current->Right->bIsNil)
			{
				RightHeight = HeightHelper(Current->Right);
			}

			return FMath::Max(LeftHeight, RightHeight) + 1;
		}

		/*
		* Insert Helper that Inserts a node into the Red Black Tree recursively
		*
		* @param Current - Currently looked at node to perform insertion
		* @param NewVal - const L Value Ref to the Value to be inserted into the RBTree
		* 
		* @returns Inserted Node for fixing and balancing the tree.
		*/
		FORCEINLINE constexpr TRBNode<T>* InsertHelper(TRBNode<T>* Current, const T& NewVal) noexcept
		{
			if (Current == Root)
			{
				// If Tree is empty insert at root.
				if (Root == nullptr)
				{
					Root = TRBNode<T>::MakeNewNode(NewVal);
					return Root;
				}
			}

			if (NewVal == Current->Value)
			{
				// Dont insert value
				return nullptr;
			}
			else if (Pred(NewVal, Current->Value))
			{
				// Look to the Left
				if (Current->Left == nullptr || Current->Left->bIsNil)
				{
					Current->Left = TRBNode<T>::MakeNewNode(NewVal, nullptr, nullptr, Current);
					return Current->Left;
				}
				else
				{
					return InsertHelper(Current->Left, NewVal);
				}
			}
			else if (Pred(Current->Value, NewVal))
			{
				// Look to the Right
				if (Current->Right == nullptr || Current->Right->bIsNil)
				{
					Current->Right = TRBNode<T>::MakeNewNode(NewVal, nullptr, nullptr, Current);
					return Current->Right;
				}
				else
				{
					return InsertHelper(Current->Right, NewVal);
				}
			}
			return nullptr;
		}

		/*
		* Insert Helper that Inserts a node into the Red Black Tree recursively
		*
		* @param Current - Currently looked at node to perform insertion
		* @param NewVal - R Value Ref to the Value to be inserted into the RBTree
		*/
		FORCEINLINE constexpr TRBNode<T>* InsertHelper(TRBNode<T>* Current, T&& NewVal) noexcept
		{
			if (Current == Root)
			{
				// If Tree is empty insert at root.
				if (Root == nullptr)
				{
					Root = TRBNode<T>::MakeNewNode(Move(NewVal));
					return Root;
				}
			}

			if (NewVal == Current->Value)
			{
				// Dont insert value
				return nullptr;
			}
			else if (Pred(NewVal, Current->Value))
			{
				// Look to the Left
				if (Current->Left == nullptr || Current->Left->bIsNil)
				{
					Current->Left = TRBNode<T>::MakeNewNode(Move(NewVal), nullptr, nullptr, Current);
					return Current->Left;
				}
				else
				{
					return InsertHelper(Current->Left, Move(NewVal));
				}
			}
			else if (Pred(Current->Value, NewVal))
			{
				// Look to the Right
				if (Current->Right == nullptr || Current->Right->bIsNil)
				{
					Current->Right = TRBNode<T>::MakeNewNode(Move(NewVal), nullptr, nullptr, Current);
					return Current->Right;
				}
				else
				{
					return InsertHelper(Current->Right, Move(NewVal));
				}
			}
			return nullptr;
		}

		/*
		* Function that fixes insertions by rotations and recoloring
		* Cases for Insertion Fixes
		* - If Parent is Red
		*	1) Z is root						=> Color Z Black
		*	2) Z's Uncle is Red					=> Recolor Z's Parent = Black, GrandParent = Red, Uncle = Black
		*	3) Z's Uncle is Black (Triangle)	=> Rotate Z's GrandParent.	(Z's Parent = Left then Right Rotate and vice-versa)
		*	4) Z's Uncle is Black (Line)		=> Rotate Z's GrandParent and recolor Parent = Black and GrandParent = Red.	(Z's Parent = Left then Right Rotate and vice-versa)
		* 
		* @param NodeToFix - The Node whose position needs to be fixed
		*/
		FORCEINLINE constexpr void FixInsertions(TRBNode<T>* NodeToFix) noexcept
		{
			constexpr bool Black = true;
			constexpr bool Red = false;

			while (NodeToFix->Parent && NodeToFix->Parent->bIsBlack == Red)
			{
				if (NodeToFix->Parent->Parent != nullptr)
				{
					if (NodeToFix->Parent == NodeToFix->Parent->Parent->Left)
					{
						// Node's Parent is Left Child
						if (NodeToFix->Parent->Parent->Right->bIsBlack == Red)
						{
							// Uncle is Red
							NodeToFix->Parent->bIsBlack = Black;
							NodeToFix->Parent->Parent->Right->bIsBlack = Black;
							NodeToFix->Parent->Parent->bIsBlack = Red;
							NodeToFix = NodeToFix->Parent->Parent;
						}
						else
						{
							// Uncle is Black or Nil
							if (NodeToFix->Parent->Right == NodeToFix)
							{
								// Triangle
								NodeToFix = NodeToFix->Parent;
								RotateLeft(NodeToFix);
							}
							// On Left Rotation will form a Line
							NodeToFix->Parent->bIsBlack = Black;
							NodeToFix->Parent->Parent->bIsBlack = Red;
							RotateRight(NodeToFix->Parent->Parent);
						}
					}
					else if (NodeToFix->Parent == NodeToFix->Parent->Parent->Right)
					{
						// Node's Parent is Right Child
						if (NodeToFix->Parent->Parent->Left->bIsBlack == Red)
						{
							// Uncle is Red
							NodeToFix->Parent->bIsBlack = Black;
							NodeToFix->Parent->Parent->Left->bIsBlack = Black;
							NodeToFix->Parent->Parent->bIsBlack = Red;
							NodeToFix = NodeToFix->Parent->Parent;
						}
						else
						{
							// Uncle is Black or Nil
							if (NodeToFix->Parent->Left == NodeToFix)
							{
								// Triangle
								NodeToFix = NodeToFix->Parent;
								RotateRight(NodeToFix);
							}
							// On Right Rotation will form a Line
							NodeToFix->Parent->bIsBlack = Black;
							NodeToFix->Parent->Parent->bIsBlack = Red;
							RotateLeft(NodeToFix->Parent->Parent);
						}
					}
				}
				if (NodeToFix == Root)
				{
					break;
				}
			}
			/*while (Root->Parent != nullptr)
			{
				Root = Root->Parent;
			}*/
			Root->bIsBlack = Black;
		}

		/*
		* Function to Rotate Left on the Node.
		* Adjusts the pointers on Node and nearby Nodes to perform a Rotate Left 
		* 
		* @param Node - Node on which the rotation happens
		*/
		FORCEINLINE constexpr void RotateLeft(TRBNode<T>* Node) noexcept
		{
			if (Node == nullptr)
			{
				return;
			}
			if (Node == Root)
			{
				if (Node->Right != nullptr)
				{
					Root = Node->Right;
					TRBNode<T>* NodeRL = Node->Right->Left;
					Node->Right->Parent = nullptr;

					Node->Right->Left = Node;
					Node->Parent = Node->Right;
					Node->Right = NodeRL;
					if (NodeRL != nullptr && !NodeRL->bIsNil)
					{
						NodeRL->Parent = Node;
					}
					Root = Node->Parent;
					Root->Left = Node;
					Root->Right = Node->Parent->Right;
				}
			}
			else
			{
				if (Node->Right != nullptr)
				{
					TRBNode<T>* NodeRL = Node->Right->Left;
					Node->Right->Parent = Node->Parent;
					if (Node->Parent->Right == Node)
					{
						Node->Parent->Right = Node->Right;
					}
					else if (Node->Parent->Left == Node)
					{
						Node->Parent->Left = Node->Right;
					}
					Node->Right->Left = Node;
					Node->Parent = Node->Right;
					Node->Right = NodeRL;
					if (NodeRL != nullptr && !NodeRL->bIsNil)
					{
						NodeRL->Parent = Node;
					}
				}
			}
		}

		/*
		* Function to Rotate Right on the Node.
		* Adjusts the pointers on Node and nearby Nodes to perform a Rotate Right
		*
		* @param Node - Node on which the rotation happens
		*/
		FORCEINLINE constexpr void RotateRight(TRBNode<T>* Node) noexcept
		{
			if (Node == nullptr)
			{
				return;
			}
			if (Node == Root)
			{
				if (Node->Left != nullptr)
				{
					TRBNode<T>* NodeRL = Node->Left->Right;
					Node->Left->Parent = nullptr;

					Node->Left->Right = Node;
					Node->Parent = Node->Left;
					Node->Left = NodeRL;
					if (NodeRL != nullptr && !NodeRL->bIsNil)
					{
						NodeRL->Parent = Node;
					}
					Root = Node->Parent;
					Root->Right = Node;
					Root->Left = Node->Parent->Left;
				}
			}
			else
			{
				if (Node->Left != nullptr)
				{
					TRBNode<T>* NodeRL = Node->Left->Right;
					Node->Left->Parent = Node->Parent;
					if (Node->Parent->Right == Node)
					{
						Node->Parent->Right = Node->Left;
					}
					else if (Node->Parent->Left == Node)
					{
						Node->Parent->Left = Node->Left;
					}
					Node->Left->Right = Node;
					Node->Parent = Node->Left;
					Node->Left = NodeRL;
					if (NodeRL != nullptr && !NodeRL->bIsNil)
					{
						NodeRL->Parent = Node;
					}
				}
			}
		}

		/*
		* Remove Helper that Removes a node from the Red Black Tree recursively
		*
		* @param Current - Currently looked at node to perform deletion
		* @param NewVal - const L Value Ref to the Value to be removed from the RBTree
		*
		* @returns true if Node with NewVal has been removed, false if Node doesn't exist and hasn't been removed
		*/
		FORCEINLINE constexpr bool RemoveHelper(TRBNode<T>* Current, const T& NewVal) noexcept
		{
			if (Current == nullptr)
			{
				return false;
			}
			else
			{
				if (NewVal == Current->Value)
				{
					if (Current == Nil)
					{
						return false;
					}
					if (Current->Left->bIsNil && Current->Right->bIsNil)
					{
						if (Current == Root)
						{
							Root = nullptr;
						}
						else
						{
							if (Current->Parent->Left == Current)
							{
								Current->Parent->Left = Nil;
							}
							else
							{
								Current->Parent->Right = Nil;
							}
							RemoveRecolor(Current, Nil);
						}
					}
					else if (Current->Left->bIsNil && !Current->Right->bIsNil)
					{
						if (Current == Root)
						{
							Root = Current->Right;
							Current->Right->Parent = nullptr;
						}
						else
						{
							if (Current->Parent->Left == Current)
							{
								Current->Parent->Left = Current->Right;
							}
							else
							{
								Current->Parent->Right = Current->Right;
							}
							Current->Right->Parent = Current->Parent;
							RemoveRecolor(Current, Current->Right);
						}
					}
					else if (!Current->Left->bIsNil && Current->Right->bIsNil)
					{
						if (Current == Root)
						{
							Root = Current->Left;
							Current->Left->Parent = nullptr;
						}
						else
						{
							if (Current->Parent->Left = Current)
							{
								Current->Parent->Left = Current->Left;
							}
							else
							{
								Current->Parent->Right = Current->Left;
							}
							Current->Left->Parent = Current->Parent;
							RemoveRecolor(Current, Current->Left);
						}
					}
					else
					{
						TRBNode<T>* MinNodeInRightSubTree = FindMinInSubTree(Current->Right);
						TRBNode<T>* FixUpNode = MinNodeInRightSubTree->Right; // X
						TRBNode<T>* FixUpParent;
						
						// If successor's parent is Current, then Successor is Current->Right
						if (MinNodeInRightSubTree->Parent == Current)
						{
							FixUpParent = MinNodeInRightSubTree;
							// If FixUp node is Nil, then set Parent's Right to Nil, otherwise properly replace
							// This is because, we have only one Nil reference we use for every leaf node.
							if (FixUpNode->bIsNil)
							{
								MinNodeInRightSubTree->Parent->Right = Nil;
							}
							else
							{
								FixUpNode->Parent = MinNodeInRightSubTree->Parent;
								FixUpNode->Parent->Right = FixUpNode;
							}
						}
						// If successor's parent is not Current, then Successor->Left is Nil and Successor is a Left Child.
						else
						{
							FixUpParent = MinNodeInRightSubTree->Parent;
							// If FixUp node is Nil, then set Parent's Left to Nil, otherwise properly replace
							// This is because, we have only one Nil reference we use for every leaf node.
							if (FixUpNode->bIsNil)
							{
								MinNodeInRightSubTree->Parent->Left = Nil;
							}
							else
							{
								FixUpNode->Parent = MinNodeInRightSubTree->Parent;
								FixUpNode->Parent->Left = FixUpNode;
							}
						}

						// Replace Current with Replacement
						if (Current->Parent != nullptr)
						{
							if (Current = Current->Parent->Right)
							{
								Current->Parent->Right = MinNodeInRightSubTree;
							}
							else
							{
								Current->Parent->Left = MinNodeInRightSubTree;
							}
						}
						else
						{
							Root = MinNodeInRightSubTree;
						}
						MinNodeInRightSubTree->Parent = Current->Parent;
						MinNodeInRightSubTree->Left = Current->Left;
						MinNodeInRightSubTree->Left->Parent = MinNodeInRightSubTree;
						MinNodeInRightSubTree->Right = Current->Right;
						MinNodeInRightSubTree->Right->Parent = MinNodeInRightSubTree;

						RemoveRecolor(Current, MinNodeInRightSubTree, FixUpNode, FixUpParent);
					}
					delete Current;
					Current = nullptr;
					// Make sure Root is not Nil.
					// If it is, then set it to nullptr, If not, color it black.
					if (Root != nullptr)
					{
						if (Root->bIsNil)
						{
							Root = nullptr;
						}
						else
						{
							Root->bIsBlack = true;
						}
					}
					return true;
				}
				else if (Pred(NewVal, Current->Value))
				{
					// Look to the Left
					if (Current->Left != nullptr && !Current->Left->bIsNil)
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
					if (Current->Right != nullptr && !Current->Right->bIsNil)
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

		FORCEINLINE constexpr void RemoveRecolor(TRBNode<T>* RemovedNode, TRBNode<T>* ReplacementNode, TRBNode<T>* HelperX = nullptr, TRBNode<T>* FixUpParent = nullptr) noexcept
		{
			if (!RemovedNode->bIsBlack)
			{
				if (!ReplacementNode->bIsBlack || ReplacementNode->bIsNil)
				{
					return;
				}
				else
				{
					// Color replacement Red
					ReplacementNode->bIsBlack = false;
				}
			}
			else
			{
				if (!ReplacementNode->bIsBlack)
				{
					// Color replacement Black
					ReplacementNode->bIsBlack = true;
					return;
				}
				else
				{
					if (Root == HelperX)
					{
						return;
					}
				}
			}
			if (HelperX == nullptr)
			{
				if (ReplacementNode->bIsNil)
				{
					RemoveFixUp(ReplacementNode, RemovedNode->Parent);
				}
				else
				{
					RemoveFixUp(ReplacementNode, ReplacementNode->Parent);
				}
			}
			else
			{
				RemoveFixUp(HelperX, FixUpParent);
			}
		}

		FORCEINLINE constexpr void RemoveFixUp(TRBNode<T>* FixUpNode, TRBNode<T>* ParentIfFixUpIsNil) noexcept
		{
			constexpr bool BLACK = true;
			constexpr bool RED = false;

			// CASE 0
			// If FixUp is Red, Color it black and return.
			if (!FixUpNode->bIsBlack)
			{
				FixUpNode->bIsBlack = true;
				return;
			}

			while (FixUpNode != Root && FixUpNode->bIsBlack)
			{
				// If FixUp is Black and Not the Root.
				
				// As Our Nil node's parents are not connected, so we need to make sure we we pass in the Right Parent.
				// Set FixUpParent to the appropriate Parent.
				// Nil ->		ParentIfFixUpIsNil
				// Not-Nit ->	FixUpNode->Parent
				TRBNode<T>* FixUpParent = nullptr;
				if (FixUpNode->bIsNil)
				{
					FixUpParent = ParentIfFixUpIsNil;
				}
				else
				{
					FixUpParent = FixUpNode->Parent;
				}

				// If FixUp is the Left Child - The Rotations and Assignments Vary
				if (FixUpNode == FixUpParent->Left)
				{
					// FixUp is left child
					// Sibling becomes the Right Child.
					TRBNode<T>* FixUpSibling = FixUpParent->Right;

					// CASE 1
					if (!FixUpSibling->bIsBlack)
					{
						// If Sibling is Red
						// Color Sibling Black and Parent Red.
						FixUpSibling->bIsBlack = true;
						FixUpParent->bIsBlack = false;

						/*
						* Fix Up = X
						* Parent = P
						* Sibling = W
						* Sibling Left = WL
						* Sibling Right = WR
						* 
						*                P(B->R)
						*              /  \
						*             X(B) W(R->B) It was Red before, => Children are Black
						*                 / \
						*             (B)WL WR(B)
						* /\/\/\/\/\/\/\
						* BEFORE ROTATION
						*/
						RotateLeft(FixUpParent);
						/*
						* AFTER ROTATION
						* \/\/\/\/\/\/\/
						*                   W(R->B) It was Red before, => Children are Black
						*                  /   \
						*             P(B->R)   WR(B)
						*              /   \
						*           X(B)  (B)WL
						* 
						* 1) After Rotation, W/Sibling will always be Black
						* 2) New W cannot be Nil, as If it is Nil, This initial RB Tree property of Red-Black height won't hold.
						*/

						FixUpSibling = FixUpParent->Right;
					}

					// CASE 2
					// If Our Sibling has 2 Black child nodes
					if (FixUpSibling->Right->bIsBlack && FixUpSibling->Left->bIsBlack)
					{
						// Set Sibling Color to Red and FixUp to its Parent 
						FixUpSibling->bIsBlack = false;
						FixUpNode = FixUpParent;

						if (!FixUpNode->bIsBlack)
						{
							// If FixUp is Red
							// then color it Black and Return
							FixUpNode->bIsBlack = true;
							return;
						}
						else
						{
							// If FixUp is Black
							// and Root
							if (FixUpNode == Root)
							{
								return;
							}
						}
						// If Black and non-root
						// Adjust FixupParent, and Sibling
						FixUpParent = FixUpParent->Parent;
						FixUpSibling = FixUpParent->Right;
						continue;
					}

					// CASE 3
					// If Our Sibling Left = Red, Right = Black
					if (FixUpSibling->Right->bIsBlack && !FixUpSibling->Left->bIsBlack)
					{
						FixUpSibling->Left->bIsBlack = true;
						FixUpSibling->bIsBlack = false;

						/*
						* Fix Up = X
						* Parent = P
						* Sibling = W
						* Sibling Left = WL
						* Sibling Right = WR
						*
						*                P(B)
						*              /  \
						*             X(B) W(B->R)
						*                 / \
						*          (R->B)WL WR(B)
						* /\/\/\/\/\/\/\
						* BEFORE ROTATION
						*/
						RotateRight(FixUpSibling);
						/*
						* AFTER ROTATION
						* \/\/\/\/\/\/\/
						*                P(B)
						*              /  \
						*             X(B) WL(R->B)
						*                   \
						*                   W(B->R)
						*                    \
						*                    WR(B)
						*
						*/

						// Will be equal to Sibling's Previous Left
						FixUpSibling = FixUpParent->Right;
					}

					// After case 3, Sibling Right will always be Red.
					// CASE 4
					if (!FixUpSibling->Right->bIsBlack)
					{
						FixUpSibling->bIsBlack = FixUpParent->bIsBlack;
						FixUpParent->bIsBlack = true;
						FixUpSibling->Right->bIsBlack = true;

						/*
						* Fix Up = X
						* Parent = P
						* Sibling = W
						* Sibling Left = WL
						* Sibling Right = WR
						* 
						*                P(B)
						*              /  \
						*             X(B) W(R->B)
						*                   \
						*                   WR(B->R)
						* /\/\/\/\/\/\/\
						* BEFORE ROTATION
						*/
						RotateLeft(FixUpParent);
						return;
					}
				}
				// If FixUp is the Right Child - The Rotations and Assignments Vary
				else
				{
					// X is Right Child
					TRBNode<T>* FixUpSibling = FixUpParent->Left;

					// CASE 1
					if (!FixUpSibling->bIsBlack)
					{
						// If Sibling is Red
						// Color Sibling Black and Parent Red.
						FixUpSibling->bIsBlack = true;
						FixUpParent->bIsBlack = false;

						// Refer to Mirrored Rotations Above
						RotateLeft(FixUpParent);

						// Reset Sibling
						FixUpSibling = FixUpParent->Left;
					}

					// CASE 2
					// If Our Sibling has 2 Black child nodes
					if (FixUpSibling->Right->bIsBlack && FixUpSibling->Left->bIsBlack)
					{
						// Set Sibling Color to Red and FixUp to its Parent 
						FixUpSibling->bIsBlack = false;
						FixUpNode = FixUpParent;

						if (!FixUpNode->bIsBlack)
						{
							// If FixUp is Red
							// then color it Black and Return
							FixUpNode->bIsBlack = true;
							return;
						}
						else
						{
							// If FixUp is Black
							// and Root
							if (FixUpNode == Root)
							{
								return;
							}
						}
						// If Black and non-root
						// Adjust FixupParent, and Sibling
						FixUpParent = FixUpParent->Parent;
						FixUpSibling = FixUpParent->Right;
						continue;
					}

					// CASE 3
					// If Our Sibling Right = Red, Left = Black
					if (!FixUpSibling->Right->bIsBlack && FixUpSibling->Left->bIsBlack)
					{
						FixUpSibling->Right->bIsBlack = true;
						FixUpSibling->bIsBlack = false;

						// Refer to Mirrored Rotations Above
						RotateLeft(FixUpSibling);

						// Will be equal to Sibling's Previous Right
						FixUpSibling = FixUpParent->Left;
					}

					// After case 3, Sibling Right will always be Red.
					// CASE 4
					if (!FixUpSibling->Left->bIsBlack)
					{
						FixUpSibling->bIsBlack = FixUpParent->bIsBlack;
						FixUpParent->bIsBlack = true;
						FixUpSibling->Left->bIsBlack = true;

						// Refer to Mirrored Rotations Above
						RotateRight(FixUpParent);
						return;
					}
				}
			}
		}

		/*
		* Search Helper that Searches a node from the Red Black Tree recursively
		*
		* @param Current - Currently looked at node to perform deletion
		* @param NewVal - const L Value Ref to the Value to be searched for in the RBTree
		*
		* @returns true if Node with NewVal exists, false otherwise
		*/
		FORCEINLINE constexpr bool SearchHelper(TRBNode<T>* Current, const T& NewVal) noexcept
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

		FORCEINLINE constexpr void ReconnectParent(TRBNode<T>* Current, TRBNode<T>* NewConnection) noexcept
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
		FORCEINLINE constexpr TRBNode<T>* FindMinInSubTree(TRBNode<T>* SubTreeRoot) noexcept
		{
			if (SubTreeRoot == nullptr)
			{
				return nullptr;
			}

			if (SubTreeRoot->Left == nullptr || SubTreeRoot->Left->bIsNil)
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
		FORCEINLINE constexpr TRBNode<T>* FindMaxInSubTree(TRBNode<T>* SubTreeRoot) noexcept
		{
			if (SubTreeRoot == nullptr)
			{
				return nullptr;
			}

			if (SubTreeRoot->Right == nullptr || SubTreeRoot->Right->bIsNil)
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
		* Helper that frees memory form the Red Black Tree recursively
		*
		* @param Current - Currently looked at node to perform freeing on the Node and it's subtree
		*/
		FORCEINLINE constexpr void FreeRBTreeHelper(TRBNode<T>* Current) noexcept
		{
			if (Current == nullptr || Current->bIsNil)
			{
				return;
			}
			if (Current->Left != nullptr && !Current->Left->bIsNil)
			{
				FreeRBTreeHelper(Current->Left);
				Current->Left = nullptr;
			}

			if (Current->Right != nullptr && !Current->Right->bIsNil)
			{
				FreeRBTreeHelper(Current->Right);
				Current->Right = nullptr;
			}

			delete Current;
		}

		/*
		* BELOW = HELPER FUNCTIONS FOR TESTING. SHOULD NOT BE USED
		* \/\/\/
		*/
		template<typename FuncType = void()>
		FORCEINLINE constexpr void InOrderPrintHelper(TRBNode<T>* Current, const std::string& AppendString = "")
		{
			if (Current == nullptr || Current->bIsNil)
			{
				return;
			}
			if (!AppendString.empty())
			{
				InOrderPrintHelper(Current->Left, AppendString + "L");
				std::cout << "[CORE] " << Current->Value << " " << (Current->bIsBlack ? "Black" : "Red") << " " << AppendString << "\n";
				InOrderPrintHelper(Current->Right, AppendString + "R");
			}
			else
			{
				InOrderPrintHelper(Current->Left, AppendString);
				std::cout << "[CORE] " << Current->Value << " " << (Current->bIsBlack ? "Black" : "Red") << "\n";
				InOrderPrintHelper(Current->Right, AppendString);
			}
		}

		template<typename FuncType = void()>
		FORCEINLINE constexpr void PreOrderPrintHelper(TRBNode<T>* Current, const std::string& AppendString = "")
		{
			if (Current == nullptr || Current->bIsNil)
			{
				return;
			}
			if (!AppendString.empty())
			{
				std::cout << "[CORE] " << Current->Value << " " << (Current->bIsBlack ? "Black" : "Red") << " " << AppendString << "\n";
				PreOrderPrintHelper(Current->Left, AppendString + "L");
				PreOrderPrintHelper(Current->Right, AppendString + "R");
			}
			else
			{
				std::cout << "[CORE] " << Current->Value << " " << (Current->bIsBlack ? "Black" : "Red") << "\n";
				PreOrderPrintHelper(Current->Left, AppendString);
				PreOrderPrintHelper(Current->Right, AppendString);
			}
		}

		// Accepts function pointers so that the Helper can run a function for the PreOrder
		template<typename FuncType = void()>
		FORCEINLINE constexpr void PostOrderPrintHelper(TRBNode<T>* Current, const std::string& AppendString = "")
		{
			if (Current == nullptr || Current->bIsNil)
			{
				return;
			}

			if (!AppendString.empty())
			{
				PostOrderPrintHelper(Current->Left, AppendString + "L");
				PostOrderPrintHelper(Current->Right, AppendString + "R");
				std::cout << "[CORE] " << Current->Value << " " << (Current->bIsBlack ? "Black" : "Red") << " " << AppendString << "\n";
			}
			else
			{
				PostOrderPrintHelper(Current->Left, AppendString);
				PostOrderPrintHelper(Current->Right, AppendString);
				std::cout << "[CORE] " << Current->Value << " " << (Current->bIsBlack ? "Black" : "Red") << "\n";
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
		TRBNode<T>* Root{ nullptr };
		/*
		* Nil Node for the Tree
		*/
		TRBNode<T>* Nil{ nullptr };
		/*
		* Predicate function used to compare values
		*/
		Predicate Pred;

	private:


	public:
		// Const and Non-Const Iterators
		using Iterator = TRedBlackIterator<TRBNode<T>>;
		using ConstIterator = TRedBlackIterator<const TRBNode<T>>;

		// Functions for Tree Iteration
		FORCEINLINE Iterator begin()
		{
			if (Root == nullptr)
			{
				return Iterator(nullptr);
			}
			TRBNode<T>* Temp = Root;
			while (Temp->Left != nullptr && !Temp->Left->bIsNil)
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
			TRBNode<T>* Temp = Root;
			while (Temp->Left != nullptr && !Temp->Left->bIsNil)
			{
				Temp = Temp->Left;
			}
			return ConstIterator(*Temp);
		}
		FORCEINLINE Iterator			end() { return Iterator(nullptr); }
		FORCEINLINE ConstIterator		end() const { return ConstIterator(nullptr); }
	};
}