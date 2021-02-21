#pragma once
#include "RenderWindow.h"
#include "Keyboard/Keyboard.h"
#include "Mouse/Mouse.h"
#include "Graphics/Graphics.h"
#include <memory>

class WindowContainer
{
public:
	WindowContainer();
	LRESULT windowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

protected:
	RenderWindow render_window;
	Keyboard m_keyboard;
	Mouse m_mouse;

private:
	
};

