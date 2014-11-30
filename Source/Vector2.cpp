#include "Vector2.h"


Vector2::Vector2() : x(0), y(0)
{
}

Vector2::Vector2(int x_, int y_) : x(x_), y(y_)
{

}


Vector2::~Vector2()
{
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

const Vector2 Vector2::operator+(const Vector2& other)
{
	Vector2 result = *this;
	result += other;
	return result;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

const Vector2 Vector2::operator-(const Vector2& other)
{
	Vector2 result = *this;
	result -= other;
	return result;
}

Vector2& Vector2::operator*=(const int& other)
{
	x *= other;
	y *= other;
	return *this;
}

const Vector2 Vector2::operator*(const int& other)
{
	Vector2 result = *this;
	result *= other;
	return result;
}