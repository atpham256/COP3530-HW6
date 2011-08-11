// Name: Anthony T. Pham
// UF ID: 5038-1111
// Discussion section #: 1079

#include<iostream>
#include<fstream>
#include<string>
#include<stack>
#include "hw6.h"

using namespace std;

// hash function
int hash(string substring, int m)
{
	int h = 0, a = 127;
	for(int i = 0; i < substring.length(); i++)
	{
		h = (a*h + (int)substring.at(i)) % m;
	}
	return h;
}

int main()
{
	// declaration of variables
	ifstream inFile;
	inFile.open("hw6prob5in");
	ofstream outFile("hw6prob5out");
	int numOfPatternStrings, hashValue, *hashTable, index, start, end;
	string longString, substring;
	bool match = true;

	outFile << "start end" << endl;

	// read in the number of pattern strings
	inFile >> numOfPatternStrings;

	// create an array to hold all the pattern strings
	string *patternString = new string[numOfPatternStrings];

	// fill the array with the pattern strings
	for(int i = 0; i < numOfPatternStrings; i++)
	{
		inFile >> patternString[i];
	}

	// read in the long string
	inFile >> longString;

	// calculate the size of the hash table = next prime closest to the length of the longString
	int hashTableSize = longString.length();
	while(hashTableSize%2 == 0 || hashTableSize%3 == 0 || hashTableSize%4 == 0 || hashTableSize%5 == 0 || hashTableSize%6 == 0 || hashTableSize%7 == 0 || hashTableSize%8 == 0 || hashTableSize%9 == 0)
	{
		hashTableSize = hashTableSize + 1;
	}

	// loop to go through all pattern strings
	for(int i = 0; i < numOfPatternStrings; i++)
	{
		// create hash table
		hashTable = new int[hashTableSize];
		// fill hash table with dummy values
		for(int y = 0; y < hashTableSize; y++)
		{
			hashTable[y] = -1;
		}
		// calculate the hash values for each possible substring of the long string
		for(int j = 0; j < (longString.length() - patternString[i].length() + 1); j++)
		{
			for(int x = j; x < (j+patternString[i].length()); x++)
			{
				substring = substring + longString.at(x);
			}
			hashValue = hash(substring, hashTableSize);
			// find an index to store the substring
			while(hashTable[hashValue] != -1)
			{
				hashValue = hashValue + 1;
				if(hashValue >= hashTableSize)
				{
					hashValue = 0;
				}
			}
			// store the index of the first character of the substring
			hashTable[hashValue] = j;
			substring = "";
		}
		// find the hash value of the pattern string
		hashValue = hash(patternString[i], hashTableSize);
		// check if there is a match in the long strong
		while(hashTable[hashValue] != -1)
		{
			// reset values
			match = true;
			index = hashTable[hashValue];
			// check the strings to see if they match
			for(int z = 0; z < patternString[i].length(); z++)
			{
				if(patternString[i].at(z) != longString.at(index))
				{
					match = false;
				}
				index = index + 1;
			}
			// if the strings match, determine the starting and ending index of the string inside
			// the long string
			if(match)
			{
				start = hashTable[hashValue];
				end = start + patternString[i].length() - 1;
				break;
			}
			hashValue = hashValue + 1;
			if(hashValue >= hashTableSize)
			{
				hashValue = 0;
			}
		}
		// if there is no match, start and end are -1
		if(!match)
		{
			start = -1;
			end = -1;
		}
		// write the start and end of the pattern string found in the long string to the file
		outFile << start << " " << end << endl;
	}

	cout << "Writing to file complete." << endl;
	// close file streams
	inFile.close();
	outFile.close();
	return 0;
}
