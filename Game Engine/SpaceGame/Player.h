#pragma once
#include "../Engine/Framework/Actor.h"
#include "../Engine/Serialization/Json.h"

struct PlayerDesc : public nu::ActorDesc{
	float speed = 2000.0f;
};

class Player : public nu::Actor{
public:
	Player() = default;
	Player(const PlayerDesc& playerDesc) : Actor{ playerDesc }, m_speed{ playerDesc.speed } {};

	CLASS_PROTOTYPE(Player)

	void Update(float dt);
	void Draw(const class nu::Renderer& renderer) const;

	void OnCollision(Actor* other) override;

	float GetSpeed() const { return m_speed; }

	void Read(const nu::json::value_t& value) override;

private:
	int m_ammo = 0;
	float m_speed = 800.0f;
};