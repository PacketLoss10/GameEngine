#include "Matrix.h"

Matrix::Matrix(float r0c0, float r0c1, float r0c2, float r1c0, float r1c1, float r1c2, float r2c0, float r2c1, float r2c2)
{
	data[0][0] = r0c0;
	data[0][1] = r0c1;
	data[0][2] = r0c2;

	data[1][0] = r1c0;
	data[1][1] = r1c1;
	data[1][2] = r1c2;
	
	data[2][0] = r2c0;
	data[2][1] = r2c1;
	data[2][2] = r2c2;
}

Matrix::Matrix()
{
}

Matrix Matrix::identity = Matrix();

Matrix Matrix::inverse() const
{

	float det =
		data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1])
		- data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0])
		+ data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);

	if (det == 0.f)
	{
		return Matrix::identity;
	}

	float invDet = 1.0f / det;
	Matrix inverse;

	inverse[0][0] = (data[1][1] * data[2][2] - data[1][2] * data[2][1]) * invDet;
	inverse[0][1] = -(data[0][1] * data[2][2] - data[0][2] * data[2][1]) * invDet;
	inverse[0][2] = (data[0][1] * data[1][2] - data[0][2] * data[1][1]) * invDet;

	inverse[1][0] = -(data[1][0] * data[2][2] - data[1][2] * data[2][0]) * invDet;
	inverse[1][1] = (data[0][0] * data[2][2] - data[0][2] * data[2][0]) * invDet;
	inverse[1][2] = -(data[0][0] * data[1][2] - data[0][2] * data[1][0]) * invDet;

	inverse[2][0] = (data[1][0] * data[2][1] - data[1][1] * data[2][0]) * invDet;
	inverse[2][1] = -(data[0][0] * data[2][1] - data[0][1] * data[2][0]) * invDet;
	inverse[2][2] = (data[0][0] * data[1][1] - data[0][1] * data[1][0]) * invDet;

	return inverse;
}

Vector2 Matrix::get_position() const
{
	return Vector2(data[0][2], data[1][2]);
}

void Matrix::translate_by(const Vector2& step)
{
	Matrix translator;
	translator[2][0] = step.x;
	translator[2][1] = step.y;

	*this = translator * *this;
}

Vector2 Matrix::get_forward() const
{
	return Vector2(data[0][0], data[0][1]);
}

float Matrix::get_rotation() const
{
	return atan2f(data[0][1], data[0][0]);
}

void Matrix::rotate_by(float angle, const Vector2& origin)
{
	Matrix rotator;
	rotator[0][0] = cosf(angle);
	rotator[1][0] = -sinf(angle);
	rotator[0][1] = sinf(angle);
	rotator[1][1] = cosf(angle);
	Matrix translator1;
	translator1[2][0] = origin.x;
	translator1[2][1] = origin.y;
	Matrix translator2;
	translator2[2][0] = -origin.x;
	translator2[2][1] = -origin.y;

	*this = translator1 * rotator * translator2 * *this;
}

Vector2 Matrix::get_scale() const
{
	return Vector2(sqrtf(data[0][0] * data[0][0] + data[1][0] * data[1][0]), sqrtf(data[0][1] * data[0][1] + data[1][1]));
}

void Matrix::scale_by(const Vector2& scale, const Vector2& origin)
{
	Matrix scaler;
	scaler[0][0] = scale.x;
	scaler[1][1] = scale.y;
	Matrix translator1;
	translator1[2][0] = origin.x;
	translator1[2][1] = origin.y;
	Matrix translator2;
	translator2[2][0] = -origin.x;
	translator2[2][1] = -origin.y;

	*this = translator1 * scaler * translator2 * *this;
}