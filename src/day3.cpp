#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <sstream>
#include <unordered_map>

using namespace std;

int max(int i1, int i2)
{
	if (i1 >= i2)
		return i1;
	else
		return i2;
}

int min(int i1, int i2)
{
	if (i1 <= i2)
		return i1;
	else
		return i2;
}

class Area
{
public:
	Area(int id, int x1, int y1, int x2, int y2)
	{
		this->id = id;
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}

	int id;
	int x1, x2, y1, y2;
	int id_over = -1;
	bool doesOverlap = false;

	void print()
	{
		printf("Id: %d, (%d, %d), (%d, %d)\n", id, x1, y1, x2, y2);
	}

	bool overlaps(Area r)
	{
		return x1 < r.x2 && x2 > r.x1 && y1 < r.y2 && y2 > r.y1;
	}

	Area calcOverlap(Area r)
	{
		int _x1 = max(r.x1, x1);
		int _y1 = max(r.y1, y1);
		int _x2 = min(r.x2, x2);
		int _y2 = min(r.y2, y2);
		Area newArea(id, _x1, _y1, _x2, _y2);
		newArea.id_over = r.id;

		return newArea;
	}

	int size()
	{
		return (x2 - x1) * (y2 - y1);
	}

	void mark(int* arr, int r, int c)
	{
		for (int i = x1; i < x2; i++)
		{
			for (int j = y1; j < y2; j++)
			{
				arr[i*c + j]++;
			}
		}
	}

};

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

void day3(bool task2)
{
	ifstream dataFile("data/input3.txt");

	if (!dataFile.is_open())
	{
		cout << "Unable to open file" << endl;
		return;
	}

	// Parse coordinates
	string line;
	vector<Area> rectangles;
	int maxX = 0;
	int maxY = 0;
	while(getline(dataFile, line))
	{
		vector<string> splitString = split(line, ' ');
		vector<string> coords = split(splitString[2], ',');
		vector<string> size = split(splitString[3], 'x');

		int id = stoi(splitString[0].erase(0, 1));
		int x1 = stoi(coords[0]);
		int y1 = stoi(coords[1].erase(coords[1].size() - 1));
		int x2 = x1 + stoi(size[0]);
		int y2 = y1 + stoi(size[1]);

		Area rect(id, x1, y1, x2, y2);
		rectangles.push_back(rect);

		if (rect.x2 > maxX)
			maxX = rect.x2;

		if (rect.y2 > maxY)
			maxY = rect.y2;
	}

	int field[maxX][maxY] = { { 0 } };
	for(Area ar : rectangles)
		ar.mark((int*)field, maxX, maxY);

	// Count overlaps
	int overlapCount = 0;
	for (int i = 0; i < maxX; i++)
	{
		for (int j = 0; j < maxY; j++)
		{
			if (field[i][j] > 1)
				overlapCount++;
		}
	}

	cout << "Overlap count is: " << overlapCount << endl;

	if (!task2)
		return;


	int rectCount = rectangles.size();
	for (int i = 0; i < rectCount; i++)
	{
		for (int j = 0; j < rectCount; j++)
		{

			if (i == j)
				continue;
			if (rectangles[i].overlaps(rectangles[j]))
			{
				rectangles[i].doesOverlap = true;
				rectangles[j].doesOverlap = true;
			}
		}
	}

	for (int i = 0; i < rectCount; i++)
	{
		if (!rectangles[i].doesOverlap)
		{
			cout << "Not overlapping: " << rectangles[i].id << endl;
		}
	}
}

int main()
{
	day3(true);
	return 0;
}





