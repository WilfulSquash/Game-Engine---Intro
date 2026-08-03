 #pragma once
#include "../Engine/Game.h"
#include "../Engine/Text.h"

class SpaceGame : public nu::Game {
public:
	SpaceGame() = default;
	SpaceGame(nu::Scene* scene) : Game(scene) {};

	bool Initialize() override;
	void Update(float dt) override;
	void Draw(class nu::Renderer& renderer) override;

	enum class GameState {
		Title,
		StartGame,
		StartLevel,
		Game, 
		GameOver
	};

	void OnPlayerDead();
	void AddPoints(int points) { m_score += points; }

private:
	void SpawnPlayer();
	void SpawnEnemy();
	void SpawnRock();

	int m_score{ 0 };
	int m_lives{ 0 };

	float m_stateTimer{ 0.0f };

	float m_spawnTimer = 0.0f;
	float m_spawnTime = 5.0f;

	GameState m_gameState = GameState::Title;

	nu::Font* m_titleFont = nullptr;
	nu::Text* m_titleText = nullptr;

	nu::Font* m_gameOverFont = nullptr;
	nu::Text* m_gameOverText = nullptr;

	nu::Font* m_scoreFont = nullptr;
	nu::Text* m_scoreText = nullptr;

	nu::Font* m_livesFont = nullptr;
	nu::Text* m_livesText = nullptr;
};