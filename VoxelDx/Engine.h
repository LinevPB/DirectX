#pragma once
#include "WindowContainer.h"

class Engine : WindowContainer
{
public:
	bool Initialize(HINSTANCE hInst, std::string windowTitle, std::string windowClass, int width, int height);
	bool ProcessMessages();
	void Update();
	void Render();

	WindowContainer windowContainer;
	Graphics graphics;
};

