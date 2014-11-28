#pragma once
class Vector2
{
public:
	int x, y;

	Vector2();
	Vector2(int x_, int y_);
	~Vector2();

	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	const Vector2 operator+(const Vector2& other);
	const Vector2 operator-(const Vector2& other);
};

