#include "Command.h"
#include "Vector2I.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Vector2I ExecuteCommandsNew(const vector<Command> &vInput)
{
	Vector2I move;
	int aim = 0;
	for (size_t i = 0; i < vInput.size(); i++)
	{
		if (vInput[i].type == "forward")
		{
			move = move + Vector2I(vInput[i].value, vInput[i].value * aim);
		}
		else if (vInput[i].type == "down")
		{
			aim += vInput[i].value;
		}
		else if (vInput[i].type == "up")
		{
			aim -= vInput[i].value;;
		}
	}
	return move;
}

Vector2I ExecuteCommandsOld(const vector<Command> &vInput)
{
	Vector2I move;
	for (size_t i = 0; i < vInput.size(); i++)
	{
		if (vInput[i].type == "forward")
		{
			move = move + Vector2I(vInput[i].value, 0);
		}
		else if (vInput[i].type == "down")
		{
			move = move + Vector2I(0, vInput[i].value);
		}
		else if (vInput[i].type == "up")
		{
			move = move + Vector2I(0, -vInput[i].value);
		}
	}
	return move;
}

void InputCommands(vector<Command> &vOutput)
{
	cout << "Start of commands input (forward X down X up X Invalid input to end)\n";
	while (true)
	{
		string type;
		int value;

		cin >> type;
		cin >> value;

		if ((type == "forward" || type == "down" || type == "up") && cin.good())
		{
			vOutput.push_back(Command(type, value));
		}
		else
		{
			break;
		}
	}
	cout << "End of command input\n\n";
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
	cout << "Day 2: Dive!\n";
	cout << "Program by David Erikssen\n\n";

	vector<Command> commands;
	InputCommands(commands);
	PrintVector(commands, "commands", "\n");

	Vector2I positionOld = ExecuteCommandsOld(commands);
	Vector2I positionNew = ExecuteCommandsNew(commands);

	int multiplyOld = positionOld.x * positionOld.y;
	int multiplyNew = positionNew.x * positionNew.y;

	cout << "Position old steering " << positionOld << "\n";
	cout << "Multiply old steering: " << multiplyOld << "\n\n";

	cout << "Position new steering " << positionNew << "\n";
	cout << "Multiply new steering: " << multiplyNew << "\n";

	return 0;
}
