#pragma once
#include "../Engine/Actor.h"

struct BulletDesc : public nu::ActorDesc {
	float speed = 2000.0f;
};
class Bullet : public nu::Actor {

public:
	Bullet() = default;
	Bullet(const BulletDesc& bulletDesc) : Actor{ bulletDesc }, m_speed{ bulletDesc.speed } {};
	Bullet(float speed, const nu::Transform& transform) : Actor{ transform }, m_speed{ speed } {};
	Bullet(const nu::Transform& transform, const nu::Model& model, float speed) : Actor{ transform, model }, m_speed{ speed } {};

	void Update(float dt);
	//void Draw(const class nu::Renderer& renderer) const;
private:
	int m_ammo = 0;
	float m_speed = 800.0f;
};