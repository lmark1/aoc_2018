/*
 * day6.cpp
 *
 *  Created on: Dec 6, 2018
 *      Author: lmark
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <unordered_set>

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

class Point
{
public:
	Point(int x, int y): x(x), y(y)
	{}

	int x;
	int y;
	bool isBorder = false;

	int dist(const Point p)
	{
		return abs(x - p.x) + abs(y - p.y);
	}

};

void day6_task1()
{
	ifstream dataFile("data/input6.txt");

	if (!dataFile.is_open())
	{
		cout << "Unable to open file" << endl;
		return;
	}

	string line;
	vector<Point> pointVector;
	int maxX = 0;
	int minX = 1000;
	int maxY = 0;
	int minY = 1000;
	while(getline(dataFile, line))
	{
		vector<string> splitLine = split(line, ',');
		int x = stoi(splitLine[0]);
		int y = stoi(splitLine[1]);

		if (x > maxX)
			maxX = x;

		if (x < minX)
			minX = x;

		if (y > maxY)
			maxY = y;

		if (y < minY)
			minY = y;

		Point newPoint(x, y);
		pointVector.push_back(newPoint);
	}

	// Initialize field
	int width = maxX - minX;
	int height = maxY - minY;

	// Normalize points
	int pSize = pointVector.size();
	for (int i = 0; i < pSize; i++)
	{
		pointVector[i].x -= minX;
		pointVector[i].y -= minY;
	}

	map<int, int> fieldMap;
	int part2Res = 0;
	// Fill up field arrays
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{

			Point fieldPoint(x, y);
			int minDist = 10e5;
			int minIndex = -1;
			int totalDist = 0;
			bool isEqual = false;
			for(int i = 0; i < pSize; i++)
			{
				Point p = pointVector[i];
				int distance = p.dist(fieldPoint);

				// Check if distance is lesser than current
				if (distance < minDist)
				{
					minDist = distance;
					isEqual = false;
					minIndex = i;
				}
				// ... if equidistant
				else if (distance ==  minDist)
				{
					isEqual = true;
				}

				totalDist += distance;
			}

			if (!isEqual)
				fieldMap[minIndex]++;

			if (x == 0 || x == width - 1 || y == 0 || y == height -1)
				pointVector[minIndex].isBorder = true;

			if (totalDist < 10000)
				part2Res++;

		} // Iterate through y coords
	} // Iterate through x corrds

	// Find max cover that doesnt extend to border
	int maxCover = 0;
	for (auto it = fieldMap.begin(); it != fieldMap.end(); ++it)
	{
		if (pointVector[it->first].isBorder)
			continue;

		if (it->second > maxCover)
			maxCover = it->second;
	}
	cout << maxCover << endl;
	cout << part2Res << endl;
}


int main()
{
	day6_task1();
}
