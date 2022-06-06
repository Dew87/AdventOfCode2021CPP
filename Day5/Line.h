#ifndef LINE_H
#define LINE_H

#include "Vector2I.h"
#include <ostream>

struct Line
{
	Line(Vector2I a, Vector2I b);

	Vector2I a;
	Vector2I b;
};

std::ostream& operator << (std::ostream &o, const Line &line);

#endif
