#include "FlyingEnemyController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Core/Factory.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Damager.h"

using namespace nu;
FACTORY_REGISTER(FlyingEnemyController)

void FlyingEnemyController::Start()
{
	CharacterBase::Start();

	m_physicsComponent = GetComponent<PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<SpriteAnimatorRendererComponent>();
	assert(m_rendererComponent);
}

void FlyingEnemyController::Update(float dt)
{
	Vector2 velocity = m_physicsComponent->GetVelocity();
	switch (m_state
		)
	{
	case CharacterBase::State::Move:
	{
		auto player = m_scene->GetActorByName("PlayerPrototype");
		if (player) {
			Vector2 position = m_physicsComponent->GetPosition();
			Vector2 playerPosition = player->GetTransform().position;
			Vector2 direction = playerPosition - position;

			m_rendererComponent->SetFlipH(direction.x < 0.0f);

			if (direction.Length() < 100.0f) {
				m_state = State::Attack;
				m_rendererComponent->Play("attack");

			}

			m_physicsComponent->ApplyForce(direction.Normalized() * 50.0f);
		}
		break;
	}
	case CharacterBase::State::Attack:
		if (m_rendererComponent->GetFrame() == 3) {
			auto damager = nu::Factory::Instance().Create<Damager>("DamagerPrototype");
			damager->SetDamage(1.0f);
			damager->SetPosition(GetTransform().position);
			damager->SetScale(3.0f);
			damager->SetTag("EnemyDamager");
			m_scene->AddActor(std::move(damager));
		}
		if (m_rendererComponent->IsAnimationDone()) {
			m_state = State::Move;
			m_rendererComponent->Play("idle");
		}
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
	
	CharacterBase::Update(dt);
}

void FlyingEnemyController::OnCollision(Actor* other)
{
	if (nu::EqualsIgnoreCase(other->GetTag(), "PlayerDamager")) {

		//hit the enemy
		m_state = State::Hit;
		m_rendererComponent->Play("hit");
		Damager* damager = dynamic_cast<Damager*>(other);
		if (damager) m_health -= damager->GetDamage();
		if (m_health <= 0) {
			SetDestroyed();
		}

		//removes the damager actor from the scene
		other->SetDestroyed();
	}
}

void FlyingEnemyController::Read(const json::value_t& value)
{
	CharacterBase::Read(value);
}
