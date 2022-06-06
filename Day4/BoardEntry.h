#ifndef BOARD_ENTRY_H
#define BOARD_ENTRY_H

struct BoardEntry
{
	BoardEntry(int number);

	bool active;
	int number;
};

#endif
