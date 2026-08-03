#pragma once
#include <cmath>
#include <cassert>

namespace nu {
	struct Vector2 {
		float x, y;
		Vector2() = default;
		Vector2(float x, float y) : x{ x }, y{ y } {}
		Vector2(float v) : x{ v }, y{ v } {}

		float operator[](unsigned int index) const { assert(index < 2); return (&x)[index]; }
		float& operator[](unsigned int index) { assert(index < 2); return (&x)[index]; }

		bool operator == (const Vector2& v) const {return this->x == v.x && this->y == v.y;}
		bool operator != (const Vector2& v) const {return this->x != v.x && this->y || v.y;}

		Vector2 operator + (const Vector2& v) const { return Vector2{ x + v.x, y + v.y };}
		Vector2 operator - (const Vector2& v) const { return Vector2{ x - v.x, y - v.y };}
		Vector2 operator * (const Vector2& v) const { return Vector2{ x * v.x, y * v.y };}
		Vector2 operator / (const Vector2& v) const { return Vector2{ x / v.x, y / v.y };}

		Vector2 operator + (float v) const { return Vector2{ this->x + v, this->y + v };}
		Vector2 operator - (float v) const { return Vector2{ this->x - v, this->y - v };}
		Vector2 operator * (float v) const { return Vector2{ this->x * v, this->y * v };}
		Vector2 operator / (float v) const { return Vector2{ this->x / v, this->y / v };}

		Vector2& operator += (const Vector2& v) {this->x += v.x, this->y += v.y;return *this;}
		Vector2& operator -= (const Vector2& v) {this->x -= v.x, this->y -= v.y;return *this;}
		Vector2& operator *= (const Vector2& v) {this->x *= v.x, this->y *= v.y;return *this;}
		Vector2& operator /= (const Vector2& v) {this->x /= v.x, this->y /= v.y;return *this;}

		Vector2& operator += (float v) { this->x += v, this->y += v; return *this; }
		Vector2& operator -= (float v) { this->x -= v, this->y -= v; return *this; }
		Vector2& operator *= (float v) { this->x *= v, this->y *= v; return *this; }
		Vector2& operator /= (float v) { this->x /= v, this->y /= v; return *this; }

		float LengthSqr() const{ return (x * x) + (y * y); }
		float Length() const{ return sqrt(LengthSqr()); }
		Vector2 Normalized() const {return (*this) / Length(); }
		float Dot(const Vector2& v) const {return (this->x * v.x) + (this->y * v.y);}
		float Angle() const { return atan2(this->y, this->x); }
		float AngleBetween(const Vector2& v) const { return acos(Dot(v)); }
		Vector2 Rotate(float radians) { 
			
			float x = this->x * cos(radians) - this->y * sin(radians);
			float y = this->x * sin(radians) + this->y * cos(radians);

			return {x, y};
		}
	};
}