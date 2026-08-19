#pragma once
#include "../Engine/Actor.h"

struct EnemyDesc : public nu::ActorDesc {
	float speed = 2000.0f;
};
class Enemy : public nu::Actor {

public:
	Enemy() = default;
	Enemy(const EnemyDesc& enemyDesc) : Actor{ enemyDesc }, m_speed{ enemyDesc.speed } {};

	void Update(float dt) override;
	void OnCollision(Actor* other) override;
	void Draw(const class nu::Renderer& renderer) const;

	void Read(const nu::json::value_t& value) override;

	CLASS_PROTOTYPE(Enemy)

private:
	int m_ammo = 0;
	float m_speed = 800.0f;
};