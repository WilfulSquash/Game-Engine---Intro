#include "EnemyController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Core/Factory.h"
#include "Engine.h"
#include "Framework/Scene.h"

using namespace nu;
FACTORY_REGISTER(EnemyController)

void EnemyController::Start()
{
	Actor::Start();

	m_physicsComponent = GetComponent<PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<SpriteAnimatorRendererComponent>();
	assert(m_rendererComponent);
}

void EnemyController::Update(float dt)
{
	Vector2 velocity = m_physicsComponent->GetVelocity();
	float dir = 0.0f;
	auto player = m_scene->GetActorByName("PlayerPrototype");
	if (player) {
		Vector2 position = m_physicsComponent->GetPosition();
		Vector2 playerPosition = player->GetTransform().position;

		if (playerPosition.x < position.x) dir = -1.0f;
		else if (playerPosition.x > position.x) dir = +1.0f;
	}

	if (dir != 0.0f) {
		velocity.x = dir * 1000.0f;
		m_rendererComponent->Play("run");
	}
	else {
		m_rendererComponent->Play("idle");
	}

	m_rendererComponent->SetFlipH(dir < 0.0f);

	m_physicsComponent->SetVelocity(velocity);

	Actor::Update(dt);
}

void EnemyController::OnCollision(Actor* other)
{
}

void EnemyController::Read(const json::value_t& value)
{
	Actor::Read(value);
}
