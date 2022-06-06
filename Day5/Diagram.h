#ifndef DIAGRAM_H
#define DIAGRAM_H

#include "Vector2I.h"
#include <ostream>
#include <vector>

struct Diagram
{
	Diagram(Vector2I size);
	int CountNumberOfOverlaps(int threshold) const;
	int Index(Vector2I position) const;

	std::vector<int> data;
	Vector2I size;
};

std::ostream& operator << (std::ostream &o, const Diagram &diagram);

#endif
