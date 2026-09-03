#pragma once
#include "Framework\Actor.h"
#include "CharacterBase.h"

namespace nu {
	class PhysicsComponent;
	class SpriteAnimatorRendererComponent;
	class PlayerController : public CharacterBase{
	public:
		CLASS_PROTOTYPE(PlayerController)

		void Start() override;

		void Update(float dt) override;

		void OnCollision(Actor* other) override;

		void Read(const json::value_t& value) override;

	protected:
		PhysicsComponent* m_physicsComponent = nullptr;
		SpriteAnimatorRendererComponent* m_rendererComponent = nullptr;
	};
}