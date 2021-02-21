#include "WindowContainer.h"

bool RenderWindow::Initialize(WindowContainer* pWindowContainer, HINSTANCE hInst, std::string windowTitle, std::string windowClass, int width, int height)
{
    hInstance = hInst;
    m_windowTitle = windowTitle;
    m_wideWindowTitle = StringHelper::StringToWide(windowTitle);
    m_windowClass = windowClass;
    m_wideWindowClass = StringHelper::StringToWide(windowClass);
    m_width = width;
    m_height = height;

    RegisterWindowClass();

    

    hwnd = CreateWindowEx(0, m_wideWindowClass.c_str(),
        m_wideWindowTitle.c_str(),
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        0, 0,
        m_width, m_height,
        NULL, NULL,
        hInstance, pWindowContainer);

    if (hwnd == NULL) {
        ErrorLogger::Log(GetLastError(), "Window creation failed for " + m_windowTitle);
        return false;
    }

    ShowWindow(hwnd, SW_SHOW);
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);

    return true;
}

LRESULT CALLBACK handleMessageRedirect(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg) {
    case WM_DESTROY:
        DestroyWindow(hwnd);
        break;

    default:
        WindowContainer* const pWindow = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        return pWindow->windowProc(hwnd, msg, wparam, lparam);
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}

LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg) {
    case WM_NCCREATE:
    {
        const CREATESTRUCTW* pCreate = reinterpret_cast<CREATESTRUCTW*>(lparam);
        WindowContainer* pWindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);

        if (pWindow == nullptr) {
            ErrorLogger::Log("Window pointer is uninitialized while windowProc(WM_NCCREATE).");
            exit(-1);
        }

        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
        SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(handleMessageRedirect));
        pWindow->windowProc(hwnd, msg, wparam, lparam);

        return pWindow->windowProc(hwnd, msg, wparam, lparam);
    }
    default:
        return DefWindowProc(hwnd, msg, wparam, lparam);
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}

bool RenderWindow::ProcessMessages()
{
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) {
        DispatchMessage(&msg);
        TranslateMessage(&msg);
    }

    if (msg.message == WM_NULL) {
        if (!IsWindow(hwnd)) {
            this->hwnd = NULL;
            UnregisterClass(m_wideWindowClass.c_str(), hInstance);
            return false;
        }
    }

    return true;
}

RenderWindow::~RenderWindow()
{
    if (hwnd != NULL) {
        DestroyWindow(hwnd);
        UnregisterClass(m_wideWindowClass.c_str(), hInstance);
    }
}

HWND RenderWindow::getWindowHandle() const
{
    return this->hwnd;
}

void RenderWindow::RegisterWindowClass()
{
    WNDCLASSEX wndClass;
    wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wndClass.lpfnWndProc = HandleMessageSetup;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = NULL;
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = NULL;
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = m_wideWindowClass.c_str();
    wndClass.hIconSm = NULL;
    wndClass.cbSize = sizeof(WNDCLASSEX);
    RegisterClassEx(&wndClass);
}
