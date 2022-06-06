#include "Board.h"
#include "BoardWin.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void InputBoards(vector<Board> &vOutput, int boardSize)
{
	cout << "Start of board numbers input (Invalid input to end)\n";
	vector<BoardEntry> boardInput;
	while (true)
	{
		int i;
		cin >> i;
		if (cin.good())
		{
			boardInput.push_back(BoardEntry(i));
			if (boardInput.size() == (size_t)boardSize * (size_t)boardSize)
			{
				vOutput.push_back(Board(boardInput, boardSize));
				boardInput.clear();
			}
		}
		else
		{
			break;
		}
	}
	cout << "End of board numbers input\n\n";
}

void InputDrawnNumbers(vector<int> &vOutput)
{
	cout << "Start of drawn numbers input (X,X,... Invalid input to end)\n";
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
	cout << "End of drawn numbers input\n\n";
}

void PlayBingoFirstToWin(const vector<int> &vInputDrawnNumbers, const vector<Board> &vInputBoards)
{
	vector<Board> boards = vInputBoards;
	vector<BoardWin> boardWin;

	// Find first winning boards and winning number
	cout << "Play bingo first to win\n";
	for (size_t i = 0; i < vInputDrawnNumbers.size() && boardWin.size() == 0; i++)
	{
		cout << "Number drawn: " << vInputDrawnNumbers[i] << "\n";
		for (size_t j = 0; j < boards.size(); j++)
		{
			for (size_t k = 0; k < boards[j].entries.size(); k++)
			{
				if (boards[j].entries[k].number == vInputDrawnNumbers[i])
				{
					boards[j].entries[k].active = true;
					int column = (int)k % boards[j].size;
					int row = (int)k / boards[j].size;

					bool wonColumn = boards[j].CheckIfColumnHaveWon(column);
					bool wonRow = boards[j].CheckIfRowHaveWon(row);
					if (wonColumn || wonRow)
					{
						boardWin.push_back(BoardWin((int)j, vInputDrawnNumbers[i]));
					}
				}
			}
		}
	}
	if (boardWin.size() > 0)
	{
		for (size_t i = 0; i < boardWin.size(); i++)
		{
			int index = boardWin[i].index;
			int number = boardWin[i].number;
			cout << "Winning board: " << index << "\n";
			cout << "Winning number: " << number << "\n";
			cout << "Score: " << boards[index].Score(number) << "\n";
			cout << boards[index] << "\n\n";
		}
	}
	else
	{
		cout << "No winning boards :(\n";
	}
}

void PlayBingoLastToWin(const vector<int> &vInputDrawnNumbers, const vector<Board> &vInputBoards)
{
	vector<Board> boards = vInputBoards;
	vector<BoardWin> boardWin;

	// Draw all numbers and record all winning boards and winning numbers
	cout << "Play bingo last to win\n";
	for (size_t i = 0; i < vInputDrawnNumbers.size(); i++)
	{
		for (size_t j = 0; j < boards.size(); j++)
		{
			for (size_t k = 0; k < boards[j].entries.size(); k++)
			{
				if (boards[j].entries[k].number == vInputDrawnNumbers[i])
				{
					boards[j].entries[k].active = true;
					int column = (int)k % boards[j].size;
					int row = (int)k / boards[j].size;

					bool wonColumn = boards[j].CheckIfColumnHaveWon(column);
					bool wonRow = boards[j].CheckIfRowHaveWon(row);
					if (wonColumn || wonRow)
					{
						boardWin.push_back(BoardWin((int)j, vInputDrawnNumbers[i]));
					}
				}
			}
		}
	}
	if (boardWin.size() > 0)
	{
		// Reverse winning order
		reverse(boardWin.begin(), boardWin.end());

		// Check if board have already won before, if so check next
		int index = 0;
		for (size_t i = 0; i < boardWin.size(); i++)
		{
			int count = 0;
			for (size_t j = i + 1; j < boardWin.size(); j++)
			{
				if (boardWin[i].index == boardWin[j].index)
				{
					count++;
				}
			}
			if (count == 0)
			{
				index = boardWin[i].index;
				break;
			}
		}

		Board board = vInputBoards[index];
		bool boardWon = false;
		int number = 0;

		// Draw numbers until last winning board wins
		for (size_t i = 0; i < vInputDrawnNumbers.size() && !boardWon; i++)
		{
			number = vInputDrawnNumbers[i];
			cout << "Number drawn: " << number << "\n";
			for (size_t j = 0; j < board.entries.size(); j++)
			{
				if (board.entries[j].number == number)
				{
					board.entries[j].active = true;
					int column = (int)j % board.size;
					int row = (int)j / board.size;

					bool wonColumn = board.CheckIfColumnHaveWon(column);
					bool wonRow = board.CheckIfRowHaveWon(row);
					boardWon = wonColumn || wonRow;
				}
			}
		}

		cout << "Last Winning board: " << index << "\n";
		cout << "Winning number: " << number << "\n";
		cout << "Score: " << board.Score(number) << "\n";
		cout << board << "\n\n";
	}
	else
	{
		cout << "No last winning boards :(\n";
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

int main()
{
	cout << "Advent of code 2021\n";
	cout << "Day 4: Giant Squid\n";
	cout << "Program by David Erikssen\n\n";

	const int boardSize = 5;

	vector<int> drawnNumbers;
	vector<Board> boards;

	InputDrawnNumbers(drawnNumbers);
	InputBoards(boards, boardSize);

	PrintVector(drawnNumbers, "drawn numbers", ",");
	PrintVector(boards, "boards", "\n\n");

	PlayBingoFirstToWin(drawnNumbers, boards);
	PlayBingoLastToWin(drawnNumbers, boards);

	return 0;
}
