#pragma once
#include "sprite.h"

// Definir posição/vetor x,y
struct Vector2 {
    float x, y;
    Vector2 (float x = 0, float y = 0) : x(x), y(y) {}
};

class Entity {
    private:
        Vector2 m_position;
        Sprite* m_sprite;
        bool m_isActive;
    
    public:
        Entity();
        Entity(float x, float y, Sprite* sprite);

        void Update(float deltaTime); // atualização de logica
        void Render(HDC hdc); // Desenhar entidade 

        void SetPosition(float x, float y);
        Vector2 GetPosition() const { return m_position; }

        void SetSprite(Sprite* sprite) { m_sprite = sprite; }
        bool IsActive() const { return m_isActive; } //retorna se a entidade ativa
        void SetActive(bool active) { m_isActive = active; } //Define entidade ativa
};