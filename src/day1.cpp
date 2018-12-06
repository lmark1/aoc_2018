#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int getNumber(std::string s)
{
	if (s[0] == '+')
	{
		s.erase(0, 1);
		return stoi(s);
	}
	else if (s[0] == '-')
	{
		s.erase(0, 1);
		return -stoi(s);
	}
	else
	{
		cout << "Unable to parse line: " << s << endl;
		throw std::runtime_error("Parse error, exiting...");
	}
}

int day1_task1() {

	ifstream dataFile("data/input1.txt");

	if (!dataFile.is_open())
	{
		cout << "Unable to open file" << endl;
		return 0;
	}

	string line;
	std::string::size_type sz;
	int totalCount = 0;
	while (getline(dataFile, line))
	{
		totalCount += getNumber(line);
	}

	cout << "Resulting frequency is: " << totalCount << endl;
	return 0;
}

int day1_task2()
{
	ifstream dataFile("data/input1.txt");

	if (!dataFile.is_open())
	{
		cout << "Unable to open file" << endl;
		return 0;
	}

	string line;
	std::string::size_type sz;
	int totalCount = 0;
	int arrSize = 0;
	bool foundDuplicate = false;
	int* freqArray = nullptr;

	while (!foundDuplicate) // looping cyclically through file
	{
		while (getline(dataFile, line) && !foundDuplicate) // loop a single time through file
		{
			totalCount += getNumber(line);

			if (freqArray == nullptr)
			{
				cout << "Initializing array!" << endl;
				freqArray = (int*)malloc(sizeof(int));
			}
			else
			{
				//cout << "Resizing array!" << endl;
				arrSize++;
				freqArray = (int*)realloc(freqArray, sizeof(int)*(arrSize + 1));
			}
			freqArray[arrSize] = totalCount;

			// cout << "Total count: " << totalCount << endl;
			// Find duplicates
			for (int i = 0; i < arrSize; i++)
			{
				// cout << "Checking duplicate: " << i << endl;
				if (freqArray[arrSize] == freqArray[i])
				{
					foundDuplicate = true;
					break;
				}
			}
		}

		//cout << "Finished reading lines" << endl;

		// Go to the beginning
		dataFile.clear();
		dataFile.seekg(0, ios::beg);
	}


	cout << "Task2: " << freqArray[arrSize] << endl;
	delete[] freqArray;
	return 0;
}

int main(int argc, char **argv) {
	day1_task1();
	day1_task2();
	return 0;
}

