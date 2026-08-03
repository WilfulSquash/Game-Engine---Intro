#pragma once
#include "../Engine/Actor.h"

struct EnemyDesc : public nu::ActorDesc {
	float speed = 2000.0f;
};
class Enemy : public nu::Actor {

public:
	Enemy() = default;
	Enemy(const EnemyDesc& enemyDesc) : Actor{ enemyDesc }, m_speed{ enemyDesc.speed } {};
	Enemy(float speed, const nu::Transform& transform) : Actor{ transform }, m_speed{ speed } {};
	Enemy(const nu::Transform& transform, const nu::Model& model, float speed) : Actor{ transform, model }, m_speed{ speed } {};

	void Update(float dt) override;
	void OnCollision(Actor* other) override;
	void Draw(const class nu::Renderer& renderer) const;
private:
	int m_ammo = 0;
	float m_speed = 800.0f;
};