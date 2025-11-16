#include "game.h"
#include "window.h"
#include "renderer.h"
#include "input.h"

// Construtor: inicializa tudo como nullptr ou valores padrão
Game::Game() 
    : m_window(nullptr)
    , m_renderer(nullptr)
    , m_input(nullptr)
    , m_running(true)
    , m_fixedTimeStep(1.0f / 60.0f)
{
}

// Destrutor: limpa recursos
Game::~Game() {
    Shutdown();
}

// Inicializa todos os sistemas
bool Game::Initialize() {
    // Criar janela
    m_window = new Window(800, 600, "Mini Game Engine");
    if (!m_window->Initialize()) {
        return false;
    }
    
    // Criar renderer
    m_renderer = new Renderer(m_window);
    if (!m_renderer->Initialize()) {
        return false;
    }
    
    // Criar input
    m_input = new Input();
    
    return true;
}

// Loop principal (mover do main.cpp para cá)
void Game::Run() {
    const float FIXED_TIME_STEP = 1.0f / 60.0f;
    float accumulator = 0.0f;

    LARGE_INTEGER frequency, lastTime, currentTime;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&lastTime);

    while (m_running) {
        QueryPerformanceCounter(&currentTime);
        float deltaTime = (currentTime.QuadPart - lastTime.QuadPart) / (float)frequency.QuadPart;
        lastTime = currentTime;

        m_window->ProcessMessages();
        m_input->Update();
        
        accumulator += deltaTime;
        while (accumulator >= FIXED_TIME_STEP) {
            Update(FIXED_TIME_STEP);
            accumulator -= FIXED_TIME_STEP;
        }
        
        Render();
    }
}

// Atualiza lógica do jogo
void Game::Update(float deltaTime) {
    // Por enquanto vazio - você adicionará lógica aqui depois
}

// Renderiza tudo
void Game::Render() {
    m_renderer->BeginFrame();
    m_renderer->Clear(RGB(50, 50, 50)); // Cor cinza escuro
    
    // Renderizar entidades aqui depois
    
    m_renderer->EndFrame();
}

// Limpa recursos
void Game::Shutdown() {
    if (m_renderer) {
        delete m_renderer;
        m_renderer = nullptr;
    }
    if (m_input) {
        delete m_input;
        m_input = nullptr;
    }
    if (m_window) {
        delete m_window;
        m_window = nullptr;
    }
}