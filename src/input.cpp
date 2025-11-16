#include "input.h"

// Construtor: inicializa arrays
Input::Input() {
    for (int i = 0; i < KEY_COUNT; i++) {
        m_keys[i] = false;
        m_keysPrevious[i] = false;
    }
}

// Atualiza estado (chamar no início de cada frame)
void Input::Update() {
    // Copia estado atual para anterior
    for (int i = 0; i < KEY_COUNT; i++) {
        m_keysPrevious[i] = m_keys[i];
    }
}

// Tecla está pressionada agora?
bool Input::IsKeyDown(int vkey) const {
    if (vkey < 0 || vkey >= KEY_COUNT) return false;
    return m_keys[vkey];
}

// Tecla foi pressionada neste frame?
bool Input::IsKeyPressed(int vkey) const {
    if (vkey < 0 || vkey >= KEY_COUNT) return false;
    return m_keys[vkey] && !m_keysPrevious[vkey];
}

// Tecla foi solta neste frame?
bool Input::IsKeyReleased(int vkey) const {
    if (vkey < 0 || vkey >= KEY_COUNT) return false;
    return !m_keys[vkey] && m_keysPrevious[vkey];
}

// Chamado quando tecla é pressionada
void Input::OnKeyDown(int vkey) {
    if (vkey >= 0 && vkey < KEY_COUNT) {
        m_keys[vkey] = true;
    }
}

// Chamado quando tecla é solta
void Input::OnKeyUp(int vkey) {
    if (vkey >= 0 && vkey < KEY_COUNT) {
        m_keys[vkey] = false;
    }
}