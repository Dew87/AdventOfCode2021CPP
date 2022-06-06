#include "Line.h"

using namespace std;

Line::Line(Vector2I a, Vector2I b) : a(a), b(b)
{}

ostream& operator << (ostream &o, const Line &line)
{
	return o << line.a << " -> " << line.b;
}
