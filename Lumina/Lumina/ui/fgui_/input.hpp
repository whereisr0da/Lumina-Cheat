#pragma once

/*
#include "render.hpp"
#include "../../common/input.h"
#include "../../sdk/interfaces.h"
*/

namespace FGUI_INPUT
{
	/*
	inline FGUI::POINT GetCursorPos()
	{
		FGUI::POINT point = FGUI::POINT();

		point.m_iX = input::get_mouse().m_pos.x;
		point.m_iY = input::get_mouse().m_pos.y;

		return point;
	}

	inline void PullInput()
	{
		//input::update_mouse();
	}

	inline bool GetKeyState(int key)
	{
		return input::get_key_info(key).m_state == input::e_state::PRESSED; //current_pressed_keys.at(key_code);
	}

	inline bool GetKeyPress(int key)
	{
		return input::get_key_info(key).m_state == input::e_state::PRESSED;
	}

	inline bool GetKeyRelease(int key)
	{
		return input::get_key_info(key).m_state == input::e_state::IDLE;
	}

	inline FGUI::POINT GetCursorPosDelta()
	{
		static Vector2D* oldVector;

		if(!oldVector)
			oldVector = new Vector2D(input::get_mouse().m_pos);

		FGUI::POINT point = FGUI::POINT();

		point.m_iX = input::get_mouse().m_pos.x - oldVector->x;
		point.m_iY = input::get_mouse().m_pos.y - oldVector->y;

		return point;
	}

	inline int GetCursorWheelDelta()
	{
		static int* oldScroll;

		if (!oldScroll)
			oldScroll = new int(input::get_mouse().m_scroll);

		return input::get_mouse().m_scroll - *oldScroll;
	}

	inline bool IsCursorInArea(FGUI::AREA area)
	{
		// m_iLeft = x, m_iTop = y, m_iRight = w, m_iBottom = h
		Vector2D vector1 = Vector2D(area.m_iLeft, area.m_iTop);
		Vector2D vector2 = Vector2D(area.m_iRight, area.m_iBottom);

		return input::mouse_in_bounds(vector1, vector2);
	}*/

	/*
	inline std::array<bool, 256> m_prgpCurrentPressedKeys, m_prgpOldPressedKeys;
	inline FGUI::POINT m_ptCursorPosition, m_ptCursorPositionDelta;

	inline void PullInput()
	{
		static FGUI::POINT ptLastKnownPosition = { 0, 0 };

		std::copy(m_prgpCurrentPressedKeys.begin(), m_prgpCurrentPressedKeys.end(), m_prgpOldPressedKeys.begin());

		for (std::size_t i = 0; i < 256; i++)
		{
			m_prgpCurrentPressedKeys.at(i) = GetAsyncKeyState(i);
		}

		// Get current cursor position
		GetCursorPos(reinterpret_cast<LPPOINT>(&m_ptCursorPosition));

		// Calculate the cursor position delta
		m_ptCursorPositionDelta = { (m_ptCursorPosition.m_iX - ptLastKnownPosition.m_iX), (m_ptCursorPosition.m_iY - ptLastKnownPosition.m_iY) };

		// Get last known position of the cursor
		ptLastKnownPosition = m_ptCursorPosition;
	}

	inline bool GetKeyState(int _key_code)
	{
		return m_prgpCurrentPressedKeys.at(_key_code);
	}

	inline bool GetKeyRelease(int _key_code)
	{
		return (!m_prgpCurrentPressedKeys.at(_key_code) && m_prgpOldPressedKeys.at(_key_code));
	}

	inline bool GetKeyPress(int _key_code)
	{
		return (m_prgpCurrentPressedKeys.at(_key_code) && !m_prgpOldPressedKeys.at(_key_code));
	}

	inline FGUI::POINT GetCursorPos()
	{
		return m_ptCursorPosition;
	}

	inline FGUI::POINT GetCursorPosDelta()
	{
		return m_ptCursorPositionDelta;
	}

	inline int GetCursorWheelDelta()
	{
		return 0;
	}

	inline bool IsCursorInArea(FGUI::AREA area)
	{
		return (GetCursorPos().m_iX > area.m_iLeft && GetCursorPos().m_iY > area.m_iTop &&
			GetCursorPos().m_iX < area.m_iLeft + area.m_iRight && GetCursorPos().m_iY < area.m_iTop + area.m_iBottom);
	}


	inline void init()
	{
		FGUI::INPUT.GetCursorPos = FGUI_INPUT::GetCursorPos;
		FGUI::INPUT.GetKeyPress = FGUI_INPUT::GetKeyPress;
		FGUI::INPUT.IsCursorInArea = FGUI_INPUT::IsCursorInArea;
		FGUI::INPUT.GetKeyState = FGUI_INPUT::GetKeyState;
		FGUI::INPUT.GetKeyRelease = FGUI_INPUT::GetKeyRelease;
		FGUI::INPUT.GetCursorWheelDelta = FGUI_INPUT::GetCursorWheelDelta;
		FGUI::INPUT.GetCursorPosDelta = FGUI_INPUT::GetCursorPosDelta;
		FGUI::INPUT.PullInput = FGUI_INPUT::PullInput;
	}

	fgui::state get_key_state(const fgui::key& key) {
		return input::get_key_info(key).m_state == input::e_state::PRESSED;// interfaces::surfac->is_button_down(key);
	}

	fgui::delta get_scroll_delta() {
		return 0; // core::ifaces::get_ifaces.input_system->get_analog_delta(enums::analog_code::analog_code_mouse_wheel);
	}

	fgui::point get_mouse_position() {
		static fgui::point point = { 0, 0 };

		interfaces::surface->SurfaceGetCursorPos(point.x, point.y);

		return point;
	}

	void setup_input_funcs() {
		fgui::input.get_key_state = get_key_state;
		fgui::input.get_scroll_delta = get_scroll_delta;
		fgui::input.get_mouse_position = get_mouse_position;
	}*/
}