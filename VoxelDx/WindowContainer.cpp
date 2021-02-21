#include "WindowContainer.h"

WindowContainer::WindowContainer()
{
    static bool RAW_INPUT_INITALIZED = false;

    if (!RAW_INPUT_INITALIZED) {
        RAWINPUTDEVICE dev;
        dev.usUsagePage = 0x01;
        dev.usUsage = 0x02;
        dev.dwFlags = 0;
        dev.hwndTarget = NULL;

        if (!RegisterRawInputDevices(&dev, 1, sizeof(dev))) {
            ErrorLogger::Log(GetLastError(), "Failed to initialize raw input device.");
            exit(-1);
        }
    }
}

LRESULT WindowContainer::windowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg) {
    //KEYBOARD MESSAGES
    case WM_KEYUP:
    {
        unsigned char ch = static_cast<unsigned char>(wparam);
        this->m_keyboard.onKeyReleased(ch);
        return 0;
    }

    case WM_KEYDOWN:
    {
        unsigned char ch = static_cast<unsigned char>(wparam);
        this->m_keyboard.onKeyPressed(ch);
        return 0;
    }

    case WM_CHAR:
    {
        unsigned char ch = static_cast<unsigned char>(wparam);

        if (this->m_keyboard.isAutoRepeatChars()) {
            m_keyboard.onChar(ch);
            return 0;
        }

        const bool pressed = lparam & 0x40000000;
        if (!pressed)
            m_keyboard.onChar(ch);

        return 0;
    }

    // MOUSE MESSAGES
    case WM_MOUSEMOVE:
    {
        int x = LOWORD(lparam);
        int y = HIWORD(lparam);

        m_mouse.onMove(x, y);

        return 0;
    }

    case WM_LBUTTONDOWN:
    {
        int x = LOWORD(lparam);
        int y = HIWORD(lparam);

        m_mouse.onPressLeft(x, y);
        return 0;
    }

    case WM_RBUTTONDOWN:
    {
        int x = LOWORD(lparam);
        int y = HIWORD(lparam);

        m_mouse.onPressRight(x, y);
        return 0;
    }

    case WM_MBUTTONDOWN:
    {
        int x = LOWORD(lparam);
        int y = HIWORD(lparam);

        m_mouse.onPressWheel(x, y);
        return 0;
    }

    case WM_RBUTTONUP:
    {
        int x = LOWORD(lparam);
        int y = HIWORD(lparam);

        m_mouse.onReleaseRight(x, y);
        return 0;
    }

    case WM_LBUTTONUP:
    {
        int x = LOWORD(lparam);
        int y = HIWORD(lparam);

        m_mouse.onReleaseLeft(x, y);
        return 0;
    }

    case WM_MBUTTONUP:
    {
        int x = LOWORD(lparam);
        int y = HIWORD(lparam);

        m_mouse.onReleaseRight(x, y);
        return 0;
    }

    case WM_MOUSEWHEEL:
    {
        int x = LOWORD(lparam);
        int y = HIWORD(lparam);

        if (GET_WHEEL_DELTA_WPARAM(wparam) > 0) {
            m_mouse.onWheelUp(x, y);
            return 0;
        }

        m_mouse.onWheelDown(x, y);
        return 0;
    }

    case WM_INPUT:
    {
        UINT dataSize;
        ZeroMemory(&dataSize, sizeof(dataSize));
        GetRawInputData(reinterpret_cast<HRAWINPUT>(lparam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));

        if (dataSize > 0) {
            std::unique_ptr<BYTE[]> rawData = std::make_unique<BYTE[]>(dataSize);
            if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lparam), RID_INPUT, rawData.get(), &dataSize, sizeof(RAWINPUTHEADER))) {
                RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawData.get());
                if (raw->header.dwType == RIM_TYPEMOUSE) {
                    m_mouse.onMoveRaw(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
                }
            }
        }

        return DefWindowProc(hwnd, msg, wparam, lparam);
    }

    default:
        return DefWindowProc(hwnd, msg, wparam, lparam);
    }
}
