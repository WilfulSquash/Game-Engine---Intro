#include "PlayerController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Core/Factory.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Damager.h"

using namespace nu;
FACTORY_REGISTER(PlayerController)

void PlayerController::Start()
{
	CharacterBase::Start();

	m_physicsComponent = GetComponent<PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<SpriteAnimatorRendererComponent>();
	assert(m_rendererComponent);
}

void PlayerController::Update(float dt)
{
	Vector2 velocity = m_physicsComponent->GetVelocity();
	

	switch (m_state)
	{
	case CharacterBase::State::Move:
	{
		float dir = 0.0f;
		if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) dir = -1.0f;
		if (Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) dir = +1.0f;
		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
			velocity.y = -800.0f;
		}

		if (dir != 0.0f) {
			velocity.x = dir * 1000.0f;
			m_rendererComponent->Play("run");
			m_rendererComponent->SetFlipH(dir < 0.0f);
		}
		else {
			m_rendererComponent->Play("idle");
		}


		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_RSHIFT)) {
			m_state = State::Attack;
			m_rendererComponent->Play("attack");

			auto damager = nu::Factory::Instance().Create<nu::Actor>("DamagerPrototype");
			damager->SetPosition(GetTransform().position + Vector2{(m_rendererComponent->GetFlipH()) ? -40.0f : 40.0f, 0.0f});
			damager->SetTag("PlayerDamager");
			m_scene->AddActor(std::move(damager));
		}
	}
		break;
	case CharacterBase::State::Attack:
	{
		if(m_rendererComponent->IsAnimationDone()) {
			m_state = State::Move;
			m_rendererComponent->Play("idle");
		}
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

	
	
	m_physicsComponent->SetVelocity(velocity);
	nu::Engine::Get().GetRenderer().SetCamera(m_physicsComponent->GetPosition());

	CharacterBase::Update(dt);
}

void PlayerController::OnCollision(Actor* other)
{
	if (nu::EqualsIgnoreCase(other->GetTag(), "EnemyDamager")) {

		//hit the enemy
		m_state = State::Hit;
		m_rendererComponent->Play("death");
		Damager* damager = dynamic_cast<Damager*>(other);
		if (damager) m_health -= damager->GetDamage();
		if (m_health <= 0) {
			SetDestroyed();
		}

		//removes the damager actor from the scene
		other->SetDestroyed();
	}
}

void PlayerController::Read(const json::value_t& value)
{
	CharacterBase::Read(value);
}
