#include "Node.h"

using namespace std;

Node::Node(string ID) : ID(ID), isLarge(!ID.empty() && isupper(ID[0]))
{}

ostream& operator << (ostream &o, const Node &node)
{
	string nodeSize = node.isLarge ? "is Large" : "is small";
	o << node.ID << "[" << node.Neighbours.size() << "] " << nodeSize << "\n";
	if (0 < node.Neighbours.size())
	{
		for (size_t i = 0; i < node.Neighbours.size() - 1; i++)
		{
			o << "\t" << node.Neighbours[i]->ID << "\n";
		}
		o << "\t" << node.Neighbours[node.Neighbours.size() - 1]->ID;
	}
	return o;
}
