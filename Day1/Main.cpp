#include <iostream>
#include <vector>

using namespace std;

void InputScan(vector<int> &vOutput)
{
	cout << "Start of scan input (Invalid input to end)\n";
	while (true)
	{
		int i;
		cin >> i;
		if (cin.good())
		{
			vOutput.push_back(i);
		}
		else
		{
			break;
		}
	}
	cout << "End of scan input\n\n";
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

int VectorNumberOfIncreases(const vector<int> &vInput)
{
	int sum = 0;
	for (size_t i = 1; i < vInput.size(); i++)
	{
		if (vInput[i - 1] < vInput[i])
		{
			sum++;
		}
	}
	return sum;
}

void VectorSumsOfNumber(const vector<int> &vInput, vector<int> &vOutput, int number)
{
	if (number <= vInput.size())
	{
		for (int i = number - 1; i < vInput.size(); i++)
		{
			int sum = 0;
			for (int j = i + 1 - number; j <= i; j++)
			{
				sum += vInput[j];
			}
			vOutput.push_back(sum);
		}
	}
}

int main()
{
	cout << "Advent of code 2021\n";
	cout << "Day 1: Sonar Sweep\n";
	cout << "Program by David Erikssen\n\n";

	int number = 3;

	vector<int> scan;
	vector<int> scanSums;

	InputScan(scan);
	PrintVector(scan, "scan", "\n");

	VectorSumsOfNumber(scan, scanSums, number);
	PrintVector(scanSums, "scan sums", "\n");

	int scanIncreases = VectorNumberOfIncreases(scan);
	int scanSumsIncreases = VectorNumberOfIncreases(scanSums);

	cout << "Scan increases: " << scanIncreases << "\n";
	cout << "Scan sums of " << number << " increases: " << scanSumsIncreases << "\n";

	return 0;
}
