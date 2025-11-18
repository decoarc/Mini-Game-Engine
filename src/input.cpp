#include "input.h"

Input::Input() {
    for (int i = 0; i < KEY_COUNT; i++) {
        m_keys[i] = false;
        m_keysPrevious[i] = false;
    }
}

void Input::Update() {
    for (int i = 0; i < KEY_COUNT; i++) {
        m_keysPrevious[i] = m_keys[i];
    }
}

bool Input::IsKeyDown(int vkey) const {
    if (vkey < 0 || vkey >= KEY_COUNT) return false;
    return m_keys[vkey];
}

bool Input::IsKeyPressed(int vkey) const {
    if (vkey < 0 || vkey >= KEY_COUNT) return false;
    return m_keys[vkey] && !m_keysPrevious[vkey];
}

bool Input::IsKeyReleased(int vkey) const {
    if (vkey < 0 || vkey >= KEY_COUNT) return false;
    return !m_keys[vkey] && m_keysPrevious[vkey];
}

void Input::OnKeyDown(int vkey) {
    if (vkey >= 0 && vkey < KEY_COUNT) {
        m_keys[vkey] = true;
    }
}

void Input::OnKeyUp(int vkey) {
    if (vkey >= 0 && vkey < KEY_COUNT) {
        m_keys[vkey] = false;
    }
}