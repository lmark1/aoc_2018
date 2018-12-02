/*
 * day2.cpp
 *
 *  Created on: Dec 2, 2018
 *      Author: lmark
 */

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

void day2_task1()
{
	ifstream dataFile("data/input2.txt");

	if (!dataFile.is_open())
	{
		cout << "Unable to open file" << endl;
		return;
	}

	string line;
	map<char, int> charMap;
	int twos = 0;
	int threes = 0;
	while(getline(dataFile, line))
	{
		charMap.clear();
		cout << line << endl;

		// Fill the charMap
		int lineSize = line.size();
		for (int i = 0; i < lineSize; i++)
		{
			char currChar = line[i];
			map<char, int>::iterator mapEntry = charMap.find(currChar);
			if (mapEntry == charMap.end())
			{
				charMap.insert(make_pair(currChar, 1));
			}
			else
			{
				charMap[currChar] = mapEntry->second + 1;
			}
		}

		// Check if 2 or 3
		bool isTwo = false;
		bool isThree = false;
		map<char,int>::iterator it = charMap.begin();
		while (it != charMap.end())
		{
			if (it->second == 2)
				isTwo = true;

			if (it->second == 3)
				isThree = true;

			it++;
		}

		if (isTwo)
			twos++;

		if (isThree)
			threes++;

		cout << twos << endl;
		cout << threes << endl;
	}

	cout << "Number of twos: " << twos << endl;
	cout << "Number of threes: " << threes << endl;
	cout << "Checksum: " << twos*threes << endl;
}


void day2_task2()
{
	ifstream dataFile("data/input2.txt");

	if (!dataFile.is_open())
	{
		cout << "Unable to open file" << endl;
		return;
	}

	string line;
	vector<string> entryVector;
	while(getline(dataFile, line))
	{
		entryVector.push_back(line);
	}

	int entrySize = entryVector[0].size();
	int dataSize = entryVector.size();
	cout << "Word size: " << entrySize << endl;
	string similar1 = "";
	string similar2 = "";
	for(int i = 0; i < dataSize && similar1.size() == 0; i++)
	{

		for(int j = i+1; j < dataSize && similar1.size() == 0; j++)
		{

			//out << "Checking: " << i << " and: " << j << endl;
			int eqCount = 0;
			//cout << "Comparing: " << i << ", and: " << j << endl;
			for (int k = 0; k < entrySize; k++)
			{
				if (entryVector[i].at(k) == entryVector[j].at(k))
					eqCount++;

				if (eqCount < k) // Break if more than 2 are wrong
					break;

			} // Iterate through each ID

			if (eqCount == (entrySize-1))
			{
				similar1 = entryVector[i];
				similar2 = entryVector[j];
			}
		} // Iterate from current to the end
	} // Iterate through all ids

	cout << "First sim: " << similar1 << endl;
	cout << "Second sim: " << similar2 << endl;

	cout << "Similarities: ";
	for (int i = 0; i < entrySize; i++)
	{
		if (similar1.at(i) == similar2.at(i))
			cout << similar1.at(i);
	}
}


int main()
{
	//day2_task1();
	day2_task2();
	return 0;
}

