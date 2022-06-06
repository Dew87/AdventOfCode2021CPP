#ifndef HEIGHT_MAP_H
#define HEIGHT_MAP_H

#include "Vector2I.h"
#include <ostream>
#include <vector>

class HeightMap
{
public:
	HeightMap(std::vector<int> data, Vector2I size);

	std::vector<std::vector<int>> getBasins() const;
	std::vector<int> getData() const;
	int getIndex(Vector2I position) const;
	std::vector<int> getLowPoints() const;
	Vector2I getPosition(int index) const;
	Vector2I getSize() const;

	void PrintBasinsPositions() const;
	void PrintData() const;
	void PrintLowPointsPositions() const;

private:
	void processBasins();
	void processLowPoints();

	std::vector<std::vector<int>> basins;
	std::vector<int> data;
	std::vector<int> lowPoints;
	Vector2I size;
};

std::ostream& operator << (std::ostream &o, const HeightMap &diagram);

#endif
