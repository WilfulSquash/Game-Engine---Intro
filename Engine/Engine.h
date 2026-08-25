#pragma once

#include "Renderer/Renderer.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"
#include "Framework/Actor.h"
#include "Core/Random.h"
#include "Input/Input.h"
#include <iostream>
#include <vector>
#include "Core/GameTime.h"
#include "Math/MathUtils.h"
#include "Framework/Scene.h"
#include "Core/File.h"
#include "Renderer/Model.h"
#include "Renderer/Mesh.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Framework/Game.h"
#include "Audio/Audio.h"
#include "Renderer/Particle.h"
#include "Renderer/Texture.h"
#include "Resources/Resource.h"
#include "Resources/ResourceManager.h"
#include "Core/Singleton.h"
#include "Serialization/Json.h"
#include "Core/StringUtils.h"
#include "Core/Factory.h"
#include "Physics/Physics.h"


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
		Physics& GetPhysics() { return m_physics; }

	private:
		Input m_input;
		Renderer m_renderer;

		Engine() = default;

		Time m_time;

		Audio m_audio;

		ParticleSystem m_particleSystem;

		Physics m_physics{};
	};
}