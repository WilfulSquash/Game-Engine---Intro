#include "pch.h"
#include "TextureFrames.h"
#include "Serialization/Json.h"
#include "Texture.h"

namespace nu {
	bool TextureFrames::Load(const string& filename, class Renderer& renderer) {
		json::document_t document;

		if (!json::Load(filename, document)) {
			cerr << "Could not load TextureFrames: " << filename << endl;
			return false;
		}
		string texture_name;
		JSON_READ_REQ(document, texture_name);
		if (texture_name.empty()) {
			return false;
		}
		m_texture = Resources().Get<Texture>(texture_name, renderer);
		if (!m_texture) {
			cerr << "Could not load Texture Frame texture: " << texture_name << endl;
			return false;
		}
		JSON_READ_NAME(document, "columns", m_numColumns);
		JSON_READ_NAME(document, "rows", m_numRows);
		JSON_READ_NAME(document, "start_frame", m_startFrame);
		JSON_READ_NAME(document, "totalFrames", m_totalFrames);
		Vector2 textureSize = m_texture->GetSize();

		if (m_numColumns <= 0 || m_numRows == 0) { 
			cerr << "Texture Frame rows or cols is 0\n.";
			return false; 
		}

		m_frameSize = textureSize / Vector2{ static_cast<float>(m_numColumns), static_cast<float>(m_numRows) };

		return true;
	}
	Rect TextureFrames::GetFrameRect(unsigned int frame)
	{
		if (frame >= static_cast<unsigned int>(m_totalFrames)) {
			cerr << "Texture Frames frame " << frame << " is out of bounds.\n";
			frame = 0;
		}
		int currentFrame = m_startFrame + frame;
		int column = currentFrame % m_numColumns;
		int row = currentFrame / m_numColumns;
		float x = column * m_frameSize.x;
		float y = row * m_frameSize.y;

		return Rect{
			x,
			y,
			m_frameSize.x,
			m_frameSize.y
		};
	}
}