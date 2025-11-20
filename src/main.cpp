#include "game.h"

//Ponto de entrada do programa Windows
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    Game game;

    //Inicializar jogo
    if (!game.Initialize()) {
        return 1;
    }

    //Executar loop principal
    game.Run();
    
    //Limpar recursos
    game.Shutdown();

    return 0;
}