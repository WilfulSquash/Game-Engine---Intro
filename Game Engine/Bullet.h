#pragma once
#include "../Engine/Actor.h"

struct BulletDesc : public nu::ActorDesc {
	float speed = 2000.0f;
};
class Bullet : public nu::Actor {

public:
	Bullet() = default;
	Bullet(const BulletDesc& bulletDesc) : Actor{ bulletDesc }, m_speed{ bulletDesc.speed } {};

	void Update(float dt);

private:
	int m_ammo = 0;
	float m_speed = 800.0f;
};