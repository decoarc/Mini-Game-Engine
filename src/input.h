#pragma once
#include <windows.h>

//Sistema de entrada - gerencia teclado
class Input {
    private:
        static const int KEY_COUNT = 256; //número total de teclas
        bool m_keys[KEY_COUNT]; //estado atual das teclas
        bool m_keysPrevious[KEY_COUNT]; //estado anterior das teclas
    
    public:
        Input();

        void Update(); //atualiza estado das teclas

        bool IsKeyDown(int vkey) const; //verifica se tecla está pressionada
        bool IsKeyPressed(int vkey) const; //verifica se tecla foi pressionada neste frame
        bool IsKeyReleased(int vkey) const; //verifica se tecla foi solta neste frame

        void OnKeyDown(int vkey); //chamado quando tecla é pressionada
        void OnKeyUp(int vkey); //chamado quando tecla é solta
};