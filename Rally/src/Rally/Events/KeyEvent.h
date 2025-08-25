#pragma once

#include "Event.h"
#include "Rally/ModsCodes.h"
#include <sstream>

namespace Rally {

	class RALLY_API KeyEvent : public Event
	{
	public:
		int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {
		}

		int m_KeyCode;
	};

	class RALLY_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, bool isRepeat = false, int mods = 0)
			: KeyEvent(keycode), m_IsRepeat(isRepeat), m_Mods(mods) {
		}

		bool IsRepeat() const { return m_IsRepeat; }
		int  GetMods()  const { return m_Mods; }

		bool IsControlDown() const { return m_Mods & RL_MOD_CONTROL; }
		bool IsShiftDown()   const { return m_Mods & RL_MOD_SHIFT; }
		bool IsAltDown()     const { return m_Mods & RL_MOD_ALT; }
		bool IsSuperDown()   const { return m_Mods & RL_MOD_SUPER; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode
				<< " (repeat=" << m_IsRepeat << ")"
				<< " mods=" << m_Mods;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		bool m_IsRepeat;
		int  m_Mods;
	};

	class RALLY_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode, int mods = 0)
			: KeyEvent(keycode), m_Mods(mods) {
		}

		int GetMods() const { return m_Mods; }

		bool IsControlDown() const { return m_Mods & RL_MOD_CONTROL; }
		bool IsShiftDown()   const { return m_Mods & RL_MOD_SHIFT; }
		bool IsAltDown()     const { return m_Mods & RL_MOD_ALT; }
		bool IsSuperDown()   const { return m_Mods & RL_MOD_SUPER; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode
				<< " mods=" << m_Mods;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)

	private:
		int m_Mods;
	};

	class RALLY_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}