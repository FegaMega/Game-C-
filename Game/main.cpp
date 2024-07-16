#include "Game.h"
#include "iostream"

Game* game = nullptr;

int main(int argc, char* argv[])
{
    std::cout << "1" << std::endl;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
    game = new Game();
    std::cout << 15 << std::endl;
    game->init("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, false);
    std::cout << 17 << std::endl;
    while (game->running()) {

        frameStart = SDL_GetTicks();

        game->handleEvents();

        game->update();

        game->render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
            // prints FPS to console
            
            /*
            if (frameTime > 0) {
                std::cout << "FPS " << 1000 / frameTime << std::endl;
            }
            else {
                std::cout << "FPS 1000+" << std::endl;
            }
            */
        }
    }  
    game->clean();
    return 0;
}