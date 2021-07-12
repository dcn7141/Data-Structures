#pragma once

// Only compile if LAB_2 is on
#if LAB_2

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

// Checks to see if a number is a palindrome (reads the same forwards and backwards)
//		An example of a palindrome word would be "racecar"
//
// In: _num			The number to check
//
// Return: True, if the number is a palindrome number
inline bool IsPalindromeNumber(unsigned int _num) 
{
	int rev = 0;
	int	remainder;
	int	temp;

	temp = _num;

	while (temp != 0)
	{
		remainder = temp % 10;
		rev = rev * 10 + remainder;
		temp = temp / 10;
	}

	if (_num == rev)
		return true;
	else
		return false;
}


class DSA_Lab2
{
	friend class TestSuite;	// Giving access to test code


private:

	vector<unsigned int> mValues;		// contains all of the values
	vector<unsigned int> mPalindromes;	// contains just the numbers that are palindromes

public:

	// Fill out the vector with the contents of the binary file
	//		First four bytes of the file are the number of ints in the file
	//
	// In:	_input		Name of the file to open
	//
	// Note: Make sure the vector is empty and shrunk to 0 capacity before adding values
	void Fill(const char* _input) {

		std::ifstream binaryFile(_input, std::ios::binary);
		Clear();

		int count;
		binaryFile.read((char*)&count, sizeof(int));
		int temp;
		while (true)
		{
			binaryFile.read((char*)&temp, sizeof(int));

			if (!binaryFile) {
				break;
			}

			mValues.push_back(temp);
		}
		binaryFile.close();
	}

	// Fill out the vector with the contents of an array
	//
	// In:	_arr			The array of values
	//		_size			The number of elements in the array
	//
	// Note: Make sure the vector is empty and shrunk to 0 capacity before adding values
	void Fill(const unsigned int* _arr, int _size) 
	{
		Clear();

		for (int i = 0; i < _size; i++)
		{
			_arr[i];
			mValues.push_back(_arr[i]);
		}
	}

	// Remove all elements from vector and decrease capacity to 0
	void Clear() 
	{
		mValues.clear();
		mValues.shrink_to_fit();
	}

	// Sort the vector 
	//
	// In:	_ascending		To sort in ascending order or not
	void Sort(bool _ascending)
	{
		if (_ascending)
		{
			std::sort(mValues.begin(), mValues.end());
		}
		else
		{
			std::sort(mValues.begin(), mValues.end(), std::greater<>());
		}
	}

	// Get an individual element from the mValues vector
	int operator[](int _index)
	{
		return mValues[_index];
	}

	// Determine if a value is present in the vector
	// 
	// In:	_val		The value to check for
	//
	// Return: True, if the value is present
	bool Contains(unsigned int _val) const
	{
		if (std::find(mValues.begin(), mValues.end(), _val) != mValues.end())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// Move all palindrome numbers from mValues vector to mPalindromes vector
	//
	// Pseudocode:
	//		iterate through the main values vector
	//			if the value is a palindrome
	//				add it to the palindrome vector
	//				remove it from the values vector
	void MovePalindromes() 
{
	
	}
};




#endif