#pragma once

namespace structs
{
	struct Vector3
	{
	public:
		float x;
		float y;
		float z;

		Vector3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vector3()
		{
			this->x = 0.0f;
			this->y = 0.0f;
			this->z = 0.0f;
		}

		Vector3 operator+(const Vector3& other) const
		{
			return Vector3(x + other.x, y + other.y, z + other.z);
		}

		Vector3 operator-(const Vector3& other) const
		{
			return Vector3(x - other.x, y - other.y, z - other.z);
		}

		Vector3 operator*(const Vector3& other) const
		{
			return Vector3(x * other.x, y * other.y, z * other.z);
		}
	};
}