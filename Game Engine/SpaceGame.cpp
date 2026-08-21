#include "SpaceGame.h"
#include "../Engine/Engine.h"
#include "../Engine/Actor.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"

#include <memory>

using namespace nu;
using namespace std;

bool SpaceGame::Initialize()
{
	Game::Initialize();

	m_scene = new Scene();
	m_scene->SetGame(this);
	m_scene->Load("data/scene.json");

	Engine::Get().GetAudio().AddSound("music", "audio/background.mp3");
	Engine::Get().GetAudio().PlaySound("music");

	m_titleText = new Text(Resources().Get<Font>("Fonts/ENDOR___.ttf", 64.0f));
	m_titleText->Create(Engine::Get().GetRenderer(), "You Like RNG?", Color{ 1.0f, 1.0f, 1.0f });

	m_gameOverFont = make_shared<Font>();
	m_gameOverFont->Load("Fonts/ENDOR___.ttf", 32.0f);

	m_scoreText = new Text(m_gameOverFont);
	m_livesText = new Text(m_gameOverFont);

	return true;
}

void SpaceGame::Update(float dt)
{
	switch (m_gameState)
	{
	case SpaceGame::GameState::Title:
		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
			m_gameState = GameState::StartGame;
		}
		break;
	case SpaceGame::GameState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_spawnTime = 5.0f;
		m_stateTimer = 0.5f;
		m_gameState = GameState::StartLevel;
		break;
	case SpaceGame::GameState::StartLevel:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) {
			m_scene->RemoveAllActors();
			SpawnPlayer();
			m_spawnTime = 5.0f;
			m_gameState = GameState::Game;
		}
		break;
	case SpaceGame::GameState::Game:
		m_spawnTimer -= dt;
		if (m_spawnTimer <= 0.0f) { 
			m_spawnTimer = m_spawnTime;  
			SpawnEnemy(); 
			SpawnRock();
		}
		break;
	case SpaceGame::GameState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) {
			m_scene->RemoveAllActors();
			m_gameState = GameState::Title;
		}
		break;
	default:
		break;
	}

	Game::Update(dt);
}

void SpaceGame::Draw(nu::Renderer& renderer)
{
	renderer.DrawTexture(*Resources().Get<Texture>("Textures/background.png", Engine::Get().GetRenderer()), 1, 1, 0.0f, 25.0f);
	switch (m_gameState)
	{
	case SpaceGame::GameState::Title:
		//Draw Title
		m_titleText->Draw(renderer, 400, 400);
		break;
	case SpaceGame::GameState::StartGame:
		break;
	case SpaceGame::GameState::StartLevel:
	case SpaceGame::GameState::Game:
		m_scoreText->Create(renderer, "Score: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f });
		m_scoreText->Draw(renderer, 30, 30);
		m_livesText->Create(renderer, "Lives: " + std::to_string(m_lives), { 1.0f, 1.0f, 1.0f });
		m_livesText->Draw(renderer, (float)renderer.GetWidth() - 160, 30);
		break;
	case SpaceGame::GameState::GameOver:
	default:
		break;
	}

	Game::Draw(renderer);
}

void SpaceGame::OnPlayerDead()
{
	m_lives--;
	if (m_lives <= 0) m_gameState = GameState::GameOver;
	else(m_gameState = GameState::StartLevel);

	m_stateTimer = 2.0f;
}

void SpaceGame::SpawnPlayer()
{
	auto actor = Factory::Instance().Create<Actor>("PlayerPrototype");
	m_scene->AddActor(move(actor));
}

void SpaceGame::SpawnEnemy()
{
	auto actor = Factory::Instance().Create<Actor>("EnemyPrototype");
	actor->SetTransform(Transform{ Vector2{RandomFloat((float)Engine::Get().GetRenderer().GetWidth()), RandomFloat((float)Engine::Get().GetRenderer().GetHeight())}, 0.0f, 1.0f });
	m_scene->AddActor(move(actor));
}

void SpaceGame::SpawnRock()
{
	auto actor = Factory::Instance().Create<Actor>("AsteroidPrototype");
	Factory::Instance().Register<Actor>("Asteroid");
	actor->SetTransform(Transform{ Vector2{RandomFloat((float)Engine::Get().GetRenderer().GetWidth()), RandomFloat((float)Engine::Get().GetRenderer().GetHeight())}, 0.0f, 1.0f });
	m_scene->AddActor(move(actor));
}
