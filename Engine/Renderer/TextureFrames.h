#pragma once
#include "Resources/ResourceManager.h"
#include "Math/Vector2.h"
#include "Math/Rect.h"
#include <string>
namespace nu {
	class TextureFrames : public Resource {
	public:
		bool Load(const string& filename, class Renderer& renderer);
		Rect GetFrameRect(unsigned int Frame);
	private:
		int m_numColumns = 0;
		int m_numRows = 0;
		int m_startFrame = 0;
		int m_totalFrames = 0;

		Vector2 m_frameSize{ 0, 0 };
		res_t<class Texture> m_texture;
	};
}