#ifndef GRID_H
#define GRID_H

#include "Vector2I.h"
#include <vector>

class Grid
{
public:
	Grid(std::vector<int> data, Vector2I size);

	std::vector<int> getData() const;
	int getIndex(Vector2I position) const;
	Vector2I getPosition(int index) const;
	Vector2I getSize() const;

	int propagateStep();

private:
	std::vector<int> getNeighbours(int index) const;

	std::vector<int> data;
	Vector2I size;
};

std::ostream& operator << (std::ostream &o, const Grid &grid);

#endif
