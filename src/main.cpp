#include "game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    Game game;

    if (!game.Initialize()) {
        return 1;
    }

    game.Run();
    game.Shutdown();

    return 0;
}