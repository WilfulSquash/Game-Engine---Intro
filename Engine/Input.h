#pragma once
#include "Vector2.h"
#include <vector>

using namespace std;


namespace nu {

	class Input {
	public:
		enum class MouseButton {
			LEFT = 1,
			MIDDLE = 2,
			RIGHT = 3
		};



		bool Initialize();
		void Shutdown();

		void Update();

		bool GetKeyDown(int key) const { return m_keyStates[key];}
		bool GetPrevKeyDown(int key) const { return m_prevKeyStates[key];}
		bool GetKeyPressed(int key) const { return !m_keyStates[key] && m_prevKeyStates[key];}
		bool GetKeyReleased(int key) const { return m_keyStates[key] && !m_prevKeyStates[key];}

		bool GetMouseDown(MouseButton button) const { return m_buttonStates & GetButtonBit(button); }
		bool GetPrevMouseDown(MouseButton button) const { return m_prevButtonStates & GetButtonBit(button); }
		bool GetButtonPressed(MouseButton button) const { return !GetPrevMouseDown(button) && GetMouseDown(button); }
		bool GetButtonReleased(MouseButton button) const { return GetPrevMouseDown(button) && !GetMouseDown(button); }

		Vector2 GetMousePosition() const { return m_mousePosition; }

	private:
		uint32_t GetButtonBit(MouseButton button) const;

	private:
		//keyboard
		vector<bool> m_keyStates;
		vector<bool> m_prevKeyStates;

		//mouse
		uint32_t m_buttonStates = 0;
		uint32_t m_prevButtonStates = 0;

		Vector2 m_mousePosition{0, 0};
	};
}