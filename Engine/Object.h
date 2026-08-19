#pragma once
#include "Json.h"
#include <string>

using namespace std;

#define CLASS_PROTOTYPE(classname) virtual unique_ptr<Object> Clone() const { return make_unique<classname>(*this); }

namespace nu {
	class Object {
	public:
		Object() = default;
		virtual ~Object() = default;

		CLASS_PROTOTYPE(Object)

		const string& GetName() const { return m_name; }
		bool IsActive() const { return m_active; }
		void SetActive(bool active = true) { m_active = active; }

		virtual void Read(const nu::json::value_t& value) {
			JSON_READ_NAME(value, "name", m_name);
			JSON_READ_NAME(value, "active", m_active);
		}

	protected:
		string m_name;
		bool m_active = true;
	};
}