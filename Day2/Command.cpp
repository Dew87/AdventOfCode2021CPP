#include "Command.h"

using namespace std;

Command::Command(string type, int value) : type(type), value(value)
{}

ostream& operator << (ostream &o, const Command &command)
{
	return o << command.type << ' ' << command.value;
}
