#include "window.h"
#include <cstring>

// Variável estática para acessar a instância no callback
static Window* g_windowInstance = nullptr;

// Construtor
Window::Window(int width, int height, const char* title)
    : m_hwnd(nullptr)
    , m_hInstance(GetModuleHandle(nullptr))
    , m_width(width)
    , m_height(height)
{
    // Copiar título (você pode usar std::string depois)
    strcpy_s(m_title, sizeof(m_title), title);
}

// Destrutor
Window::~Window() {
    if (m_hwnd) {
        DestroyWindow(m_hwnd);
    }
}

// Inicializa a janela
bool Window::Initialize() {
    // Registrar classe de janela
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = m_hInstance;
    wc.lpszClassName = "MiniGameEngineWindow";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    
    if (!RegisterClass(&wc)) {
        return false;
    }
    
    // Criar janela
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
    
    // Guardar ponteiro da instância
    g_windowInstance = this;
    SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
    
    ShowWindow(m_hwnd, SW_SHOW);
    UpdateWindow(m_hwnd);
    
    return true;
}

// Processa mensagens do Windows
void Window::ProcessMessages() {
    MSG msg = {};
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

// Verifica se janela ainda está rodando
bool Window::IsRunning() const {
    return m_hwnd != nullptr;
}

// Callback de mensagens do Windows
LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    
    switch (uMsg) {
        case WM_DESTROY:
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}