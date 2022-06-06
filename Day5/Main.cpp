#include "Diagram.h"
#include "Line.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool InputVector2I(const string sInput, Vector2I &v2IOutput, char separator)
{
	size_t i = sInput.find(separator);
	if (i != string::npos)
	{
		string inputX = sInput.substr(0, i);
		string inputY = sInput.substr(i + 1);
		try
		{
			int x = stoi(inputX);
			int y = stoi(inputY);
			v2IOutput = Vector2I(x, y);
			return true;
		}
		catch (exception e)
		{ }
	}
	return false;
}

void InputLines(vector<Line> &vOutput)
{
	cout << "Start of lines input (X,Y -> X,Y Invalid input to end)\n";
	while (true)
	{
		string input;
		getline(cin, input);

		size_t i = input.find("->");
		if (i != string::npos)
		{
			Vector2I a;
			Vector2I b;

			bool aValid = InputVector2I(input.substr(0, i), a, ',');
			bool bValid = InputVector2I(input.substr(i + 2), b, ',');

			if (aValid && bValid)
			{
				vOutput.push_back(Line(a, b));
				continue;
			}
		}
		break;
	}
	cout << "End of lines input\n\n";
}

Vector2I MaxSizeVector2I(const vector<Line> &vInput)
{
	Vector2I max;
	for (size_t i = 0; i < vInput.size(); i++)
	{
		Vector2I a = vInput[i].a;
		Vector2I b = vInput[i].b;

		max.x = max.x < a.x ? a.x : max.x;
		max.x = max.x < b.x ? b.x : max.x;

		max.y = max.y < a.y ? a.y : max.y;
		max.y = max.y < b.y ? b.y : max.y;
	}
	return max + Vector2I(1, 1);
}

void PropagateDiagramWithDiagonals(const Diagram &inputDiagram, const vector<Line> &vInputLines)
{
	Diagram diagram = inputDiagram;
	for (size_t i = 0; i < vInputLines.size(); i++)
	{
		// Extract vectors. Order vectors so a.x <= b.x and c.y <= d.y
		Vector2I a = vInputLines[i].a.x < vInputLines[i].b.x ? vInputLines[i].a : vInputLines[i].b;
		Vector2I b = vInputLines[i].a.x < vInputLines[i].b.x ? vInputLines[i].b : vInputLines[i].a;
		Vector2I c = vInputLines[i].a.y < vInputLines[i].b.y ? vInputLines[i].a : vInputLines[i].b;
		Vector2I d = vInputLines[i].a.y < vInputLines[i].b.y ? vInputLines[i].b : vInputLines[i].a;

		if (a.x == b.x && a.y == b.y)
		{
			// Line is a dot
			diagram.data[diagram.Index(a)]++;
		}
		else if (a.y == b.y)
		{
			// Horizontal line
			for (int j = 0; j <= b.x - a.x; j++)
			{
				diagram.data[diagram.Index(Vector2I(a.x + j, a.y))]++;
			}
		}
		else if (c.x == d.x)
		{
			// Vertical line
			for (int j = 0; j <= d.y - c.y; j++)
			{
				diagram.data[diagram.Index(Vector2I(c.x, c.y + j))]++;
			}
		}
		else if (b.x - a.x == b.y - a.y)
		{
			// Diagonal increasing y
			for (int j = 0; j <= b.x - a.x; j++)
			{
				diagram.data[diagram.Index(Vector2I(a.x + j, a.y + j))]++;
			}
		}
		else if (b.x - a.x == -(b.y - a.y))
		{
			// Diagonal decreasing y
			for (int j = 0; j <= b.x - a.x; j++)
			{
				diagram.data[diagram.Index(Vector2I(a.x + j, a.y - j))]++;
			}
		}
	}

	//cout << diagram << "\n";
	cout << "Overlaps new method: " << diagram.CountNumberOfOverlaps(2) << "\n\n";
}

void PropagateDiagramWithoutDiagonals(const Diagram &inputDiagram, const vector<Line> &vInputLines)
{
	Diagram diagram = inputDiagram;
	for (size_t i = 0; i < vInputLines.size(); i++)
	{
		// Extract vectors. Order vectors so a.x <= b.x and c.y <= d.y
		Vector2I a = vInputLines[i].a.x < vInputLines[i].b.x ? vInputLines[i].a : vInputLines[i].b;
		Vector2I b = vInputLines[i].a.x < vInputLines[i].b.x ? vInputLines[i].b : vInputLines[i].a;
		Vector2I c = vInputLines[i].a.y < vInputLines[i].b.y ? vInputLines[i].a : vInputLines[i].b;
		Vector2I d = vInputLines[i].a.y < vInputLines[i].b.y ? vInputLines[i].b : vInputLines[i].a;

		if (a.x == b.x && a.y == b.y)
		{
			// Line is a dot
			diagram.data[diagram.Index(a)]++;
		}
		else if (a.y == b.y)
		{
			// Horizontal line
			for (int j = 0; j <= b.x - a.x; j++)
			{
				diagram.data[diagram.Index(Vector2I(a.x + j, a.y))]++;
			}
		}
		else if (c.x == d.x)
		{
			// Vertical line
			for (int j = 0; j <= d.y - c.y; j++)
			{
				diagram.data[diagram.Index(Vector2I(c.x, c.y + j))]++;
			}
		}
	}

	//cout << diagram << "\n";
	cout << "Overlaps old method: " << diagram.CountNumberOfOverlaps(2) << "\n\n";
}

template <typename T>
void PrintVector(const vector<T> &vInput, const char *vName, const char* separation)
{
	cout << "Start of " << vName << "[" << vInput.size() << "] print\n";
	if (0 < vInput.size())
	{
		for (size_t i = 0; i < vInput.size() - 1; i++)
		{
			cout << vInput[i] << separation;
		}
		cout << vInput[vInput.size() - 1] << "\n";
	}
	cout << "End of " << vName << " print\n\n";
}

int main()
{
	cout << "Advent of code 2021\n";
	cout << "Day 5: Hydrothermal Venture\n";
	cout << "Program by David Erikssen\n\n";

	vector<Line> lines;
	InputLines(lines);
	PrintVector(lines, "lines", "\n");

	Diagram diagram(MaxSizeVector2I(lines));

	PropagateDiagramWithoutDiagonals(diagram, lines);
	PropagateDiagramWithDiagonals(diagram, lines);

	return 0;
}
