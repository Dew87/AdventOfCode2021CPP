#include "Board.h"

using namespace std;

void OutputBoardRow(ostream &o, const Board &board, int row)
{
	if (0 <= row && row < board.size)
	{
		int rowIndex = row * board.size;
		for (int i = 0; i < board.size - 1; i++)
		{
			o << board.entries[rowIndex + i].number << " ";
		}
		o << board.entries[rowIndex + board.size - 1].number;
	}
}

Board::Board(vector<BoardEntry> entries, int size) : entries(entries), size(size)
{}

bool Board::CheckIfColumnHaveWon(int column) const
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (entries[(i * size) + column].active)
		{
			count++;
		}
	}
	return count == size;
}

bool Board::CheckIfRowHaveWon(int row) const
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (entries[(row * size) + i].active)
		{
			count++;
		}
	}
	return count == size;
}

int Board::Score(int number) const
{
	int sum = 0;
	for (size_t i = 0; i < entries.size(); i++)
	{
		if (!entries[i].active)
		{
			sum += entries[i].number;
		}
	}
	return sum * number;
}

ostream& operator << (ostream &o, const Board &board)
{
	if (0 < board.size)
	{
		for (int i = 0; i < board.size - 1; i++)
		{
			OutputBoardRow(o, board, i);
			o << "\n";
		}
		OutputBoardRow(o, board, board.size - 1);
	}
	return o;
}
