#include "Engine.h"

bool Engine::Initialize(HINSTANCE hInst, std::string windowTitle, std::string windowClass, int width, int height)
{
    this->m_keyboard.enableAutoRepeatChars();

    if (!this->render_window.Initialize(this, hInst, windowTitle, windowClass, width, height))
        return false;

    if (!this->graphics.Initialize(this->render_window.getWindowHandle(), width, height))
        return false;

    return true;
}

bool Engine::ProcessMessages()
{
    return render_window.ProcessMessages();
}

void Engine::Update()
{
    while (!m_keyboard.isBufferCharEmpty()) {
        unsigned char ch = m_keyboard.readChar();
    }

    while (!m_keyboard.isBufferKeyEmpty()) {
        KeyboardEvent e = m_keyboard.readKey();
    }

    while (!m_mouse.isEventBufferEmpty()) {
        MouseEvent e = m_mouse.readEvent();
    }
}

void Engine::Render()
{
    graphics.Render();
}
