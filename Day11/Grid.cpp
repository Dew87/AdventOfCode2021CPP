#include "Grid.h"
#include <iostream>
#include <queue>

using namespace std;

Grid::Grid(vector<int> data, Vector2I size) : data(data), size(size)
{}

vector<int> Grid::getData() const
{
	return data;
}

int Grid::getIndex(Vector2I position) const
{
	return position.x + (position.y * size.x);
}

vector<int> Grid::getNeighbours(int index) const
{
	vector<int> neighbours;
	Vector2I position = getPosition(index);

	// Check for out of bounds and add neighbours clockwise
	if (0 < position.y)
	{
		if (0 < position.x)
		{
			neighbours.push_back(getIndex(position + Vector2I(-1, -1)));
		}
		neighbours.push_back(getIndex(position + Vector2I(0, -1)));
		if (position.x < size.x - 1)
		{
			neighbours.push_back(getIndex(position + Vector2I(1, -1)));
		}
	}
	if (position.x < size.x - 1)
	{
		neighbours.push_back(getIndex(position + Vector2I(1, 0)));
	}
	if (position.y < size.y - 1)
	{
		if (position.x < size.x - 1)
		{
			neighbours.push_back(getIndex(position + Vector2I(1, 1)));
		}
		neighbours.push_back(getIndex(position + Vector2I(0, 1)));
		if (0 < position.x)
		{
			neighbours.push_back(getIndex(position + Vector2I(-1, 1)));
		}
	}
	if (0 < position.x)
	{
		neighbours.push_back(getIndex(position + Vector2I(-1, 0)));
	}

	return neighbours;
}

Vector2I Grid::getPosition(int index) const
{
	return Vector2I(index % size.x, index / size.x);
}

Vector2I Grid::getSize() const
{
	return size;
}

int Grid::propagateStep()
{
	int flashes = 0;
	queue<int> processFlashes;

	// Initial step increase
	for (size_t i = 0; i < data.size(); i++)
	{
		data[i]++;
		if (data[i] == 10)
		{
			processFlashes.push((int)i);
		}
	}

	// Flashing
	while (!processFlashes.empty())
	{
		flashes++;
		int index = processFlashes.front();
		processFlashes.pop();

		vector<int> neighbours = getNeighbours(index);
		for (size_t i = 0; i < neighbours.size(); i++)
		{
			index = neighbours[i];
			data[index]++;
			if (data[index] == 10)
			{
				processFlashes.push(index);
			}
		}
	}

	// Reset flashing indexes
	for (size_t i = 0; i < data.size(); i++)
	{
		if (9 < data[i])
		{
			data[i] = 0;
		}
	}

	return flashes;
}

ostream& operator << (ostream &o, const Grid &grid)
{
	vector<int> data = grid.getData();
	Vector2I size = grid.getSize();

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
