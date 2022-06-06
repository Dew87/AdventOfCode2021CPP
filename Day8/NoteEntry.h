#ifndef NOTE_ENTRY_H
#define NOTE_ENTRY_H

#include <ostream>
#include <string>
#include <vector>

struct NoteEntry
{
	NoteEntry(std::vector<std::string> signals, std::vector<std::string> output);
	int Decode() const;

	std::vector<std::string> signals;
	std::vector<std::string> output;
};

std::ostream& operator << (std::ostream &o, const NoteEntry &noteEntry);

#endif
