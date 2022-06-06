#ifndef VECTOR2I_H
#define VECTOR2I_H

#include <ostream>

struct Vector2I
{
	Vector2I();
	Vector2I(int x, int y);

	int x;
	int y;
};

Vector2I operator + (const Vector2I a, const Vector2I b);

std::ostream& operator << (std::ostream &o, const Vector2I &vector2D);

#endif
