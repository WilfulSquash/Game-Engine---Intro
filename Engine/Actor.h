#pragma once
#include "Transform.h"
#include "Model.h"
#include <string>

namespace nu {

    class Scene;

    struct ActorDesc {
        Transform transform{0};
        Vector2 velocity{0.0f, 0.0f};
        float damping{ 0.0f };
        float lifespan = 0.0f;
        Model model;
        string name;
        string tag;
    };
    class Actor {
       
    public:
        Actor() = default;
        Actor(const ActorDesc& actorDesc) : 
            m_name{ actorDesc.name }, 
            m_tag{ actorDesc.tag }, 
            m_transform{ actorDesc.transform }, 
            m_velocity{ actorDesc.velocity }, 
            m_damping{actorDesc.damping}, 
            m_model{ actorDesc.model },
            m_lifespan{actorDesc.lifespan}
        {};
        Actor(const Transform& transform) : m_transform{ transform } { };
		Actor(const Transform& transform, const Model& model) : m_transform{ transform }, m_model{ model } {};

        virtual void Update(float dt);
        virtual void Draw(const class Renderer& renderer) const;

        virtual void OnCollision(Actor* other) {};

        const Transform& GetTransform() const { return m_transform; }
        void SetPosition(const Vector2& position) { m_transform.position = position; }
        void SetRotation(float rotation) { m_transform.rotation = rotation; }
        void SetScale(float scale) { m_transform.rotation = scale; }

        const Vector2& GetVelocity() const { return m_velocity; }
        const Vector2& SetVelocity(const Vector2& velocity) { return m_velocity = velocity; }
        const Vector2& AddVelocity(const Vector2& velocity) { return m_velocity += velocity; }

		const string& GetName() const { return m_name; }
        const string& GetTag() const { return m_tag; }

        Scene* GetScene() { return m_scene; }

        float GetRadius() const;

        void SetDestroyed(bool destroy = true) { m_destroyed = destroy; }
        bool GetDestroyed() const { return m_destroyed; }

        friend Scene;

    protected:
		string m_name;
        string m_tag;

        Transform m_transform;
        Vector2 m_velocity{ 0, 0 };
        float m_damping{ 0.0f };
        float m_lifespan = 0.0f;
        bool m_destroyed = false;

        Model m_model;

        Scene* m_scene = nullptr;
    };
}