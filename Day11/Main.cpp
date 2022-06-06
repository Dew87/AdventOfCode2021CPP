#include "Grid.h"
#include <iostream>
#include <string>

using namespace std;

void InputGrid(vector<int> &vOutputData, Vector2I &v2IOutputSize)
{
	cout << "Start of octupus grid input (Invalid input to end)\n";
	for (int i = 0; true; i++)
	{
		string input;
		getline(cin, input);

		for (size_t j = 0; j < input.size(); j++)
		{
			string inputSubstring = input.substr(j, 1);
			try
			{
				int number = stoi(inputSubstring);
				vOutputData.push_back(number);
				v2IOutputSize = Vector2I((int)input.size(), i + 1);
			}
			catch (exception e)
			{
				cout << "End of octupus grid input\n\n";
				return;
			}
		}
	}
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

void PropagateSteps(Grid grid, int steps)
{
	int flashes = 0;

	cout << "Before any steps:\n" << grid << "\n";
	for (int i = 1; i <= steps; i++)
	{
		flashes += grid.propagateStep();
		cout << "After step " << i << ":\n" << grid << "\n";
	}

	cout << "After " << steps << " steps, there have been a total of " << flashes << " flashes.\n\n";
}

void PropagateStepsUntilSynchronized(Grid grid, int maxSteps)
{
	for (int i = 1; i <= maxSteps; i++)
	{
		if (grid.propagateStep() == grid.getData().size())
		{
			cout << "After step " << i << ":\n" << grid << "\n";
			cout << "First step all octopuses flash simultaneously is step " << i << "\n";
			return;
		}
	}
	cout << "No step when all octopuses flash simultaneously during " << maxSteps << " max steps\n\n";
}

int main()
{
	cout << "Advent of code 2021\n";
	cout << "Day 11: Dumbo Octopus\n";
	cout << "Program by David Erikssen\n\n";

	vector<int> data;
	Vector2I size;

	InputGrid(data, size);
	Grid grid(data, size);

	PropagateSteps(grid, 100);
	PropagateStepsUntilSynchronized(grid, 1000);

	return 0;
}
