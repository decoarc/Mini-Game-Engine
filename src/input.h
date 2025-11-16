#pragma once
#include <windows.h>

class Input {
    private:
        static const int KEY_COUNT = 256;
        bool m_keys[KEY_COUNT];
        bool m_keysPrevious[KEY_COUNT];
    
    public:
        Input();

        void Update();

        bool IsKeyDown(int vkey) const;
        bool IsKeyPressed(int vkey) const;
        bool IsKeyReleased(int vkey) const;

        void OnKeyDown(int vkey);
        void OnKeyUp(int vkey);
};