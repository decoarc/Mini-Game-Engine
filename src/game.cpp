#include "game.h"
#include "window.h"
#include "renderer.h"
#include "input.h"
#include "sprite.h"
#include <cstdio>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <fstream>

//Construtor - inicializa variáveis
Game::Game() 
    : m_window(nullptr)
    , m_renderer(nullptr)
    , m_input(nullptr)
    , m_running(true)
    , m_fixedTimeStep(1.0f / 60.0f)
{
}

//Destrutor - limpa recursos
Game::~Game() {
    Shutdown();
}

//Inicializa todos os sistemas do jogo
bool Game::Initialize() {
    AllocConsole();
    FILE* pCout;
    FILE* pCerr;
    FILE* pCin;
    freopen_s(&pCout, "CONOUT$", "w", stdout);
    freopen_s(&pCerr, "CONOUT$", "w", stderr);
    freopen_s(&pCin, "CONIN$", "r", stdin);
    
    //Criar janela
    m_window = new Window(800, 600, "Mini Game Engine");
    if (!m_window->Initialize()) {
        return false;
    }
    
    //Criar renderer
    m_renderer = new Renderer(m_window);
    if (!m_renderer->Initialize()) {
        return false;
    }
    
    //Criar input e conectar à janela
    m_input = new Input();
    m_window->SetInput(m_input);
    
    return true;
}

//Loop principal do jogo
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

        if (!m_window->ProcessMessages()) {
            m_running = false;
            break;
        }

        m_input->Update();
        
        accumulator += deltaTime;
        while (accumulator >= FIXED_TIME_STEP) {
            Update(FIXED_TIME_STEP);
            accumulator -= FIXED_TIME_STEP;
        }
        
        Render();
    }
}

//Atualiza lógica do jogo
void Game::Update(float deltaTime) {
    //Lógica do jogo será adicionada aqui
}

//Renderiza tudo na tela
void Game::Render() {
    m_renderer->BeginFrame();
    m_renderer->Clear(RGB(50, 50, 50));

    HDC hdc = m_renderer->GetMemoryDC();
    
    if (!hdc) {
        m_renderer->EndFrame();
        return;
    }
    //Carregar e desenhar sprite de teste
    static Sprite* testSprite = nullptr;
    
    if (!testSprite) {
        testSprite = new Sprite();
        testSprite->LoadFromFile("assets/sprites/test.bmp");
    }

    if (testSprite && testSprite->GetBitmap()) {
        testSprite->Draw(hdc, 200, 100);
    }
    
    
    m_renderer->EndFrame();
    
    //Forçar atualização da janela
    InvalidateRect(m_window->GetHandle(), nullptr, FALSE);
}

//Limpa todos os recursos
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
    
    //Liberar console
    FreeConsole();
}