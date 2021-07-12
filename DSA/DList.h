// DList.h - A doubly-linked list
// (similar to the stl list)

#pragma once


template<typename Type>
class DList {

	friend class TestSuite; // Giving access to test code

	// Node structor a doubly linked list
	struct Node {

		// Data members
		Type data;				// The value being stored
		Node* next, * prev;		// Pointers to the next and previous nodes

		// Constructor
		//
		// In:	_data			The value to store
		//		_next			Pointer to the next node in the list
		//		_prev			Pointer to the previous node in the list
		Node(const Type& _data, Node* _next = nullptr, Node* _prev = nullptr) 
		{
			data = _data;
			next = _next;
			prev = _prev;
		}
	};

public:

	// An iterator class to made traversal more efficient
	class Iterator {
	public:

		// Data members
		Node* mCurr;

		// Pre-fix increment operator
		//
		// Example:
		//		I - Iterator's curr
		//		R - Return
		/*
			Before

			0<-[4]<->[5]<->[6]->0
					  I

			After

			0<-[4]<->[5]<->[6]->0
							I
							R
		*/
		// Return:	The Iterator (the invoking object)
		Iterator& operator++() {
			mCurr = mCurr->next;
			return *this;
		}

		// Post-fix increment operator
		//
		// Example:
		//		I - Iterator's curr
		//		R - Return
		/*
			Before

			0<-[4]<->[5]<->[6]->0
					  I

			After

			0<-[4]<->[5]<->[6]->0
					  R		I

		*/
		// Return:	The Iterator (before increment)
		// NOTE:	Will need a temporary pointer
		Iterator operator++(int) {
			mCurr = mCurr->next;

			Iterator iter;
			iter.mCurr = mCurr->prev;
			return iter;
		}

		// Pre-fix decrement operator
		//
		// Example:
		//		I - Iterator's curr
		//		R - Return
		/*
			Before

			0<-[4]<->[5]<->[6]->0
					  I

			After

			0<-[4]<->[5]<->[6]->0
				I
				R
		*/
		// Return:	The Iterator (the invoking object)
		Iterator& operator--() {
			mCurr = mCurr->prev;
			return *this;
		}

		// Post-fix decrement operator
		//
		// Example:
		//		I - Iterator's curr
		//		R - Return
		/*
			Before

			0<-[4]<->[5]<->[6]->0
					  I

			After

			0<-[4]<->[5]<->[6]->0
				I	  R

		*/
		// Return:	The Iterator (before decrement)
		// NOTE:	Will need a temporary pointer
		Iterator operator--(int) {
			mCurr = mCurr->prev;

			Iterator iter;
			iter.mCurr = mCurr->next;
			return iter;
		}

		// Gets the value the iterator is currently pointing to
		//
		// Return:	The data of the current iterator
		Type& operator*() {
			return mCurr->data;
		}
	};

	// Data members
	Node* mHead;			// The head (first node) of the list
	Node* mTail;			// The tail (last node) of the list
	unsigned int mSize;		// Current number of nodes being stored

public:

	// Default constructor
	//		Creates a new empty linked list
	DList() 
	{
		mHead = mTail = nullptr;
		mSize = 0;
	}

	// Destructor
	//		Cleans up all dynamically allocated memory
	~DList() 
	{
		Clear();
	}

	// Copy constructor
	//		Used to initialize one object to another
	//
	// In:	_copy			The object to copy from
	DList(const DList& _copy) 
	{
		//		*this = _copy;
	}

	// Assignment operator
	//		Used to assign one object to another
	//
	// In:	_assign			The object to assign from
	//
	// Return: The invoking object (by reference)
	//		This allows us to daisy-chain
	DList& operator=(const DList& _assign) 
	{
		//if (this != &_assign)
		//{
		//	mHead = nullptr;
		//	mTail = nullptr;

		//	mSize = _assign.mSize;

		//	Node* temp = new Node[mSize];
		//	temp = mHead;
		//	while (temp != nullptr)
		//	{
		//		AddTail();
		//	}
		//}
		//return *this;
	}

private:

	// Optional recursive helper method for use with Rule of 3
	//
	// In:	_curr		The current Node to copy
	void Copy(const Node* _curr) {

	}

public:
	// Add a piece of data to the front of the list
	//
	// In:	_data			The object to add to the list
	void AddHead(const Type& _data) 
	{
		Node* newNode = new Node(_data);

		newNode->next = mHead;

		if (mTail == nullptr)
		{
			mTail = mHead = newNode;
		}
		else
		{
			mHead->prev = newNode;
			mHead = newNode;
		}
		mSize++;
	}

	// Add a piece of data to the end of the list
	//
	// In:	_data			The object to add to the list
	void AddTail(const Type& _data) 
	{
		Node* newNode = new Node(_data);

		newNode->prev = mTail;

		if (mHead == nullptr)
		{
			mHead = mTail = newNode;
		}
		else
		{
			mTail->next = newNode;
			mTail = newNode;
		}
		mSize++;
	}

	// Clear the list of all dynamic memory
	//			Resets the list to its default state
	void Clear() 
	{
		mSize = 0;
		Node* temp = mHead;
		mHead = mTail = nullptr;
		while (temp)
		{
			Node* newNode = temp->next;
			delete temp;
			temp = newNode;
		}
	}

private:

	// Optional recursive helper method for use with Clear
	// 
	// In:	_curr		The current Node to clear
	void Clear(const Node* _curr) {

	}

public:

	// Insert a piece of data *before* the passed-in iterator
	//
	// In:	_iter		The iterator
	//		_data		The value to add
	//
	// Example:
	/*
		Before

			0<-[4]<->[5]<->[6]->0
					  I

		After

			0<-[4]<->[9]<->[5]<->[6]->0
					  I
	*/
	// Return:	The iterator
	// SPECIAL CASE:	Inserting at head or empty list
	// NOTE:	The iterator should now be pointing to the new node created
	Iterator Insert(Iterator& _iter, const Type& _data) {

	/*	Node* newNode = new Node(_data);

		newNode->next = _iter.mCurr;
		newNode->prev = _iter.mCurr->prev;

		_iter.mCurr->prev->next = newNode;
		_iter.mCurr = newNode;

		if (_iter.mCurr = nullptr)
		{
			mHead = newNode;
		}

		return _iter;*/
	}

	// Erase a Node from the list
	//
	// In:	_iter		The iterator
	//
	// Example
	/*

		Before

			0<-[4]<->[5]<->[6]->0
					  I

		After

			0<-[4]<->[6]->0
					  I
	*/
	// Return:	The iterator
	// SPECIAL CASE:	Erasing head or tail
	// NOTE:	The iterator should now be pointing at the node after the one erased
	Iterator Erase(Iterator& _iter) {

	}

	// Set an Iterator at the front of the list
	// 
	// Return: An iterator that is pointing to the list's head
	Iterator Begin() {
		Iterator iter;
		iter.mCurr = mHead;
		return iter;
	}

	// Set an Iterator pointing to the end of the list
	// 
	// Return: An iterator that is pointing to a null pointer
	Iterator End() {
		Iterator iter;
		iter.mCurr = mTail;
		return iter;
	}
};