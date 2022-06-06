#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

const vector<char> SyntaxClose =
{
	')', ']', '}', '>'
};

const vector<int64_t> SyntaxCompletionScore =
{
	1, 2, 3, 4
};

const vector<int64_t> SyntaxCorruptScore =
{
	3, 57, 1197, 25137
};

const vector<char> SyntaxOpen =
{
	'(', '[', '{', '<'
};

int64_t CheckSyntaxError(string input, string &output)
{
	stack<char> syntacStack;

	for (size_t i = 0; i < input.size(); i++)
	{
		for (size_t j = 0; j < SyntaxOpen.size(); j++)
		{
			if (input[i] == SyntaxOpen[j])
			{
				syntacStack.push(input[i]);
			}
			else if (input[i] == SyntaxClose[j])
			{
				if (!syntacStack.empty())
				{
					char c = syntacStack.top();
					syntacStack.pop();

					if (c != SyntaxOpen[j])
					{
						for (size_t k = 0; k < SyntaxOpen.size(); k++)
						{
							if (c == SyntaxOpen[k])
							{
								cout << input << " - Expected " << SyntaxClose[k] << ", but found " << SyntaxClose[j] << " instead.\n";
							}
						}
						return SyntaxCorruptScore[j];
					}
				}
				else
				{
					cout << input << " - Missing opening syntax " << SyntaxOpen[j] << " for " << input[i] << "[" << i << "]\n";
					return 0;
				}
			}
		}
	}
	if (syntacStack.empty())
	{
		cout << input << " is valid\n";
		return 0;
	}
	else
	{
		string completion;
		while (!syntacStack.empty())
		{
			char c = syntacStack.top();
			syntacStack.pop();

			for (size_t i = 0; i < SyntaxClose.size(); i++)
			{
				if (c == SyntaxOpen[i])
				{
					completion += SyntaxClose[i];
				}
			}
		}
		cout << input << " - Complete by adding " << completion << ".\n";
		output = completion;
		return 0;
	}
}

void InputSyntax(vector<string> &vOutputData)
{
	cout << "Start of syntax input (Invalid input to end)\n";
	while (true)
	{
		string input;
		getline(cin, input);

		bool valid = false;
		for (size_t i = 0; i < input.size(); i++)
		{
			for (size_t j = 0; j < SyntaxOpen.size(); j++)
			{
				valid = valid || (input[i] == SyntaxOpen[j]) || (input[i] == SyntaxClose[j]);
			}
		}
		if (valid)
		{
			vOutputData.push_back(input);
		}
		else
		{
			break;
		}
	}
	cout << "End of syntax input\n\n";
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

void SyntaxValidation(const vector<string> &vInput)
{
	int64_t sumSyntaxCorruption = 0;
	vector<int64_t> completionScores;

	for (size_t i = 0; i < vInput.size(); i++)
	{
		string completion;
		int64_t score = CheckSyntaxError(vInput[i], completion);
		if (score != 0)
		{
			sumSyntaxCorruption += score;
		}
		else if (!completion.empty())
		{
			int64_t completionScore = 0;
			for (size_t j = 0; j < completion.size(); j++)
			{
				completionScore *= 5;
				for (size_t k = 0; k < SyntaxClose.size(); k++)
				{
					if (completion[j] == SyntaxClose[k])
					{
						completionScore += SyntaxCompletionScore[k];
					}
				}
			}
			completionScores.push_back(completionScore);
		}
	}

	int64_t completionScoreMedian = 0;
	if (!completionScores.empty())
	{
		sort(completionScores.begin(), completionScores.end());
		completionScoreMedian = completionScores[completionScores.size() / 2];
	}

	cout << "Total syntax corruption score: " << sumSyntaxCorruption << "\n";
	cout << "Median completion score: " << completionScoreMedian << "\n";
}

int main()
{
	cout << "Advent of code 2021\n";
	cout << "Day 10: Syntax Scoring\n";
	cout << "Program by David Erikssen\n\n";

	vector<string> syntax;

	InputSyntax(syntax);
	PrintVector(syntax, "syntax", "\n");

	SyntaxValidation(syntax);

	return 0;
}
