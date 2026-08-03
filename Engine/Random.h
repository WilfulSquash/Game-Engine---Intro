#pragma once

#include <stdlib.h>

namespace nu {

	inline int RandomInt() {
		return rand();
	}

	/// <summary>
	/// Get Random Integer from 0 to max
	/// </summary>
	/// <param name="max"></param>
	/// <returns></returns>

	inline int RandomInt(int max) {
		return rand() % max;
	}

	inline int RandomInt(int min, int max) {
		return min + RandomInt((max - min) + 1);
	}

	inline float RandomFloat() {
		return rand() / (float)RAND_MAX;
	}

	inline float RandomFloat(float max) {
		return RandomFloat() * max;
	}	

	inline float RandomFloat(float min, float max) {
		return min + RandomFloat() * (max - min);
	}
}