#include "Game.h"
#include "iostream"

Game* game = nullptr;

int main(int argc, char* argv[])
{
    
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, false);


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