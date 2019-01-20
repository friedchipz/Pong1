#include "Maths.h"
#include <math.h>

Vector2d::Vector2d(float x, float y) :x(x), y(y) {}
/*Vector2d::Vector2d(Vector2d && src){
	x = src.x;
	y = src.y;
}

Vector2d & Vector2d::operator=(Vector2d && src) {
	if (&src == this) return *this;
	x = src.x;
	y = src.y;
}*/

float Vector2d::length() {
	return sqrt(x * x + y * y);
}

Vector2d Vector2d::normalize() {
	float length = this->length();
	if (length == 0) return Vector2d(0, 0);
	return Vector2d(x/length,y/length);
}

Vector2d operator+(const Vector2d & v1, const Vector2d & v2) {
	return Vector2d(v1.x + v2.x, v1.y + v2.y);
}

Vector2d operator-(const Vector2d & v1, const Vector2d & v2) {
	return Vector2d(v1.x - v2.x, v1.y - v2.y);
}

Vector2d operator*(const Vector2d & v1, const Vector2d & v2) {
	return Vector2d(v1.x * v2.x, v1.y * v2.y);
}

Vector2d operator*(const Vector2d & v1, const float f) {
	return Vector2d(v1.x * f, v1.y * f);
}