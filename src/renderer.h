#pragma once
#include <windows.h>

//Renderizar a imagem na janela do Windows

class Window;

class Renderer {
    private:
        HWND m_hwnd;
        HDC m_hdc;
        HDC m_memoryDC;
        HBITMAP m_bitmap;
        HBITMAP m_oldBitmap;
        int m_width, m_height;
    
    public:
        Renderer(Window* window);
        ~Renderer();

        bool Initialize();
        void BeginFrame();
        void EndFrame();
        void Clear(COLORREF color);

        void DrawBitmap(HBITMAP bitmap, int x, int y, int width, int height);

        HDC GetMemoryDC() const { return m_memoryDC; }
};