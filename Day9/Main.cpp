#include "HeightMap.h"
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

void InputHeightMap(vector<int> &vOutputData, Vector2I &v2IOutputSize)
{
	cout << "Start of height map input (Invalid input to end)\n";
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
				cout << "End of height map input\n\n";
				return;
			}
		}
	}
}

int MultiplyLargestBasins(const HeightMap &heightMap, int numberOfBasins)
{
	vector<vector<int>> basins = heightMap.getBasins();
	sort(basins.begin(), basins.end(), [](const vector<int> &a, const vector<int> &b) { return a.size() > b.size(); });

	int multiply = 1;
	for (size_t i = 0; i < basins.size() && i < numberOfBasins; i++)
	{
		multiply *= (int)basins[i].size();
	}
	return multiply;
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

int SumOfRiskLevels(const HeightMap &heightMap)
{
	vector<int> data = heightMap.getData();
	vector<int> lowPoints = heightMap.getLowPoints();

	int sum = 0;
	for (size_t i = 0; i < lowPoints.size(); i++)
	{
		sum += data[lowPoints[i]] + 1;
	}
	return sum;
}

int main()
{
	cout << "Advent of code 2021\n";
	cout << "Day 9: Smoke Basin\n";
	cout << "Program by David Erikssen\n\n";

	vector<int> heightMapData;
	Vector2I heightMapSize;

	InputHeightMap(heightMapData, heightMapSize);
	HeightMap heightMap(heightMapData, heightMapSize);

	int sumOfRiskLevels = SumOfRiskLevels(heightMap);
	int multiplication = MultiplyLargestBasins(heightMap, 3);

	heightMap.PrintData();
	heightMap.PrintLowPointsPositions();
	heightMap.PrintBasinsPositions();

	cout << "Sum of risk levels: " << sumOfRiskLevels << "\n";
	cout << "Multiplication of 3 largest basins sizes: " << multiplication << "\n";

	return 0;
}
