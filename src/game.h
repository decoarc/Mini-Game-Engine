#pragma once
#include "window.h"
#include "renderer.h"
#include "input.h"
#include "entity.h"
#include <vector>

//Classe principal do jogo - gerencia todos os sistemas
class Game {
    private:
        Window* m_window; //janela do jogo
        Renderer* m_renderer; //sistema de renderização
        Input* m_input; //sistema de entrada

        std::vector<Entity*> m_entities; //lista de entidades do jogo

        bool m_running; //define se o jogo está rodando
        float m_fixedTimeStep; //tempo fixo para atualização

    public:
        Game();
        ~Game();

        bool Initialize(); //inicializa todos os sistemas
        void Run(); //loop principal do jogo
        void Shutdown(); //limpa recursos e encerra

    private:
        void Update(float deltaTime); //atualiza lógica do jogo
        void Render(); //renderiza tudo na tela
        void ProcessInput(); //processa entrada do usuário
};