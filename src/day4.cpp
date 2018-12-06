/*
 * day4.cpp
 *
 *  Created on: Dec 4, 2018
 *      Author: lmark
 */
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <sstream>
#include <unordered_map>
#include <cstring>
#include <algorithm>

using namespace std;


std::vector<std::string> split(std::string strToSplit, char delimeter)
{
    std::stringstream ss(strToSplit);
    std::string item;
	std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
	{
		splittedStrings.push_back(item);
    }
	return splittedStrings;
}

void day4_task1()
{
	ifstream dataFile("data/input4.txt");

	if (!dataFile.is_open())
	{
		cout << "Unable to open file" << endl;
		return;
	}

	string line;
	vector<string> lines;
	while(getline(dataFile, line))
	{
		lines.push_back(line);
	}
	sort(lines.begin(), lines.end());

	// Parse information
	char c_sentance[30];
	int year, month, day, hour, minute;

	// Guard information
	int guard_id = -1;
	bool isAsleep = false;
	bool isAwake = false;
	unordered_map<int, int*> guardInfo;
	int prev_time = 0;
	int curr_time = 0;
	for (auto line : lines)
	{
		// Parse the string
		sscanf(line.c_str(), "[%d-%d-%d %d:%d] %[^\n]",
				&year, &month, &day, &hour, &minute, c_sentance);
		string words(c_sentance);
		curr_time = minute;

		// Wake up case
		if (strcmp(words.c_str(), "wakes up") == 0)
		{
			if (guard_id >= 0 && isAsleep)
			{
				isAsleep = false;
				isAwake = true;
				if (guardInfo.find(guard_id) == guardInfo.end())
				{
					guardInfo[guard_id] = (int*)calloc(60, sizeof(int));
				}
				for (int i = prev_time; i < curr_time; i++)
				{
					(guardInfo[guard_id])[i]++;
				}
			}
		}
		// Fall asleep case
		else if (strcmp(words.c_str(), "falls asleep") == 0)
		{
			if (guard_id >= 0 && isAwake)
			{
				isAsleep = true;
				isAwake = false;
				prev_time = curr_time;
			}
		}
		// New guard case
		else
		{
			vector<string> splitString = split(words, ' ');
			string stringId = splitString[1].erase(0, 1);
			guard_id = stoi(stringId);
			isAwake = true;
			isAsleep = false;
		}
	}

	// Check who sleeps most
	int maxSleep = 0;
	int maxId = 0;

	for (auto it = guardInfo.begin(); it != guardInfo.end(); ++it)
	{
		int count = 0;
		for (int i = 0; i < 60; i++)
			count += (it->second)[i];

		if (count > maxSleep)
		{
			maxSleep = count;
			maxId = it->first;
		}
	}
	cout << "Most minutes asleep id: " << maxId << endl;

	// Count which minute guard sleeps most
	int maxSleepMins = 0;
	int maxMin = 0;
	for (int i = 0; i < 60; i++)
	{
		if (guardInfo[maxId][i] > maxSleepMins)
		{
			maxSleepMins = guardInfo[maxId][i];
			maxMin = i;
		}
	}

	cout << "Most minutes asleep min: " << maxMin << endl;
	cout << "Answer: " << maxMin * maxId << endl;

	// Which guard sleeps most single minutes
	int maxMinuteIndex = 0;
	int maxSleepMinutes = 0;
	int maxSleepMinuteId = 0;
	for (auto it = guardInfo.begin(); it != guardInfo.end(); ++it)
	{
		for (int i = 0; i < 60; i++)
		{
			int currMin = (it->second)[i];
			if (currMin > maxSleepMinutes)
			{
				maxSleepMinutes = currMin;
				maxMinuteIndex = i;
				maxSleepMinuteId = it->first;
			}

		}
	}
	cout << "Most slept at single minute: " << guardInfo[maxSleepMinuteId][maxSleepMinutes] << endl;
	cout << "Most slept minute: " << maxSleepMinutes << endl;
	cout << "Most single minutes asleep id: " << maxSleepMinuteId << endl;
	cout << "Answer2: " << maxSleepMinuteId * maxMinuteIndex << endl;

}

int main()
{
	day4_task1();
}



