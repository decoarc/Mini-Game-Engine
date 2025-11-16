#pragma once
#include "sprite.h"

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

        void Update(float deltaTime);
        void Render(HDC hdc);

        void SetPosition(float x, float y);
        Vector2 GetPosition() const { return m_position; }

        void SetSprite(Sprite* sprite) { m_sprite = sprite; }
        bool IsActive() const { return m_isActive; }
        void SetActive(bool active) { m_isActive = active; }
};