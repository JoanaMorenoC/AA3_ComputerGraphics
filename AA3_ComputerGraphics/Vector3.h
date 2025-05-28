#pragma once
#include <cmath>

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3(float newX, float newY, float newZ)
	{
		x = newX;
		y = newY;
		z = newZ;
	}

	float length() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	Vector3 Cross(const Vector3& other) const
	{
		return Vector3(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x);
	}

	Vector3 Normalized() const
	{
		float len = length();
		if (len == 0)
			return Vector3(0, 0, 0);
		return Vector3(x / len, y / len, z / len);
	}

	Vector3 operator+(const Vector3& other) const
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	Vector3& operator+=(const Vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vector3& operator-=(const Vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vector3 operator*(const float& other) const
	{
		return Vector3(x * other, y * other, z * other);
	}
};