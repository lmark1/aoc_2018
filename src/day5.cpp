#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <cctype>
#include <unordered_map>

using namespace std;

bool charReacts(char c1, char c2)
{
	if (isupper(c1) != 0 && islower(c2) != 0)
	{
		return c2 == c1 + 32;
	}
	else if (islower(c1) != 0 && isupper(c2) != 0)
	{
		return c1 == c2 + 32;
	}
	else
		return false;
}

bool charReacts2(char c1, char c2)
{
	return abs(c1 - c2) == abs('A' - 'a');
}

void day5_task1()
{
	ifstream dataFile("data/input5.txt");

	if (!dataFile.is_open())
	{
		cout << "Unable to open file" << endl;
		return;
	}

	string input(istreambuf_iterator<char>(dataFile), {});

	string res;
	res.push_back(input.at(0));
	for(int i = 1; i < (int)input.size(); i++)
	{
		if (isspace(input[i]))
			continue;

		if (charReacts2(res[res.size()-1], input[i]))
		{
			res.erase(res.size()-1, 1);
		}
		else
		{
			res.push_back(input.at(i));
		}
	}
	cout << "Rest size: " << res.size() << endl;
}

void day5_task2()
{
	ifstream dataFile("data/input5.txt");

	if (!dataFile.is_open())
	{
		cout << "Unable to open file" << endl;
		return;
	}

	string input(istreambuf_iterator<char>(dataFile), {});

	unordered_map<char, int> polyMap;
	int minRes = 10e6;
	char minCharType = '?';
	for (int i = 0; i < (int)input.size(); i++)
	{
		if (isspace(input[i]))
		continue;

		char currChar = tolower(input.at(i));
		if (polyMap[currChar] != 0)
			continue; // input already assesed

		string result;
		result.push_back(input.at(0));
		for (int j = 1; j < (int)input.size(); j++)
		{
			// Proceed normally
			if (isspace(input[j]) || currChar == tolower(input[j]))
				continue;

			if (charReacts2(result[result.size()-1], input[j]))
			{
				result.erase(result.size()-1, 1);
			}
			else
				result.push_back(input.at(j));
		}

		int resSize = result.size();
		polyMap[currChar] = resSize;
		cout << "Min res: " << resSize << ", for char: " << currChar << endl;
		if (resSize < minRes)
		{
			minRes = resSize;
			minCharType = currChar;
		}
	}

	cout << "Best poly: " << minCharType << endl;
	cout << "Smallest res: " << minRes << endl;
}

int main()
{
	day5_task1();
	day5_task2();
}


