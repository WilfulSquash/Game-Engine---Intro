#pragma once

#include <string>
#include <iostream>

using namespace std;

namespace nu {
	inline string ToLower(const string& str) {
		string lower = str;

		for (auto& c : lower) {
			c = tolower(c);
		}
		return lower;
	}

	inline string ToUpper(const string& str) {
		string upper = str;

		for (auto& c : upper) {
			c = toupper(c);
		}
		return upper;
	}

	inline bool EqualsIgnoreCase(const string& str1, const string& str2) {
		if (str1.size() != str2.size()) return false;

		return ToLower(str1) == ToLower(str2);
	}
}