#pragma once

#if LAB_6
#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;

class DSA_Lab6 {

	friend class TestSuite;	// Giving access to test code

	// Data members
	int mLetterValues[26];
	unordered_map<string, int> mScrabbleMap;

public:

	// In Scrabble, each letter has a value associated with it.
	// This method will populate the array of letter values.
	//
	// In:	_letterValues		The array of 26 values
	void PopulateLetterValues(const int* _letterValues) 
	{
		//passing in array of 26 vals
		//mlettervalues fil with value from array

		for (int i = 0; i < 26; i++)
		{
			mLetterValues[i] = _letterValues[i];
		}
	}

	// Retrieve the value of a particular letter
	// 
	// In:	_letter			The letter to get the score for
	//
	// Return:	The score value for the letter passed in
	// NOTE:	The letter passed in will always be upper-case
	int GetLetterValue(char _letter) 
	{
		auto iter = mLetterValues;
		if (iter == mLetterValues)
		{
			return mLetterValues[_letter - 65];
		}
	}
	
	// Get the value of a word
	//		This is done by adding up the values of each letter in the word
	//
	// In:	_word		The word to get the value of
	//
	// Return: The total value of the word
	int GetWordValue(string _word) 
	{
		//pass in a string for the word
		//go through the string to figure out what the value of each letter in the word is
		//and return the sum.

		int sum = 0;
		for (int i = 0; i < _word.size(); i++)
		{
			sum += GetLetterValue(_word[i]);
		}
		return sum;
	}

	// Create a pair to add into the scrabbleMap
	//		This will have a "first" of the word, and a "second" of the total score
	//
	// In:	_word		The word for the pair
	//
	// Return: A pair that contains the word and the total score
	pair<string, int> CreatePair(string _word) 
	{
		//word is the key in the pair we will creat.
		//the value will be the total word value
		//return the pair.

		return std::make_pair(_word, GetWordValue(_word));
	}

	// Load a file containing all of the possible scrabble words, along with their values
	//		This file will contain one word per line
	// In:	_filename	The name of the file to load
	//
	// Note: You may want to use one or more existing methods to help.
	void LoadWords(const char* _filename) 
	{
		//open file
			std::ifstream file(_filename);

			if (!file.is_open()) return;

			string currentline;

			//read file
			while (!file.eof())
			{
				std::getline(file, currentline);

				//creat a pair
				mScrabbleMap.insert(CreatePair(currentline));
			}
		file.close();
	}
	
	/**********************************/
	/* ONLY FOR USE IN FindValueInMap */
	/**********************************/
	int values[26] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };

	// Searches for a word in the map, and retrieves the score for that word
	//		This will make use of some of your previous methods
	//		Use above "values" array to populate your letter scores
	//		Use "words.txt" for loading words
	//
	// In:	_word			The word to search for
	//
	// Return: The word score for _word (or -1 if not found)
	int FindValueInMap(string _word) 
	{
		LoadWords("words.txt");

		for (int i = 0; i < 26; i++)
		{
			mLetterValues[i] = values[i];
		}

		auto iter = mScrabbleMap.find(_word);

		int score;
		if (iter != mScrabbleMap.end())
		{
			score = GetWordValue(_word);
			return score;
		}
		else
		{
			return -1;
		}
	}
};
#endif
