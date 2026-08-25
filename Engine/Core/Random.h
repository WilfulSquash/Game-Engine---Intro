#pragma once

#include <random>
#include <stdlib.h>

namespace nu {

	inline mt19937& Generator() {
		static random_device rd;
		static mt19937 generator(rd());
		return generator;
	}

	inline void SeedRandom(unsigned int seed) {
		Generator().seed(seed);
	}

	inline int RandomInt() {
		static uniform_int_distribution<int> dist;
		return dist(Generator());
	}

	/// <summary>
	/// Get Random Integer from 0 to max
	/// </summary>
	/// <param name="max"></param>
	/// <returns></returns>

	inline int RandomInt(int max) {
		uniform_int_distribution<int> dist(0, max - 1);
		return dist(Generator());
	}

	inline int RandomInt(int min, int max) {
		if (min > max) { swap(min, max); }
		uniform_int_distribution<int> dist(min, max);
		return dist(Generator());
	}

	inline float RandomFloat() {
		static uniform_real_distribution<float> dist(0.0f, 1.0f);
		return dist(Generator());
	}

	inline float RandomFloat(float max) {
		uniform_real_distribution<float> dist(0.0f, max);
		return dist(Generator());
	}	

	inline float RandomFloat(float min, float max) {
		if (min > max) { swap(min, max); }
		uniform_real_distribution<float> dist(min, max);
		return dist(Generator());
	}

	inline bool RandomBool() {
		static bernoulli_distribution dist(0.5f);
		return dist(Generator());
	}
}