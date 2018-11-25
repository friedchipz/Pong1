#pragma once

class Vector2d {
public:
	float x, y;
	Vector2d(float x = 0, float y = 0);
	/*Vector2d(Vector2d && src);
	Vector2d & operator=(Vector2d && src);*/
	Vector2d normalize();
	float length();
};

Vector2d operator+(const Vector2d & v1, const Vector2d & v2);
Vector2d operator-(const Vector2d & v1, const Vector2d & v2);
Vector2d operator*(const Vector2d & v1, const Vector2d & v2);
Vector2d operator*(const Vector2d & v1, const float f);
