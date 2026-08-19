#pragma once
#include "Object.h"
#include "Singleton.h"
#include "StringUtils.h"
#include <memory>
#include <map>

#define FACTORY_REGISTER(classname)                                 \
    class Register##classname                                       \
    {                                                               \
    public:                                                         \
        Register##classname()                                       \
        {                                                           \
            nu::Factory::Instance().Register<classname>(#classname);    \
        }                                                           \
    };                                                              \
    static Register##classname registerInstance;

using namespace std;

namespace nu {
    class ICreator {
    public:
        virtual ~ICreator() = default;
        virtual unique_ptr<Object> Create() = 0;
    };

    template <typename T>
        requires derived_from<T, Object>
    class Creator : public ICreator {
    public:
        unique_ptr<Object> Create() override { return make_unique<T>(); }
    };

    template <typename T>
        requires derived_from<T, Object>
    class PrototypeCreator : public ICreator {
    public:

        PrototypeCreator(unique_ptr<Object> prototype):
            m_prototype{move(prototype)}
        { }

        unique_ptr<Object> Create() override { 
            return m_prototype->Clone(); 
        }

    private:
        unique_ptr<Object> m_prototype;
    };

    class Factory : public Singleton<Factory>{
    public:
        template<typename T>
            requires derived_from<T, Object>
        void Register(const string& name);

        template<typename T>
            requires derived_from<T, Object>
        void RegisterProtoype(const string& name, unique_ptr<T> prototype);

        template<typename T = class Object>
            requires derived_from<T, Object>
        unique_ptr<T> Create(const string& name);
    private:
        map<string, unique_ptr<ICreator>> m_registry;
    };

    template<typename T>
        requires derived_from<T, Object>
    inline void Factory::Register(const string& name)
    {
        string lowerName = ToLower(name);

        if (m_registry.contains(lowerName)) {
            cerr << "Object Already registered: " << name << endl;

            return;
        }

        cout << "Object Registered: " << endl;

        m_registry[lowerName] = make_unique<Creator<T>>();
    }

    template<typename T>
        requires derived_from<T, Object>
    inline void Factory::RegisterProtoype(const string& name, unique_ptr<T> prototype)
    {
        string lowerName = ToLower(name);

        if (m_registry.contains(lowerName)) {
            cerr << "Object Already registered: " << name << endl;

            return;
        }

        m_registry[lowerName] = make_unique<PrototypeCreator<T>>(move(prototype));
    }

    template<typename T>
        requires derived_from<T, Object>
    inline unique_ptr<T> Factory::Create(const string& name)
    {
        string lowerName = ToLower(name);

        if (!m_registry.contains(lowerName)) {
            cerr << "Object not registered: " << name << endl;

            return unique_ptr<T>();
        }

        auto iter = m_registry.find(lowerName);

        //auto creator = m_registry[lowerName];
        //create unique ptr to object
        auto object = iter->second->Create();

        //check if object is derived from T
        T* derived = dynamic_cast<T*>(object.get());
        if (derived) {
            //release ptr ownership
            object.release();
            //create new unique ptr with derived ptr
            return unique_ptr<T>(derived);
        }
        else {
            cerr << "Object not derived from type: " << name << endl;
        }

        return unique_ptr<T>();
    }
}