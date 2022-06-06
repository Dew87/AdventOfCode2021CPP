#include "Vector2I.h"

using namespace std;

Vector2I::Vector2I() : x(0), y(0)
{}

Vector2I::Vector2I(int x, int y) : x(x), y(y)
{}

Vector2I operator + (const Vector2I a, const Vector2I b)
{
	return Vector2I(a.x + b.x, a.y + b.y);
}

ostream& operator << (ostream &o, const Vector2I &vector2I)
{
	return o << vector2I.x << "," << vector2I.y;
}
