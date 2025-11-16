#pragma once
#include "window.h"
#include "renderer.h"
#include "input.h"
#include "entity.h"
#include <vector>

class Game {
    private:
        Window* m_window;
        Renderer* m_renderer;
        Input* m_input;

        std::vector<Entity*> m_entities;

        bool m_running;
        float m_fixedTimeStep;

    public:
        Game();
        ~Game();

        bool Initialize();
        void Run();
        void Shutdown();

    private:
        void Update(float deltaTime);
        void Render();
        void ProcessInput();
};