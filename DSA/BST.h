// BST.h - A binary search tree
#pragma once

// For InOrder method
#include "string.h"
using namespace std;


#if LAB_8
template<typename Type>
class BST {

	friend class TestSuite; // Giving access to test code

	struct Node {
		Type data;
		Node* left, * right;

		// Constructor
		//		Creates a leaf node
		//
		// In:	_data		The value to store in this node
		Node(const Type& _data) 
		{
			data = _data;
			left = nullptr;
			right = nullptr;
		}
	};

	// Data members
	Node* mRoot;

public:

	// Default constructor
	//			Creates an empty tree
	BST() {
		mRoot = nullptr;
	}

	// Destructor
	//			Clear all dynamic memory
	~BST() {
		Clear();
	}

	// Copy constructor
	//			Used to initialize one object to another
	//
	// In:	_copy		The object to copy from
	BST(const BST<Type>& _copy) {
		*this = _copy;
	}


	// Assignment operator
	//			Used to assign one object to another
	//
	// In:	_assign		The object to assign from
	//
	// Return:	The invoking object (by reference)
	//		This allows us to daisy-chain
	BST<Type>& operator=(const BST<Type>& _assign)
	{

		if (this != &_assign)
		{
			Clear();
			Copy(_assign.mRoot);
		}
		return *this;
	}

private:

	// Optional recursive helper method for use with Rule of 3
	// 
	// In:	_curr		The current Node to copy
	//
	// NOTE:	Use pre-order traversal
	void Copy(const Node* _curr)
	{
		if (_curr != nullptr)
		{
			Push(_curr->data);
			Copy(_curr->left);
			Copy(_curr->right);
		}
	}

public:

	// Clears out the tree and readies it for re-use
	void Clear() {

		Clear(mRoot);
		mRoot = nullptr;
	}

private:

	// Optional recursive helper method for use with Clear
	// 
	// In:	_curr		The current Node to clear
	//
	// NOTE:	Use post-order traversal
	void Clear(Node* _curr) 
	{
		if (_curr != nullptr)
		{
			Clear(_curr->left);
			Clear(_curr->right);
			delete _curr;
		}
	}

public:

	// Add a value into the tree
	//
	// In:	_val			The value to add
	void Push(const Type& _val)
	{
		if (mRoot == nullptr)
		{
			mRoot = new Node(_val);
			return;
		}

		Node* temp = mRoot;

		while (temp != nullptr)
		{
			if (_val < temp->data && temp->left == nullptr) 
			{
				temp->left = new Node(_val);
				break;
			}
			else if(_val < temp->data&& temp->left != nullptr)
			{
				temp = temp->left;
			}

			else if (_val >= temp->data && temp->right == nullptr)
			{
				temp->right = new Node(_val);
			    break;
			}
			else if (_val >= temp->data && temp->right != nullptr)
			{
				temp = temp->right;
			}
		}	
		temp = nullptr;
		delete temp;
	}

private:

	// Optional recursive helper method for use with Push
	//
	// In:	_val		The value to add
	//		_curr		The current Node being looked at
	void Push(const Type& _val, Node* _curr) 
	{
	
	}

public:


	// Checks to see if a value is in the tree
	//
	// In:	_val		The value to search for
	//
	// Return:	True, if found
	bool Contains(const Type& _val) 
	{
		Node* temp = mRoot;

		while (temp != nullptr)
		{
			if (_val < temp->data)
			{
				temp = temp->left;
			}
			else if (_val > temp->data)
			{
				temp = temp->right;
			}
			else
			{
				return true;
			}
		}
		return false;
	}

	// Removes a value from tree (first instance only)
	//
	// In:	_val			The value to search for
	//
	// Return:	True, if a Node was removed
	// NOTE:	Keep in mind the three cases
	//			A) 2 children ("fix" tree)
	//			B) 0 children
	//			C) 1 child

	bool Remove(const Type& _val)
	{
		if (mRoot == nullptr)
		{
			return false;
		}

		Node* parent = nullptr;
		Node* temp = mRoot;

		while (temp)
		{
			if (_val < temp->data)
			{
				parent = temp;
				temp = temp->left;
			}
			else if (_val > temp->data)
			{
				parent = temp;
				temp = temp->right;
			}
			else
			{
				break;
			}
		}

		if (temp == nullptr)
		{
			return false;
		}
		
		// Case 2
		if (temp->left && temp->right) 
		{
			Node* temp2 = temp->right;
			while (temp2->left)
			{
				parent = temp2;
				temp2 = temp2->left;
			}
			temp->data = temp2->data;
			temp = temp2;
		}
		// Case 0
		if (temp->left == nullptr && temp->right == nullptr) 
		{
			if (temp != mRoot) 
			{
				if (parent->left == temp) 
				{
					parent->left = nullptr;
				}
				else 
				{
					parent->right = nullptr;
				}
			}
			else 
			{
				mRoot = nullptr;
			}
		}
		// Case 1
		else if (!(temp->left == nullptr && temp->right == nullptr)) 
		{
			if (parent) 
			{
				if (parent->left == temp) 
				{
					if (temp->left)
					{
						parent->left = temp->left;
					}
					else
					{
						parent->left = temp->right;
					}
				}
				else 
				{
					if (temp->left)
					{
						parent->right = temp->left;
					}
					else
					{
						parent->right = temp->right;
					}
				}
			}
			else 
			{
				if (mRoot->left != nullptr) 
				{
					mRoot = mRoot->left;
				}
				else 
				{
					mRoot = mRoot->right;
				}
			}
		}

		delete temp;
		return true;
	}


	// Returns a space-delimited string of the tree in order
	/*
	 Example:
			 24
			/ \
		   10  48
			\   \
			12   50

	 Should return: "10 12 24 48 50"
	*/
	// NOTE:	Use to_string to convert an int to its string equivelent

	string InOrder() 
	{
		string temp;
		InOrder(mRoot,temp);
		temp.pop_back();
		return temp;
	}

private:

	// Optional recursive helper method to help with InOrder
	//
	// In:	_curr		The current Node being looked at
	//		_str		The string to add to
	//
	// NOTE:	Use in-order traversal
	void InOrder(Node* _curr, string& _str)
	{
		if (_curr == nullptr)
		{
			return;
		}

		if (_curr != nullptr)
		{
			InOrder(_curr->left, _str);	
			_str += to_string(_curr->data);
			_str = _str + ' ';
			InOrder(_curr->right, _str);
		}
	}
};
#endif