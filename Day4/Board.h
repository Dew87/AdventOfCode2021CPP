#ifndef BOARD_H
#define BOARD_H

#include "BoardEntry.h"
#include <ostream>
#include <vector>

struct Board
{
	Board(std::vector<BoardEntry> entries, int size);
	bool CheckIfColumnHaveWon(int column) const;
	bool CheckIfRowHaveWon(int row) const;
	int Score(int number) const;

	std::vector<BoardEntry> entries;
	int size;
};

std::ostream& operator << (std::ostream &o, const Board &board);

#endif
