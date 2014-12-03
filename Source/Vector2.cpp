#define _USE_MATH_DEFINES

#include "Vector2.h"
#include <cmath>
#include <math.h>

float deg2rad(float degrees){ return degrees * (float)M_PI / 180; }

Vector2::Vector2() : x(0), y(0)
{
}

Vector2::Vector2(float x_, float y_) : x(x_), y(y_)
{

}

Vector2::Vector2(int x_, int y_) : x(static_cast<float>(x_)), y(static_cast<float>(y_))
{

}

Vector2::~Vector2()
{
}

void Vector2::rotate(float degrees)
{
	float preMag = magnitude();

	float rads = deg2rad(degrees);

	float px = cos(rads)*x + -sin(rads)*y;
	float py = sin(rads)*x + cos(rads)*y;
	x = px;
	y = py;

	normalize();
	
	x *= preMag;
	y *= preMag;
}

void Vector2::normalize()
{
	float mag = magnitude();

	x /= mag;
	y /= mag;
}

float Vector2::magnitude()
{
	return sqrtf(x*x + y*y);
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

Vector2& Vector2::operator*=(const float& other)
{
	x *= other;
	y *= other;
	return *this;
}

const Vector2 Vector2::operator*(const float& other)
{
	Vector2 result = *this;
	result *= other;
	return result;
}

const Vector2 Vector2::operator*(const int& other)
{
	Vector2 result = *this;
	result *= static_cast<float>(other);
	return result;
}