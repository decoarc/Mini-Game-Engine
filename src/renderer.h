#pragma once
#include <windows.h>

//Renderizar a imagem na janela do Windows

class Window;

class Renderer {
    private:
        HWND m_hwnd; //handle da janela
        HDC m_hdc; //device context da janela
        HDC m_memoryDC; //device context em memória para double buffering
        HBITMAP m_bitmap; //bitmap do buffer
        HBITMAP m_oldBitmap; //bitmap anterior (para restaurar)
        int m_width, m_height; //largura e altura
    
    public:
        Renderer(Window* window);
        ~Renderer();

        bool Initialize(); //inicializa o renderer
        void BeginFrame(); //inicia frame de renderização
        void EndFrame(); //finaliza frame e copia para tela
        void Clear(COLORREF color); //limpa tela com cor

        void DrawBitmap(HBITMAP bitmap, int x, int y, int width, int height); //desenha bitmap

        HDC GetMemoryDC() const { return m_memoryDC; } //retorna device context em memória
};