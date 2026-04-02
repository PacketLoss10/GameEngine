#include "IntVector.h"

IntVector::IntVector(int x, int y) :x(x), y(y) {}

int IntVector::dot(const IntVector& other) const
{
	return x * other.x + y * other.y;
}

int IntVector::cross(const IntVector& other) const
{
	return x * other.y - y * other.x;
}

IntVector IntVector::component_wise_mult(const IntVector& other) const
{
	return IntVector(x * other.x, y * other.y);
}

IntVector IntVector::component_wise_div(const IntVector& other) const
{
	return IntVector(x / other.x, y / other.y);
}