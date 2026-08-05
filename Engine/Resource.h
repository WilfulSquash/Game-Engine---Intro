#pragma once

#include <memory>

using namespace std;

namespace nu {
	class Resource {
	public:
		Resource() = default;
		virtual ~Resource() = default;
	};

	template <typename T = Resource>
	using res_t = shared_ptr<T>;
}