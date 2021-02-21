#include "Engine.h"

int WINAPI wWinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrevInst,
	_In_ LPWSTR lpCmdLine, _In_ int nCmdLine)
{
	Engine engine;

	engine.Initialize(hInst, "Hello window", "mainWindow", 800, 600);

	while (engine.ProcessMessages()) {
		engine.Update();
		engine.Render();
	}

	return S_OK;
}