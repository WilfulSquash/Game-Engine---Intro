#pragma once
#include "Framework\Actor.h"

namespace nu {
	class PhysicsComponent;
	class SpriteAnimatorRendererComponent;
	class FlyingEnemyController : public Actor {
	public:
		CLASS_PROTOTYPE(FlyingEnemyController)

		void Start() override;

		void Update(float dt) override;

		void OnCollision(Actor* other) override;

		void Read(const json::value_t& value) override;

	protected:
		PhysicsComponent* m_physicsComponent = nullptr;
		SpriteAnimatorRendererComponent* m_rendererComponent = nullptr;
	};
}

