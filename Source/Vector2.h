#pragma once
class Vector2
{
public:
	float x, y;

	Vector2();
	Vector2(float x_, float y_);
	Vector2(int x_, int y_);
	~Vector2();

	void rotate(float degrees);
	void normalize();
	float magnitude();

	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2& operator*=(const float& other);
	const Vector2 operator+(const Vector2& other);
	const Vector2 operator-(const Vector2& other);
	const Vector2 operator*(const float& other);
	const Vector2 operator*(const int& other);
};

