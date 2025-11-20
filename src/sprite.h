#pragma once
#include <windows.h>

//Carregar a imagem do sprite e definir suas propriedades

class Sprite {
    private:
        HBITMAP m_bitmap; //armazena handle 
        int m_width, m_height;
    public:
        Sprite();
        ~Sprite();

        bool LoadFromFile(const char* filename); //carregar imagem == filename
        void Draw(HDC hdc, int x, int y); //desenhar a sprite 
        int GetWidth() const { return m_width; } // pegar with e alvar no m_with
        int GetHeight() const { return m_height; } // pegar height e salvar no m_heught
        HBITMAP GetBitmap() const { return m_bitmap; } //carrega o handle do m_bitmap
};