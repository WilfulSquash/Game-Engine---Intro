#pragma once
#include "Object.h"
#include "../Engine/Math/Transform.h"
#include "../Engine/Renderer/Model.h"
#include "../Engine/Resources/Resource.h"
#include "../Engine/Components/Component.h"
#include <string>
#include <memory>

namespace nu {

    class Scene;
    class Texture;

    struct ActorDesc {
        Transform transform{0};
        float lifespan = 0.0f;
        string name;
        string tag;
        res_t<Model> model;
        res_t<Texture> texture;

        Scene* m_scene{ nullptr };
    };
    class Actor : public Object {
       
    public:
        Actor() = default;
        Actor(const ActorDesc& actorDesc) :  
            m_tag{ actorDesc.tag }, 
            m_transform{ actorDesc.transform },  
            m_lifespan{actorDesc.lifespan}
        {};

        Actor(const Actor& other);

        CLASS_PROTOTYPE(Actor)

        virtual void Update(float dt);
        virtual void Draw(const class Renderer& renderer) const;

        virtual void Start();
        virtual void OnDestroy();

        virtual void OnCollision(Actor* other) {};

        const Transform& GetTransform() const { return m_transform; }
		void SetTransform(const Transform& transform) { m_transform = transform; }

        void SetPosition(const Vector2& position) { m_transform.position = position; }
        void SetRotation(float rotation) { m_transform.rotation = rotation; }
        void SetScale(float scale) { m_transform.scale = scale; }

		const string& GetName() const { return m_name; }
        const string& GetTag() const { return m_tag; }
        void SetTag(const string& tag) { m_tag = tag; }

        Scene* GetScene() { return m_scene; }

        float GetRadius() const;
		//void SetModel(std::shared_ptr<Model> model) { m_model = model; }

        void SetDestroyed(bool destroy = true) { m_destroyed = destroy; }
        bool GetDestroyed() const { return m_destroyed; }

        bool GetPersistent() const { return m_persistent; }

        virtual void Read(const nu::json::value_t& value) override;

		void AddComponent(unique_ptr<Component> component);

        template<derived_from <Component> T>
        T* GetComponent();

        friend Scene;

    protected:
        string m_tag;

        Transform m_transform;
        float m_lifespan = 0.0f;
        bool m_destroyed = false;
        bool m_persistent = false;

        vector<unique_ptr<Component>> m_components;

        Scene* m_scene = nullptr;
    };
    template<derived_from<Component> T>
    inline T* Actor::GetComponent()
    {
        for (auto& component : m_components) {
            auto result = dynamic_cast<T*>(component.get());
            if (result) return result;
        }

        return nullptr;
    }
}