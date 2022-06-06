#ifndef NODE_H
#define NODE_H

#include <ostream>
#include <string>
#include <vector>

struct Node
{
	Node(std::string ID);

	bool isLarge;
	std::string ID;
	std::vector<Node*> Neighbours;
};

std::ostream& operator << (std::ostream &o, const Node &node);

#endif
