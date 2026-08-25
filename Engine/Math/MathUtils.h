#pragma once

namespace nu {
	constexpr float PI = 3.14159265358979323846f;
	constexpr float TwoPI = 2 * 3.14159265358979323846f;
	constexpr float HalfPI = 3.14159265358979323846f / 2;

	constexpr float RadToDeg = 180.0f / PI;
	constexpr float DegToRad = PI / 180.0f;

	template <typename T>
	T Min(T a, T b) {
		if (a < b) { return a; }
		else return b;
	}
	template <typename T>
	T Max(T a, T b) {
		if (a > b) { return a; }
		else return b;
	}
	template <typename T>
	T Wrap(T min, T max, T value) {
		if (value > max) { value = min; }
		if (value < min) { value = max; }
		return value;
	}

	template <typename T>
	T Clamp(T min, T max, T value) {
		if (value > max) { value = max; }
		if (value < min) { value = min; }
		return value;
	}
}