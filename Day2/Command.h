#ifndef COMMAND_H
#define COMMAND_H

#include <ostream>
#include <string>

struct Command
{
	Command(std::string type, int value);

	std::string type;
	int value;
};

std::ostream& operator << (std::ostream &o, const Command &command);

#endif
