#include "HeightMap.h"
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

HeightMap::HeightMap(vector<int> data, Vector2I size) : data(data), size(size)
{
	processLowPoints();
	processBasins();
}

vector<vector<int>> HeightMap::getBasins() const
{
	return basins;
}

vector<int> HeightMap::getData() const
{
	return data;
}

int HeightMap::getIndex(Vector2I position) const
{
	return position.x + (position.y * size.x);
}

vector<int> HeightMap::getLowPoints() const
{
	return lowPoints;
}

Vector2I HeightMap::getPosition(int index) const
{
	return Vector2I(index % size.x, index / size.x);
}

Vector2I HeightMap::getSize() const
{
	return size;
}

void HeightMap::PrintBasinsPositions() const
{
	for (size_t i = 0; i < basins.size(); i++)
	{
		cout << "Start of basin[" << i << "][" << basins[i].size() << "]\n";
		for (size_t j = 0; j < basins[i].size(); j++)
		{
			cout << getPosition(basins[i][j]) << "\n";
		}
		cout << "End of basin\n\n";
	}
}

void HeightMap::PrintData() const
{
	cout << "Start of height Map[" << data.size() << "]\n";
	cout << *this;
	cout << "End of height Map\n\n";
}

void HeightMap::PrintLowPointsPositions() const
{
	cout << "Start of low points[" << lowPoints.size() << "] print\n";
	for (size_t i = 0; i < lowPoints.size(); i++)
	{
		cout << getPosition(lowPoints[i]) << "\n";
	}
	cout << "End of low points print\n\n";
}

void HeightMap::processBasins()
{
	vector<bool> isIndexExplored(data.size(), false);

	for (size_t i = 0; i < lowPoints.size(); i++)
	{
		int index = lowPoints[i];
		vector<int> basin;
		queue<int> indexQueue;

		if (!isIndexExplored[index] && data[index] != 9)
		{
			isIndexExplored[index] = true;
			indexQueue.push(index);
		}
		while (!indexQueue.empty())
		{
			index = indexQueue.front();
			indexQueue.pop();

			basin.push_back(index);

			Vector2I position = getPosition(index);
			if (0 < position.x)
			{
				int indexLeft = index - 1;
				if (!isIndexExplored[indexLeft] && data[indexLeft] != 9)
				{
					isIndexExplored[indexLeft] = true;
					indexQueue.push(indexLeft);
				}
			}
			if (position.x < size.x - 1)
			{
				int indexRight = index + 1;
				if (!isIndexExplored[indexRight] && data[indexRight] != 9)
				{
					isIndexExplored[indexRight] = true;
					indexQueue.push(indexRight);
				}
			}
			if (0 < position.y)
			{
				int indexTop = index - size.x;
				if (!isIndexExplored[indexTop] && data[indexTop] != 9)
				{
					isIndexExplored[indexTop] = true;
					indexQueue.push(indexTop);
				}
			}
			if (position.y < size.y - 1)
			{
				int indexBottom = index + size.x;
				if (!isIndexExplored[indexBottom] && data[indexBottom] != 9)
				{
					isIndexExplored[indexBottom] = true;
					indexQueue.push(indexBottom);
				}
			}
		}
		if (!basin.empty())
		{
			sort(basin.begin(), basin.end());
			basins.push_back(basin);
		}
	}
}

void HeightMap::processLowPoints()
{
	for (int y = 0; y < size.y; y++)
	{
		for (int x = 0; x < size.x; x++)
		{
			int index = getIndex(Vector2I(x, y));
			bool lessThenLeft = true;
			if (0 < x)
			{
				int indexLeft = getIndex(Vector2I(x - 1, y));
				lessThenLeft = data[index] < data[indexLeft];
			}

			bool lessThenRight = true;
			if (x < size.x - 1)
			{
				int indexRight = getIndex(Vector2I(x + 1, y));
				lessThenRight = data[index] < data[indexRight];
			}

			bool lessThenTop = true;
			if (0 < y)
			{
				int indexTop = getIndex(Vector2I(x, y - 1));
				lessThenTop = data[index] < data[indexTop];
			}

			bool lessThenBottom = true;
			if (y < size.y - 1)
			{
				int indexBottom = getIndex(Vector2I(x, y + 1));
				lessThenBottom = data[index] < data[indexBottom];
			}

			if (lessThenLeft && lessThenRight && lessThenTop && lessThenBottom)
			{
				lowPoints.push_back(index);
			}
		}
	}
}

ostream& operator << (ostream &o, const HeightMap &heightMap)
{
	vector<int> data = heightMap.getData();
	Vector2I size = heightMap.getSize();

	for (int i = 0; i < size.y; i++)
	{
		for (int j = 0; j < size.x; j++)
		{
			o << data[((size_t)i * size.x) + j];
		}
		o << "\n";
	}
	return o;
}
