#pragma once
#include <cmath>

namespace nu {
	struct Vector3 {

		union{
			struct { float x, y, z; };
			struct { float r, g, b; };
		};

		Vector3() = default;
		Vector3(float x, float y, float z) : x{ x }, y{ y }, z{z} {}
		Vector3(float v) : x{ v }, y{ v }, z{v} {}

		bool operator == (const Vector3& v) const { return this->x == v.x && this->y == v.y && this->z == v.z; }
		bool operator != (const Vector3& v) const { return this->x != v.x && this->y || v.y && this->z || v.z; }

		Vector3 operator + (const Vector3& v) const { return Vector3{ x + v.x, y + v.y, z + v.z }; }
		Vector3 operator - (const Vector3& v) const { return Vector3{ x - v.x, y - v.y, z - v.z }; }
		Vector3 operator * (const Vector3& v) const { return Vector3{ x * v.x, y * v.y, z * v.z }; }
		Vector3 operator / (const Vector3& v) const { return Vector3{ x / v.x, y / v.y, z / v.z }; }

		Vector3 operator + (float v) const { return Vector3{ this->x + v, this->y + v, this->z + v }; }
		Vector3 operator - (float v) const { return Vector3{ this->x - v, this->y - v, this->z - v }; }
		Vector3 operator * (float v) const { return Vector3{ this->x * v, this->y * v, this->z * v }; }
		Vector3 operator / (float v) const { return Vector3{ this->x / v, this->y / v, this->z / v }; }

		Vector3& operator += (const Vector3& v) { this->x += v.x, this->y += v.y, this->z += v.z; return *this; }
		Vector3& operator -= (const Vector3& v) { this->x -= v.x, this->y -= v.y, this->z -= v.z; return *this; }
		Vector3& operator *= (const Vector3& v) { this->x *= v.x, this->y *= v.y, this->z *= v.z; return *this; }
		Vector3& operator /= (const Vector3& v) { this->x /= v.x, this->y /= v.y, this->z /= v.z; return *this; }

		Vector3& operator += (float v) { this->x += v, this->y += v, this->z += v; return *this; }
		Vector3& operator -= (float v) { this->x -= v, this->y -= v, this->z -= v; return *this; }
		Vector3& operator *= (float v) { this->x *= v, this->y *= v, this->z *= v; return *this; }
		Vector3& operator /= (float v) { this->x /= v, this->y /= v, this->z /= v; return *this; }

		float LengthSqr() const {return (x * x) + (y * y) + (z * z);}
		float Length() const {return sqrt(LengthSqr());}
		Vector3 Normalized() const {return (*this) / Length();}
		float Dot(const Vector3& v) const {return (this->x * v.x) + (this->y * v.y) + (this->z * v.z);}
	};
	using Color = Vector3;
}