#pragma once
#include "Resource.h"
#include "Singleton.h"

#include <map>
#include <string>
#include <iostream>

using namespace std;

namespace nu {
	class ResourceManager : public Singleton<ResourceManager>{
	public:
		template <typename T, typename ... Args>
		res_t<T> Get(const string& name, Args&& ... args);

	private:
		map<string, res_t<Resource>> m_resources;
	};

	template<typename T, typename ...Args>
	inline res_t<T> ResourceManager::Get(const string& name, Args && ...args)
	{
		auto iter = m_resources.find(name);
		//check if resource exists
		if (iter != m_resources.end()) {
			auto base = iter->second; // return existing resource
			auto resource = dynamic_pointer_cast<T>(base);

			if (resource == nullptr) {
				cerr << "Resource type mismatch: " << name << endl;
				return res_t<T>();
			}
			return resource;
		}
		//resource does not exist, create and load
		res_t<T> resource = make_shared<T>();
		if (!resource->Load(name, forward<Args>(args)...)) {
			cerr << "Couldn't load resource: " << name << endl;
			return res_t<T>();
		}

		//store resource in map
		m_resources[name] = resource;

		return resource;
	}
	inline ResourceManager& Resources() {return ResourceManager::Instance();}
}