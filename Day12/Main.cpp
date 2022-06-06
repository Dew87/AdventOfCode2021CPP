#include <iostream>
#include "Node.h"

using namespace std;

template <typename T>
void DeleteVector(vector<T*> &vInput)
{
	for (size_t i = 0; i < vInput.size(); i++)
	{
		delete vInput[i];
	}
	vInput.clear();
}

Node* GetNodeFromVector(string ID, vector<Node*> &nodes)
{
	for (size_t i = 0; i < nodes.size(); i++)
	{
		if (ID == nodes[i]->ID)
		{
			// Return found node
			return nodes[i];
		}
	}

	// Node not found. Add new node to vector and return it
	Node *node = new Node(ID);
	nodes.push_back(node);
	return node;
}

void InputNodeGraph(vector<Node*> &vOutputNodes)
{
	cout << "Start of node graph input (X-Y Invalid input to end)\n";
	while (true)
	{
		string input;
		getline(cin, input);

		size_t i = input.find("-");
		if (i != string::npos)
		{
			string aID = input.substr(0, i);
			string bID = input.substr(i + 1);

			if (!aID.empty() && !bID.empty())
			{
				Node *aNode = GetNodeFromVector(aID, vOutputNodes);
				Node *bNode = GetNodeFromVector(bID, vOutputNodes);

				aNode->Neighbours.push_back(bNode);
				bNode->Neighbours.push_back(aNode);
				continue;
			}
		}
		break;
	}
	cout << "End of node graph input\n\n";
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

void PrintVector(const vector<Node*> &vInput, const char *vName, const char* separation)
{
	cout << "Start of " << vName << "[" << vInput.size() << "] print\n";
	if (0 < vInput.size())
	{
		for (size_t i = 0; i < vInput.size() - 1; i++)
		{
			cout << *vInput[i] << separation;
		}
		cout << *vInput[vInput.size() - 1] << "\n";
	}
	cout << "End of " << vName << " print\n\n";
}

int main()
{
	cout << "Advent of code 2021\n";
	cout << "Day 12: Passage Pathing\n";
	cout << "Program by David Erikssen\n\n";

	vector<Node*> nodes;

	InputNodeGraph(nodes);

	PrintVector(nodes, "nodes", "\n");

	DeleteVector(nodes);

	PrintVector(nodes, "nodes", "\n");

	return 0;
}
