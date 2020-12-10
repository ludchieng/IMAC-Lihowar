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

}
