#include "NoteEntry.h"
#include <algorithm>
#include <iostream>

/* Note seven-segment displays
* 
*   0:      1:      2:      3:      4:     5:      6:      7:      8:      9:
*  aaaa    ....    aaaa    aaaa    ....   aaaa    aaaa    aaaa    aaaa    aaaa
* b    c  .    c  .    c  .    c  b    c b    .  b    .  .    c  b    c  b    c
* b    c  .    c  .    c  .    c  b    c b    .  b    .  .    c  b    c  b    c
*  ....    ....    dddd    dddd    dddd   dddd    dddd    ....    dddd    dddd
* e    f  .    f  e    .  .    f  .    f .    f  e    f  .    f  e    f  .    f
* e    f  .    f  e    .  .    f  .    f .    f  e    f  .    f  e    f  .    f
*  gggg    ....    gggg    gggg    ....   gggg    gggg    ....    gggg    gggg
* 
* 0[6]: abcefg
* 1[2]: cf      (unique length)
* 2[5]: acdeg
* 3[5]: acdfg
* 4[4]: bcdf    (unique length)
* 5[5]: abdfg
* 6[6]: abdefg
* 7[3]: acf     (unique length)
* 8[7]: abcdefg (unique length)
* 9[6]: abcdfg
* 
* StringSum(0 -> 9)
* a count: 8
* b count: 6 (unique)
* c count: 8
* d count: 7
* e count: 4 (unique)
* f count: 9 (unique)
* g count: 7
* 
* Decode
* a: 7[3] - 1[2]
* b: StringSum(0 -> 9) count 6 (unique)
* c: StringSum(0 -> 9) count 8 - a
* d: StringSum(2,3,5[5] + 4[4]) count 4 (unique)
* e: StringSum(0 -> 9) count 4 (unique)
* f: StringSum(0 -> 9) count 9 (unique)
* g: StringSum(0 -> 9) count 7 - d
* 
* Note seven-segment displays */

using namespace std;

const vector<string> SevenSegmentDisplay =
{
	"abcefg",
	"cf",
	"acdeg",
	"acdfg",
	"bcdf",
	"abdfg",
	"abdefg",
	"acf",
	"abcdefg",
	"abcdfg"
};

string CharsInStringWithCount(string input, int number)
{
	sort(input.begin(), input.end());

	string result;
	for (char c = 'a'; c <= 'g'; c++)
	{
		if (count(input.begin(), input.end(), c) == number)
		{
			result += c;
		}
	}
	return result;
}

string operator - (const string a, const char c)
{
	string result = a;
	size_t i = result.find(c);
	if (i != string::npos)
	{
		result.erase(i, 1);
	}
	return result;
}

string operator - (const string a, const string b)
{
	string result = a;
	for (size_t i = 0; i < b.size(); i++)
	{
		result = result - b[i];
	}
	return result;
}

NoteEntry::NoteEntry(vector<string> signals, vector<string> output) : signals(signals), output(output)
{}

int NoteEntry::Decode() const
{
	string string1;
	string string7;
	string stringSum0To9;
	string stringSum2To5;
	for (size_t i = 0; i < signals.size(); i++)
	{
		stringSum0To9 += signals[i];
		switch (signals[i].size())
		{
		case 2:
			string1 = signals[i];
			break;
		case 3:
			string7 = signals[i];
			break;
		case 4:
		case 5:
			stringSum2To5 += signals[i];
			break;
		default:
			break;
		}
	}
	sort(stringSum0To9.begin(), stringSum0To9.end());
	sort(stringSum2To5.begin(), stringSum2To5.end());

	// Decode map. a = [0]. Check note above on decode procedure
	vector<char> decodeMap;
	decodeMap.push_back((string7 - string1)[0]);
	decodeMap.push_back(CharsInStringWithCount(stringSum0To9, 6)[0]);
	decodeMap.push_back((CharsInStringWithCount(stringSum0To9, 8) - decodeMap[0])[0]);
	decodeMap.push_back(CharsInStringWithCount(stringSum2To5, 4)[0]);
	decodeMap.push_back(CharsInStringWithCount(stringSum0To9, 4)[0]);
	decodeMap.push_back(CharsInStringWithCount(stringSum0To9, 9)[0]);
	decodeMap.push_back((CharsInStringWithCount(stringSum0To9, 7) - decodeMap[3])[0]);

	// Decoded string from original string
	vector<string> decodedOutput;
	for (size_t i = 0; i < output.size(); i++)
	{
		string s;
		for (size_t j = 0; j < output[i].size(); j++)
		{
			for (size_t k = 0; k < decodeMap.size(); k++)
			{
				if (output[i][j] == decodeMap[k])
				{
					s += 'a' + (int)k;
				}
			}
		}
		sort(s.begin(), s.end());
		decodedOutput.push_back(s);
	}

	// Make number string from decoded string
	string numberString;
	for (size_t i = 0; i < decodedOutput.size(); i++)
	{
		for (size_t j = 0; j < SevenSegmentDisplay.size(); j++)
		{
			if (decodedOutput[i] == SevenSegmentDisplay[j])
			{
				numberString += to_string(j);
			}
		}
	}

	// Return number string as an int
	try
	{
		return stoi(numberString);
	}
	catch (exception e)
	{
		cerr << "Can't convert decoded output " << numberString << " to int for entry: " << *this << "\n";
	}

	return -1;
}

ostream& operator << (ostream &o, const NoteEntry &noteEntry)
{
	if (0 < noteEntry.signals.size())
	{
		for (size_t i = 0; i < noteEntry.signals.size() - 1; i++)
		{
			o << noteEntry.signals[i] << " ";
		}
		o << noteEntry.signals[noteEntry.signals.size() - 1];
	}
	o << " | ";
	if (0 < noteEntry.output.size())
	{
		for (size_t i = 0; i < noteEntry.output.size() - 1; i++)
		{
			o << noteEntry.output[i] << " ";
		}
		o << noteEntry.output[noteEntry.output.size() - 1];
	}
	return o;
}
