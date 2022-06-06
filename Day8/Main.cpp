#include "NoteEntry.h"
#include <algorithm>
#include <iostream>

using namespace std;

void SplitString(string sInput, vector<string> &vOutputSubstrings, char separator)
{
	size_t i = sInput.find(separator);
	while (i != string::npos)
	{
		string inputSubString = sInput.substr(0, i);
		sort(inputSubString.begin(), inputSubString.end());
		if (!inputSubString.empty())
		{
			vOutputSubstrings.push_back(inputSubString);
		}
		sInput = sInput.substr(i + 1);
		i = sInput.find(separator);
	}
	if (sInput.size() != 0)
	{
		vOutputSubstrings.push_back(sInput);
	}
}

int CountSizeInNoteEntryOutput(const vector<NoteEntry> &vInput, int size)
{
	int sum = 0;
	for (size_t i = 0; i < vInput.size(); i++)
	{
		for (size_t j = 0; j < vInput[i].output.size(); j++)
		{
			if (vInput[i].output[j].size() == size)
			{
				sum++;
			}
		}
	}
	return sum;
}

void InputNoteEntries(vector<NoteEntry> &vOutput)
{
	cout << "Start of note entries input (X X X X X X X X X X | X X X X Invalid input to end)\n";
	while (true)
	{
		string input;
		getline(cin, input);

		size_t i = input.find("|");
		if (i != string::npos)
		{
			vector<string> signals;
			vector<string> output;

			SplitString(input.substr(0, i), signals, ' ');
			SplitString(input.substr(i + 1), output, ' ');

			bool aValid = signals.size() == 10;
			bool bValid = output.size() == 4;

			if (aValid && bValid)
			{
				vOutput.push_back(NoteEntry(signals, output));
				continue;
			}
		}
		break;
	}
	cout << "End of note entries input\n\n";
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

int SumOfDecodedEntries(const vector<NoteEntry> &noteEntries)
{
	int sum = 0;
	for (size_t i = 0; i < noteEntries.size(); i++)
	{
		sum += noteEntries[i].Decode();
	}
	return sum;
}

int main()
{
	cout << "Advent of code 2021\n";
	cout << "Day 8: Seven Segment Search\n";
	cout << "Program by David Erikssen\n\n";

	vector<NoteEntry> noteEntries;

	InputNoteEntries(noteEntries);

	PrintVector(noteEntries, "note entries", "\n");

	int Count1 = CountSizeInNoteEntryOutput(noteEntries, 2);
	int Count4 = CountSizeInNoteEntryOutput(noteEntries, 4);
	int Count7 = CountSizeInNoteEntryOutput(noteEntries, 3);
	int Count8 = CountSizeInNoteEntryOutput(noteEntries, 7);
	int CountEasyDigits = Count1 + Count4 + Count7 + Count8;

	cout << "Number of 1: " << Count1 << "\n";
	cout << "Number of 4: " << Count4 << "\n";
	cout << "Number of 7: " << Count7 << "\n";
	cout << "Number of 8: " << Count8 << "\n";
	cout << "Easy digits (1,4,7,8) count: " << CountEasyDigits << "\n";

	int sum = SumOfDecodedEntries(noteEntries);
	cout << "Decoded sum: " << sum << "\n";

	return 0;
}
