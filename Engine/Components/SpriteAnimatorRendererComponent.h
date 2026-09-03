#pragma once
#include "SpriteRendererComponent.h"
#include "Resources/ResourceManager.h"

namespace nu {
	class SpriteAnimatorRendererComponent : public SpriteRendererComponent{
	public:
		CLASS_PROTOTYPE(SpriteAnimatorRendererComponent)

		struct SpriteAnimation {
			string name;
			float fps{10.0f};
			bool loop = true;
			res_t<class TextureFrames> textureFrames;
		};
		void Start() override;
		void Update(float dt) override;

		void Play(const string& name);

		bool GetPaused() { return m_pause; }
		void SetPause(bool pause = true) { m_pause = pause; }

		unsigned int GetFrame() const { return m_frame; }
		bool IsAnimationDone() const;
		const string& GetAnimationName() const { return m_spriteAnimation.name; }

		void Read(const json::value_t& value) override;

	private:
		unsigned int m_frame = 0;
		float m_frameTimer = 0;
		bool m_pause = false;

		string m_defaultAnimationName;

		SpriteAnimation m_spriteAnimation;
		map<string, SpriteAnimation> m_spriteAnimations;
	};
}