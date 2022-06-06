#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

template <typename T>
void InputLanternfishSpawning(vector<T> &vOutput)
{
	cout << "Start of lanternfish spawning input (X,X,... Invalid input to end)\n";
	string input;
	cin >> input;

	size_t i = input.find(',');
	while (i != string::npos)
	{
		string inputSubstring = input.substr(0, i);
		input = input.substr(i + 1);
		try
		{
			int number = stoi(inputSubstring);
			while ((int)vOutput.size() < number + 1)
			{
				vOutput.push_back(0);
			}
			vOutput[number]++;
		}
		catch (exception e)
		{ }
		i = input.find(',');
	}
	if (input.size() != 0)
	{
		try
		{
			int number = stoi(input);
			while ((int)vOutput.size() < number + 1)
			{
				vOutput.push_back(0);
			}
			vOutput[number]++;
		}
		catch (exception e)
		{ }
	}
	cout << "End of lanternfish spawning input\n\n";
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

template <typename T>
T PropagateLanternfishSpawning(const vector<T> &vInput, int generations, int parentSpawnDelay, int babySpawnDelay)
{
	vector<T> currentGenaration = vInput;
	vector<T> nextGeneration;

	if (0 < currentGenaration.size())
	{
		for (int i = 0; i < generations; i++)
		{
			// Decrement spawn value for none spawning fish
			for (size_t j = 1; j < currentGenaration.size(); j++)
			{
				while (nextGeneration.size() < j)
				{
					nextGeneration.push_back(0);
				}
				nextGeneration[j - 1] += currentGenaration[j];
			}

			// Spawn new baby fish and add old parent fish with new spawn value
			while (nextGeneration.size() < (size_t)(parentSpawnDelay < babySpawnDelay ? babySpawnDelay : parentSpawnDelay) + 1)
			{
				nextGeneration.push_back(0);
			}
			nextGeneration[babySpawnDelay] += currentGenaration[0];
			nextGeneration[parentSpawnDelay] += currentGenaration[0];

			// Set next generation to current
			currentGenaration = nextGeneration;
			nextGeneration.clear();
		}
	}

	stringstream ss;
	ss << "Generation(" << generations << ")";
	PrintVector(currentGenaration, ss.str().c_str(), "\n");

	T sum = 0;
	for (size_t i = 0; i < currentGenaration.size(); i++)
	{
		sum += currentGenaration[i];
	}
	return sum;
}

int main()
{
	cout << "Advent of code 2021\n";
	cout << "Day 6: Lanternfish\n";
	cout << "Program by David Erikssen\n\n";

	vector<int64_t> lanternfishes;

	InputLanternfishSpawning(lanternfishes);

	int64_t lanternfishCount80days = PropagateLanternfishSpawning(lanternfishes, 80, 6, 8);
	cout << lanternfishCount80days << " lanternfishes after 80 days\n\n";

	int64_t lanternfishCount256days = PropagateLanternfishSpawning(lanternfishes, 256, 6, 8);
	cout << lanternfishCount256days << " lanternfishes after 256 days\n\n";

	return 0;
}
