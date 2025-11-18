#include "window.h"
#include "input.h"
#include <cstring>
#include <cstdio>

static Window* g_windowInstance = nullptr;

Window::Window(int width, int height, const char* title)
    : m_hwnd(nullptr)
    , m_hInstance(GetModuleHandle(nullptr))
    , m_input(nullptr)
    , m_width(width)
    , m_height(height)
{
    strcpy_s(m_title, sizeof(m_title), title);
}

Window::~Window() {
    if (m_hwnd) {
        DestroyWindow(m_hwnd);
    }
}

bool Window::Initialize() {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = m_hInstance;
    wc.lpszClassName = "MiniGameEngineWindow";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    
    if (!RegisterClass(&wc)) {
        return false;
    }
    
    m_hwnd = CreateWindowEx(
        0,
        "MiniGameEngineWindow",
        m_title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        m_width, m_height,
        nullptr, nullptr,
        m_hInstance,
        nullptr
    );
    
    if (!m_hwnd) {
        return false;
    }
    
    g_windowInstance = this;
    SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
    
    ShowWindow(m_hwnd, SW_SHOW);
    UpdateWindow(m_hwnd);
    SetFocus(m_hwnd);
    
    return true;
}

bool Window::ProcessMessages() {
    MSG msg = {};
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
            return false;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}

bool Window::IsRunning() const {
    return m_hwnd != nullptr;
}

LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    
    switch (uMsg) {
        case WM_DESTROY:
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;

        case WM_KEYDOWN:
            if (window && window->m_input) {
                window->m_input->OnKeyDown((int)wParam);
            }
            break;
        
        case WM_KEYUP:
            if (window && window->m_input) {
                window->m_input->OnKeyUp((int)wParam);
            }
            break;
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}