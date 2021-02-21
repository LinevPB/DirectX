#pragma once
#include "ErrorLogger.h"

class WindowContainer;

class RenderWindow
{
public:
	bool Initialize(WindowContainer* pWindowContainer, HINSTANCE hInst, std::string windowTitle, std::string windowClass, int width, int height);
	bool ProcessMessages();
	~RenderWindow();
	HWND getWindowHandle() const;

private:
	void RegisterWindowClass();
	HWND hwnd;
	HINSTANCE hInstance;
	int m_width = 0, m_height = 0;
	std::string m_windowTitle = "";
	std::wstring m_wideWindowTitle = L"";
	std::string m_windowClass = "";
	std::wstring m_wideWindowClass = L"";
};

