#include <iostream>
#include <string>
#include <vector>

using namespace std;

int CountNumberOfCharOnIndex(const vector<string> &vInput, char c, size_t index)
{
	int count = 0;
	for (size_t i = 0; i < vInput.size(); i++)
	{
		if (vInput[i][index] == c)
		{
			count++;
		}
	}
	return count;
}

size_t MaxStringLength(const vector<string> &vInput)
{
	size_t max = 0;
	for (size_t i = 0; i < vInput.size(); i++)
	{
		max = max < vInput[i].size() ? vInput[i].size() : max;
	}
	return max;
}

int CO2ScrubberRating(const vector<string> &vInput, size_t numberOfBits)
{
	vector<string> input = vInput;
	for (size_t i = 0; i < numberOfBits; i++)
	{
		int count = CountNumberOfCharOnIndex(input, '0', i);
		char c = input.size() - count < count ? '1' : '0';

		vector<string> inputNext;
		for (size_t j = 0; j < input.size(); j++)
		{
			if (input[j][i] == c)
			{
				inputNext.push_back(input[j]);
			}
		}
		if (inputNext.size() == 1)
		{
			return stoi(inputNext[0], nullptr, 2);
		}
		input = inputNext;
	}
	return 0;
}

int EpsilonRate(const vector<string> &vInput, size_t numberOfBits)
{
	int result = 0;
	for (size_t i = 0; i < numberOfBits; i++)
	{
		int count = CountNumberOfCharOnIndex(vInput, '1', i);
		if (count < vInput.size() - count)
		{
			result += 1 << ((int)numberOfBits - 1 - (int)i);
		}
	}
	return result;
}

int GammaRate(const vector<string> &vInput, size_t numberOfBits)
{
	int result = 0;
	for (size_t i = 0; i < numberOfBits; i++)
	{
		int count = CountNumberOfCharOnIndex(vInput, '1', i);
		if (vInput.size() - count < count)
		{
			result += 1 << ((int)numberOfBits - 1 - (int)i);
		}
	}
	return result;
}

void InputBinaryCode(vector<string> &vOutput)
{
	cout << "Start of binary code input (Invalid input to end)\n";
	while (true)
	{
		string input;
		cin >> input;
		try
		{
			int i = stoi(input, nullptr, 2);
			vOutput.push_back(input);
		}
		catch (exception e)
		{
			break;
		}
	}
	cout << "End of binary code input\n\n";
}

int OxygenGeneratorRating(const vector<string> &vInput, size_t numberOfBits)
{
	vector<string> input = vInput;
	for (size_t i = 0; i < numberOfBits; i++)
	{
		int count = CountNumberOfCharOnIndex(input, '1', i);
		char c = count < input.size() - count ? '0' : '1';

		vector<string> inputNext;
		for (size_t j = 0; j < input.size(); j++)
		{
			if (input[j][i] == c)
			{
				inputNext.push_back(input[j]);
			}
		}
		if (inputNext.size() == 1)
		{
			return stoi(inputNext[0], nullptr, 2);
		}
		input = inputNext;
	}
	return 0;
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
	cout << "Day 3: Binary Diagnostic\n";
	cout << "Program by David Erikssen\n\n";

	vector<string> code;

	InputBinaryCode(code);
	PrintVector(code, "binary code", "\n");

	const size_t numberOfBits = MaxStringLength(code);

	int gammaRate = GammaRate(code, numberOfBits);
	int epsilonRate = EpsilonRate(code, numberOfBits);
	int powerConsumption = epsilonRate * gammaRate;

	int oxygenGeneratorRating = OxygenGeneratorRating(code, numberOfBits);
	int co2ScrubberRating = CO2ScrubberRating(code, numberOfBits);
	int lifeSupportRating = oxygenGeneratorRating * co2ScrubberRating;

	cout << "Gamma rate: " << gammaRate << '\n';
	cout << "Epsilon rate: " << epsilonRate << '\n';
	cout << "Power consumption: " << powerConsumption << "\n\n";

	cout << "Oxygen generator rating: " << oxygenGeneratorRating << "\n";
	cout << "CO2 scrubber rating: " << co2ScrubberRating << "\n";
	cout << "Life support rating: " << lifeSupportRating << "\n";

	return 0;
}
