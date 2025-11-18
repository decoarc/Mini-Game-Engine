#include "game.h"
#include "window.h"
#include "renderer.h"
#include "input.h"
#include <cstdio>
#include <io.h>
#include <fcntl.h>
#include <windows.h>

Game::Game() 
    : m_window(nullptr)
    , m_renderer(nullptr)
    , m_input(nullptr)
    , m_running(true)
    , m_fixedTimeStep(1.0f / 60.0f)
{
}

Game::~Game() {
    Shutdown();
}

bool Game::Initialize() {
    AllocConsole();
    FILE* pCout;
    FILE* pCerr;
    FILE* pCin;
    freopen_s(&pCout, "CONOUT$", "w", stdout);
    freopen_s(&pCerr, "CONOUT$", "w", stderr);
    freopen_s(&pCin, "CONIN$", "r", stdin);
    
    printf("Console initialized. Press any key to test...\n");
    
    m_window = new Window(800, 600, "Mini Game Engine");
    if (!m_window->Initialize()) {
        return false;
    }
    
    m_renderer = new Renderer(m_window);
    if (!m_renderer->Initialize()) {
        return false;
    }
    
    m_input = new Input();
    m_window->SetInput(m_input);
    
    return true;
}

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

void Game::Update(float deltaTime) {
    for (int i = 0; i < 256; i++) {
        if (m_input->IsKeyPressed(i)) {
            printf("Key %d (0x%02X) is pressed\n", i, i);
            fflush(stdout);
        }
    }
    
    static bool spaceWasDown = false;
    if (m_input->IsKeyDown(VK_SPACE)) {
        if (!spaceWasDown) {
            printf("The Space key was pressed!\n");
            fflush(stdout);
            spaceWasDown = true;
        }
    } else {
        spaceWasDown = false;
    }
}

void Game::Render() {
    m_renderer->BeginFrame();
    m_renderer->Clear(RGB(50, 50, 50));
    m_renderer->EndFrame();
}

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
    
    FreeConsole();
}