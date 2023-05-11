#include "Vector2i.h"

Vector2i::Vector2i() : x(0), y(0)
{
}

Vector2i::Vector2i(const int& x, const int& y) : x(x), y(y)
{
}

Vector2i::Vector2i(const Vector2i& rhs) : x(rhs.x), y(rhs.y)
{
}

Vector2i& Vector2i::operator=(const Vector2i& rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}

bool Vector2i::operator==(const Vector2i& rhs)
{
	return x == rhs.x && y == rhs.y;
}

Vector2i operator+(const Vector2i& lhs, const Vector2i rhs)
{
	Vector2i newVec(lhs);
	newVec.x += rhs.x;
	newVec.y += rhs.y;
	return newVec;
}

Vector2i operator-(const Vector2i& lhs, const Vector2i rhs)
{
	Vector2i newVec(lhs);
	newVec.x += rhs.x;
	newVec.y += rhs.y;
	return newVec;
}

Vector2i operator*(const int& num, const Vector2i vec)
{
	Vector2i newVec(vec);
	newVec.x *= num;
	newVec.y *= num;
	return newVec;
}

Vector2i operator*(const Vector2i& vec, const int num)
{
	Vector2i newVec(vec);
	newVec.x *= num;
	newVec.y *= num;
	return newVec;
}
