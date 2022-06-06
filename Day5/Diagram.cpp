#include "Diagram.h"

using namespace std;

void OutputDiagramRow(ostream &o, const Diagram &diagram, int row)
{
	if (0 <= row && row < diagram.size.y)
	{
		int rowIndex = row * diagram.size.x;
		for (int i = 0; i < diagram.size.x; i++)
		{
			o << diagram.data[rowIndex + i];
		}
	}
}

Diagram::Diagram(Vector2I size) : size(size), data(size.x * size.y)
{}

int Diagram::CountNumberOfOverlaps(int threshold) const
{
	int sum = 0;
	for (size_t i = 0; i < data.size(); i++)
	{
		if (threshold <= data[i])
		{
			sum++;
		}
	}
	return sum;
}

int Diagram::Index(Vector2I position) const
{
	return position.x + (position.y * size.x);
}

ostream& operator << (ostream &o, const Diagram &diagram)
{
	if (0 < diagram.size.y)
	{
		for (int i = 0; i < diagram.size.y - 1; i++)
		{
			OutputDiagramRow(o, diagram, i);
			o << "\n";
		}
		OutputDiagramRow(o, diagram, diagram.size.y - 1);
	}
	return o;
}
