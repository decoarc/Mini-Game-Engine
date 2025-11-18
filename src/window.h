#pragma once
#include <windows.h>

class Input;

//Gerar a Janela do Windows e definir suas propriedades

class Window {
    private:
        HWND m_hwnd;
        HINSTANCE m_hInstance;
        Input* m_input;
        int m_width, m_height;
        char m_title[256];

        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    public:
        Window(int width, int height, const char* title);
        ~Window();

        bool Initialize();
        bool ProcessMessages();
        bool IsRunning() const;
        void SetInput(Input* input) { m_input = input; }

        HWND GetHandle() const { return m_hwnd; }
        int GetWidth() const { return m_width; }
        int GetHeight() const { return m_height; }
};