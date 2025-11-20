#include "renderer.h"
#include "window.h"

//Construtor - inicializa variáveis
Renderer::Renderer(Window* window)
    : m_hwnd(window->GetHandle())
    , m_hdc(nullptr)
    , m_memoryDC(nullptr)
    , m_bitmap(nullptr)
    , m_oldBitmap(nullptr)
    , m_width(window->GetWidth())
    , m_height(window->GetHeight())
{
}

//Destrutor - limpa recursos
Renderer::~Renderer() {
    if (m_memoryDC && m_oldBitmap) {
        SelectObject(m_memoryDC, m_oldBitmap);
    }
    if (m_bitmap) {
        DeleteObject(m_bitmap);
    }
    if (m_memoryDC) {
        DeleteDC(m_memoryDC);
    }
    if (m_hdc) {
        ReleaseDC(m_hwnd, m_hdc);
    }
}

//Inicializa o renderer - cria device contexts e bitmap
bool Renderer::Initialize() {
    m_hdc = ::GetDC(m_hwnd);
    if (!m_hdc) {
        return false;
    }
    
    // Criar device context em memória para double buffering
    m_memoryDC = CreateCompatibleDC(m_hdc);
    if (!m_memoryDC) {
        return false;
    }
    
    // Criar bitmap para o buffer
    m_bitmap = CreateCompatibleBitmap(m_hdc, m_width, m_height);
    if (!m_bitmap) {
        return false;
    }
    
    // Selecionar bitmap no DC
    m_oldBitmap = (HBITMAP)SelectObject(m_memoryDC, m_bitmap);
    
    return true;
}

//Inicia frame - prepara buffer para desenhar
void Renderer::BeginFrame() {
    // Buffer já está pronto para desenhar
}

//Finaliza frame - copia buffer para tela
void Renderer::EndFrame() {
    if (m_hdc && m_memoryDC) {
        BitBlt(m_hdc, 0, 0, m_width, m_height, m_memoryDC, 0, 0, SRCCOPY);
    }
}

//Limpa tela com uma cor
void Renderer::Clear(COLORREF color) {
    RECT rect = { 0, 0, m_width, m_height };
    HBRUSH brush = CreateSolidBrush(color);
    FillRect(m_memoryDC, &rect, brush);
    DeleteObject(brush);
}

//Desenha um bitmap na posição especificada
void Renderer::DrawBitmap(HBITMAP bitmap, int x, int y, int width, int height) {
    HDC tempDC = CreateCompatibleDC(m_memoryDC);
    HBITMAP oldBmp = (HBITMAP)SelectObject(tempDC, bitmap);
    
    BitBlt(m_memoryDC, x, y, width, height, tempDC, 0, 0, SRCCOPY);
    
    SelectObject(tempDC, oldBmp);
    DeleteDC(tempDC);
}