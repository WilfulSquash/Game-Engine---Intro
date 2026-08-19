#pragma once

#include "Renderer.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Transform.h"
#include "Actor.h"
#include "Random.h"
#include "Input.h"
#include <iostream>
#include <vector>
#include "GameTime.h"
#include "MathUtils.h"
#include "Scene.h"
#include "File.h"
#include "Model.h"
#include "Mesh.h"
#include "Text.h"
#include "Font.h"
#include "Game.h"
#include "Audio.h"
#include "Particle.h"
#include "Texture.h"
#include "Resource.h"
#include "ResourceManager.h"
#include "Singleton.h"
#include "Json.h"
#include "StringUtils.h"
#include "Factory.h"


namespace nu {
	class Engine {
	public:
		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize();
		void Shutdown();

		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		Time& GetTime() { return m_time; }
		Audio& GetAudio() { return m_audio; }
		ParticleSystem& GetPS() { return m_particleSystem; }

	private:
		Input m_input;
		Renderer m_renderer;

		Engine() = default;

		Time m_time;

		Audio m_audio;

		ParticleSystem m_particleSystem;
	};
}