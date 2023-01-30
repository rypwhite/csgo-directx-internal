#pragma once

typedef float vec_t;
class Vector
{
public:
	float x, y, z;
	Vector(void);
	Vector(float X, float Y, float Z);
};

class QAngle
{
public:
	// Members
	float x, y, z;

	// Construction/destruction
	QAngle(void);
	QAngle(float X, float Y, float Z);
};

class matrix3x4_t
{
public:
	matrix3x4_t() {}
	matrix3x4_t(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23)
	{
		flMatVal[0][0] = m00;	flMatVal[0][1] = m01; flMatVal[0][2] = m02; flMatVal[0][3] = m03;
		flMatVal[1][0] = m10;	flMatVal[1][1] = m11; flMatVal[1][2] = m12; flMatVal[1][3] = m13;
		flMatVal[2][0] = m20;	flMatVal[2][1] = m21; flMatVal[2][2] = m22; flMatVal[2][3] = m23;
	}

	float flMatVal[3][4];
};

class VMatrix
{
public:

	VMatrix();
	VMatrix(
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33
	);

	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	VMatrix(const Vector& forward, const Vector& left, const Vector& up);

	// Construct from a 3x4 matrix
	VMatrix(const matrix3x4_t& matrix3x4);
};