#include "Player.h"
#include "../Engine/Engine.h"
#include "Bullet.h"
#include "Assets.h"
#include "../Engine/Renderer.h"
#include "SpaceGame.h"

void Player::Update(float dt) {

	//Movement
	float thrust = 0.0f;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +m_speed;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

	float rotate = 0.0f;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +180.0f;
	SetRotation(m_transform.rotation + rotate * dt);

	nu::Vector2 forward{1, 0};
	nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad) * thrust;
	AddVelocity(velocity * dt);

	//Particles
	if (thrust) {
		nu::Particle particle;
		nu::Vector2 offset{ -1.0f, 0.0f };
		offset = offset.Rotate(m_transform.rotation * nu::DegToRad);
		particle.position = m_transform.position;
		particle.color = { 1.0f, 1.0f, 1.0f };
		particle.lifespan = nu::RandomFloat(0.5f, 1.5f);
		particle.velocity = { nu::RandomFloat(-200.0f, 200.0f), nu::RandomFloat(-200.0f, 200.0f) };

		nu::Engine::Get().GetPS().AddParticle(particle);
	}

	//Fire
	if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
		
		//nu::Engine::Get().GetAudio().PlaySound("shoot");

		BulletDesc bulletDesc;
		bulletDesc.name = "Bullet";
		bulletDesc.tag = "PlayerBullet";
		bulletDesc.model = assets::bulletModel;
		bulletDesc.transform = m_transform;
		bulletDesc.speed = 1000.0f;
		bulletDesc.lifespan = 1.0f;
		unique_ptr<Bullet> bullet = make_unique<Bullet>(bulletDesc);
		m_scene->AddActor(move(make_unique<Bullet>(bulletDesc)));
	}

	////Bullet Time
	//if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_X)) {
	//	nu::Engine::Get().GetTime().SetTimeScale(0.5f);
	//}
	//else {
	//	nu::Engine::Get().GetTime().SetTimeScale(1.0f);
	//}

	Actor::Update(dt);
}
void Player::Draw(const nu::Renderer& renderer) const {
	Actor::Draw(renderer);
}

void Player::OnCollision(Actor* other)
{
	if (other->GetName() == "Enemy") { 
		SetDestroyed(); 
		((SpaceGame*)m_scene->GetGame())->OnPlayerDead();
	}
	if (other->GetName() == "Rock") {
		SetDestroyed();
		((SpaceGame*)m_scene->GetGame())->OnPlayerDead();
	}
}
