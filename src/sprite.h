#pragma once
#include <windows.h>

//Carregar a imagem do sprite e definir suas propriedades

class Sprite {
    private:
        HBITMAP m_bitmap;
        int m_width, m_height;
    public:
        Sprite();
        ~Sprite();

        bool LoadFromFile(const char* filename);
        void Draw(HDC hdc, int x, int y);
        int GetWidth() const { return m_width; }
        int GetHeight() const { return m_height; }
        HBITMAP GetBitmap() const { return m_bitmap; }
};