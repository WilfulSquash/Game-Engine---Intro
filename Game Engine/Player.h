#pragma once
#include "../Engine/Actor.h"

struct PlayerDesc : public nu::ActorDesc{
	float speed = 2000.0f;
};

class Player : public nu::Actor{
public:
	Player() = default;
	Player(const PlayerDesc& playerDesc) : Actor{ playerDesc }, m_speed{ playerDesc.speed } {};

	void Update(float dt);
	void Draw(const class nu::Renderer& renderer) const;

	void OnCollision(Actor* other) override;

private:
	int m_ammo = 0;
	float m_speed = 800.0f;
};