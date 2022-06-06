#include <iostream>
#include <string>
#include <vector>

using namespace std;

int EscalationSum(int number)
{
	int sum = 0;
	for (int i = 1; i <= number; i++)
	{
		sum += i;
	}
	return sum;
}

void VectorMinMax(const vector<int> &vInput, int &outputMin, int &outputMax)
{
	if (0 < vInput.size())
	{
		outputMin = INT32_MAX;
		outputMax = INT32_MIN;

		for (size_t i = 0; i < vInput.size(); i++)
		{
			outputMin = vInput[i] < outputMin ? vInput[i] : outputMin;
			outputMax = outputMax < vInput[i] ? vInput[i] : outputMax;
		}
	}
}

void AlignCrabSubmarines(const vector<int> &vInput)
{
	if (0 < vInput.size())
	{
		int firstPosition;
		int lastPosition;
		int leastSumNew = INT32_MAX;
		int leastSumOld = INT32_MAX;
		int leastSumPositionNew = 0;
		int leastSumPositionOld = 0;
		VectorMinMax(vInput, firstPosition, lastPosition);

		for (int i = firstPosition; i <= lastPosition; i++)
		{
			int sumNew = 0;
			int sumOld = 0;

			for (size_t j = 0; j < vInput.size(); j++)
			{
				sumNew += EscalationSum(abs(vInput[j] - i));
				sumOld += abs(vInput[j] - i);
			}

			if (sumNew < leastSumNew)
			{
				leastSumNew = sumNew;
				leastSumPositionNew = i;
			}
			if (sumOld < leastSumOld)
			{
				leastSumOld = sumOld;
				leastSumPositionOld = i;
			}
		}

		cout << "Old cheapest fuel total " << leastSumOld << " on position " << leastSumPositionOld << "\n";
		cout << "New cheapest fuel total " << leastSumNew << " on position " << leastSumPositionNew << "\n";
	}
	else
	{
		cout << "No crab submarines to align\n";
	}
}

void InputCrabSubmarines(vector<int> &vOutput)
{
	cout << "Start of crab submarines input (X,X,... Invalid input to end)\n";
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
			vOutput.push_back(number);
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
			vOutput.push_back(number);
		}
		catch (exception e)
		{ }
	}
	cout << "End of crab submarines input\n\n";
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
	cout << "Day 7: The Treachery of Whales\n";
	cout << "Program by David Erikssen\n\n";

	vector<int> crabSubmarines;

	InputCrabSubmarines(crabSubmarines);
	PrintVector(crabSubmarines, "Crab Submarines", "\n");

	AlignCrabSubmarines(crabSubmarines);

	return 0;
}
