/*
 * day7.cpp
 *
 *  Created on: Dec 8, 2018
 *      Author: lmark
 */

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <list>
#include <map>

using namespace std;

int char2Num(char c)
{
	return c - 'A' + 1 + 60;
}

void day7_task1()
{
	ifstream dataFile("data/input7.txt");

	if (!dataFile.is_open())
	{
		cout << "Unable to open file" << endl;
		return;
	}

	string line;
	char step_req, step_after;
	unordered_map<char, vector<char>> followUpMap;
	map<char, int> reqCountMap;
	while (getline(dataFile, line))
	{
		sscanf(line.c_str(), "Step %c must be finished before step %c can begin.", &step_req, &step_after);
		// cout << step_req << ", " << step_after << endl;
		vector<char> children = followUpMap[step_req];

		// Add element to vector
		bool added = false;
		for (int i = 0; i < (int)children.size(); i++)
		{
			if (step_req < children[i])
			{
				children.insert(children.begin() + i, step_after);
				added = true;
				break;
			}
		}

		// If not added push it back
		if (!added)
			children.push_back(step_after);

		// Add it to map
		followUpMap[step_req] = children;

		// Add empty requirement for step_req
		reqCountMap[step_after]++;
		reqCountMap[step_req] += 0;
	}

	map<char, int> reqCountMap1;
	reqCountMap1.insert(reqCountMap.begin(), reqCountMap.end());
	string jobString;

	while (reqCountMap1.size() != 0)
	{
		// Find out which char is without requirements
		char noReq_c;
		for (auto it = reqCountMap1.begin(); it != reqCountMap1.end(); ++it)
		{
			if (it->second == 0)
			{
				noReq_c = it->first;
				break;
			}

		}

		// Print all noRequirement chars and remove them from followup list
		cout << noReq_c;
		jobString.push_back(noReq_c);
		reqCountMap1.erase(noReq_c);

		for (char decReq_c : followUpMap[noReq_c])
		{
			reqCountMap1[decReq_c]--;
		}
	}
	cout << endl << "Task 1: " << jobString << endl;

	// TASK 2
	map<char, int> reqCountMap2;
	reqCountMap2.insert(reqCountMap.begin(),reqCountMap.end());

	int workerCount = 5;
	int workersBusy = 0;
	int currTime = 0;
	char workerJobs[workerCount];
	for (int i = 0; i < workerCount; i++)
		workerJobs[i] = '0';
	int timeRemain[workerCount] = { 0 };

	vector<char> jobBuffer;

	while (!(jobString.size() == 0 && workersBusy == 0))
	{
		cout << "Current time is: " << currTime << endl;
		// Decrease worker time
		for (int i = 0; i < workerCount; i++)
		{
			if (workerJobs[i] != '0')
			{
				timeRemain[i]--;
				cout << "Time remaining for worker " << i << " is: "
						<< timeRemain[i] << endl;

				// If remaining time is finished then update reqMap
				if (timeRemain[i] == 0)
				{

					cout << "Worker " << i << " has finished!"
							" job: " << workerJobs[i] << endl;
					for (char decReq_c : followUpMap[workerJobs[i]])
					{
						reqCountMap2[decReq_c]--;
					}

					workerJobs[i] = '0';
					workersBusy--;
					cout << workersBusy << " workers remain busy." << endl;
				}
			}
		}


		// Try to queue all available jobs
		while (workersBusy < workerCount &&
				jobString.size() > 0)
		{

			// Find first available job
			char currChar = '0';
			for (int i = 0; i < (int)jobString.size(); i++)
			{
				if (reqCountMap2[jobString[i]] == 0)
				{
					currChar = jobString[i];
					jobString.erase(i, 1);
					break;
				}
			}

			// Check if the curr Job is available
			if (currChar == '0')
			{
				cout << "No job is currently available" << endl;
				break;
			}

			cout << "Job " << currChar << " is availiable." << endl;
			cout << "Rest of the jobs: " << jobString << endl;

			// .. job is available
			// Give it to a worker !
			for (int i = 0; i < workerCount; i++)
			{
				if (workerJobs[i] == '0')
				{
					workerJobs[i] = currChar;
					timeRemain[i] = char2Num(currChar);
					cout << "Worker " << i
							<< " starts working on job " << currChar
							<< " for " << timeRemain[i] << " mins." << endl;
					break;
				}
			}

			workersBusy++;
			cout << workersBusy << " workers are busy." << endl;
		}

		currTime++;
		cout << endl;
		cout << endl;
	}

	cout << "Time: " << currTime - 1 << endl;
}


int main() {
	day7_task1();
}



