#include "pch.h"
#include "Font.h"
#include "SDL3_ttf/SDL_ttf.h"

using namespace std;
namespace nu {
	Font::~Font() {
		if (m_ttfFont != nullptr) {
			TTF_CloseFont(m_ttfFont);
		}
	}

	bool Font::Load(const string& name, float fontSize) {
		m_ttfFont = TTF_OpenFont(name.c_str(), fontSize);
		if (m_ttfFont == nullptr) {
			cerr << "Could not load font: " << name << endl;
			return false;
		}

		return true;
	}
}