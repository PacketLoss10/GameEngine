#pragma once

#include "Transform.h"

class Matrix
{
private:
	float data[3][3] = 
	{ 
	  {1.f,0.f,0.f},
	  {0.f,1.f,0.f},
	  {0.f,0.f,1.f} 
	};
public:
	Matrix(float r0c0, float r0c1, float r0c2, float r1c0, float r1c1, float r1c2, float r2c0, float r2c1, float r2c2);
	Matrix();

	float* operator[](size_t row)
	{
		return data[row];
	}
	const float* operator[](size_t row) const
	{
		return data[row];
	}

	Matrix operator*(const Matrix& rhs) const
	{
		Matrix result;

		for (int row = 0; row < 3; row++)
		{
			for (int collumn = 0; collumn < 3; collumn++)
			{
				result[row][collumn] =
					*this[row][0] * rhs[0][collumn] +
					*this[row][1] * rhs[1][collumn] +
					*this[row][2] * rhs[2][collumn];
			}
		}

		return result;
	}

	static Matrix identity();

	const FVector& get_position() const;
	void translate_by(FVector step);

	const FVector& get_forward() const;
	float get_rotation() const;
	void rotate_by(float angle, FVector origin);

	const FVector& get_scale() const;
	void scale_by(FVector scale, FVector origin);
};