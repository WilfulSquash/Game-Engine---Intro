#include "pch.h"
#include "Actor.h"
#include "Renderer/Renderer.h"
#include "Math/MathUtils.h"
#include "Renderer/Texture.h"
#include "Engine.h"
#include "Components/RendererComponent.h"

namespace nu {
    FACTORY_REGISTER(Actor)
    FACTORY_REGISTER_AS(Actor, "Asteroid")

    Actor::Actor(const Actor& other) :
        //copy stuff
        Object{ other },
        m_tag{ other.m_tag },
        m_transform{ other.m_transform },
        m_lifespan{ other.m_lifespan }
    {
		//clone components
        for(const auto& component : other.m_components) 
        {
			auto clone = unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			AddComponent(move(clone));
		}
    }
    void Actor::Start() {
        for (auto& component : m_components) {
            component->Start();
        }
    };

    void Actor::OnDestroy() {
        for (auto& component : m_components) {
            component->Destroyed();
        }
    };

    void Actor::Update(float dt) {
        //lifespan
        if (m_lifespan > 0.0f) {
            m_lifespan -= dt;
            m_destroyed = (m_lifespan <= 0.0f);
        }

        for (auto& component : m_components) {
			if (component->IsActive())
            component->Update(dt);
        }
    }

    void Actor::Draw(const Renderer& renderer) const
    {

        for (auto& component : m_components) {
            auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
            if (rendererComponent) {
				if (rendererComponent->IsActive())
                rendererComponent->Draw(renderer);
            }
        }
    }

    float Actor::GetRadius() const
    {
        //if (m_model) { return m_model->GetRadius() * m_transform.scale * 0.9f; }
        //if (m_texture) { return (m_texture->GetSize().Length() * 0.5f) * 0.5f; }

        return 0.0f;
    }
    void Actor::Read(const nu::json::value_t& value)
    {
        Object::Read(value);

        if (JSON_HAS_NAME(value, "transform")) {
            m_transform.Read(JSON_GET_NAME(value, "transform"));
        }

		JSON_READ_NAME(value, "tag", m_tag);
        JSON_READ_NAME(value, "lifespan", m_lifespan);
        JSON_READ_NAME(value, "persistent", m_persistent);

        //Read actor compo
        if (JSON_HAS_NAME(value, "components")) {
            //iterrate through actor compos
            for (auto& componentValue : JSON_GET_NAME(value, "components").GetArray()) {

                //get compo type
                string typeName;
                JSON_READ_NAME(componentValue, "type", typeName);

                cout << "Loading component type: " << typeName << endl;

                auto component = Factory::Instance().Create<Component>(typeName);

                if (component) {
                    component->Read(componentValue);
		            AddComponent(move(component));
                }
            }
        }
    }

    void Actor::AddComponent(unique_ptr<Component> component)
    {
		component->SetOwner(this);
		m_components.push_back(move(component));
    }
}