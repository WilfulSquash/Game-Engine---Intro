#include "EnemyController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Core/Factory.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Damager.h"

using namespace nu;
FACTORY_REGISTER(EnemyController)

void EnemyController::Start()
{
	CharacterBase::Start();

	m_physicsComponent = GetComponent<PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<SpriteAnimatorRendererComponent>();
	assert(m_rendererComponent);
}

void EnemyController::Update(float dt)
{
	Vector2 velocity = m_physicsComponent->GetVelocity();
	switch (m_state)
	{
	case CharacterBase::State::Move:
	{
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
			m_rendererComponent->SetFlipH(dir < 0.0f);
		}
		else {
			m_rendererComponent->Play("idle");
		}
		break;
	}
	case CharacterBase::State::Attack:
		break;
	case CharacterBase::State::Hit:
		if (m_rendererComponent->IsAnimationDone()) {
			m_state = State::Move;
			m_rendererComponent->Play("idle");
		}
		break;
	case CharacterBase::State::Death:
		break;
	default:
		break;
	}

	m_physicsComponent->SetVelocity(velocity);

	CharacterBase::Update(dt);
}

void EnemyController::OnCollision(Actor* other)
{
	if (nu::EqualsIgnoreCase(other->GetTag(), "PlayerDamager")) {
		m_state = State::Hit;
		m_rendererComponent->Play("hit");
		Damager* damager = dynamic_cast<Damager*>(other);
		if(damager) m_health -= damager->GetDamage();
		if(m_health <= 0) {
			SetDestroyed();
		}
	}
}

void EnemyController::Read(const json::value_t& value)
{
	CharacterBase::Read(value);
}
