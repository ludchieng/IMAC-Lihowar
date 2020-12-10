#include "lihowarlib/Game.hpp"

using namespace lihowar;

namespace lihowar {

void Game::handle(SDL_Event e)
{
    switch (e.type) {
        case SDL_QUIT:
            _isRunning = false;
            break;
        case SDL_MOUSEBUTTONUP:
            handleMouseBtn(e);
            break;
        case SDL_KEYDOWN:
            handleKeydown(e);
            break;
        default:
            break;
    }
}


void Game::handleKeydown(SDL_Event e)
{
    switch (e.key.keysym.sym) {
        default:
            break;
    }
}


void Game::handleMouseBtn(SDL_Event e)
{
    switch (e.button.button) {
        case SDL_BUTTON_WHEELUP:
            //GameRenderer.moveFront(0.8);
            break;
        case SDL_BUTTON_WHEELDOWN:
            //cam.moveFront(1.2);
            break;
        default:
            break;
    }
}

}
