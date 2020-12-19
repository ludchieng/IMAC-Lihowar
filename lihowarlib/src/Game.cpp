#include "lihowarlib/Game.hpp"

using namespace std;
using namespace lihowar;

namespace lihowar {

void Game::update()
{
    SDL_PumpEvents();
    Uint8* keystate = SDL_GetKeyState(NULL);
    if(keystate[SDLK_LEFT]) {
        _gController.scene().player().applyForce( glm::vec3(0., 0., -.4) );
    }
    if(keystate[SDLK_RIGHT]) {
        _gController.scene().player().applyForce( glm::vec3(0., 0., .4) );
    }
    if(keystate[SDLK_UP]) {
        _gController.scene().player().applyForce( glm::vec3(.4, 0., 0.) );
    }
    if(keystate[SDLK_DOWN]) {
        _gController.scene().player().applyForce( glm::vec3(-.4, 0., 0.) );
    }
    if(keystate[SDLK_p]) {
        _gController.scene().player().applyForce( glm::vec3(0., .2, 0.) );
    }
    if(keystate[SDLK_m]) {
        _gController.scene().player().applyForce( glm::vec3(0., -.2, 0.) );
    }
    if(keystate[SDLK_g]) {
        _gController.scene().player().applyTorque( glm::vec3(.002, 0., 0.) );
    }
    if(keystate[SDLK_h]) {
        _gController.scene().player().applyTorque( glm::vec3(0., .002, 0.) );
    }
    if(keystate[SDLK_j]) {
        _gController.scene().player().applyTorque( glm::vec3(0., 0., .002) );
    }

    _gController.update();
}


void Game::handle(SDL_Event e)
{
    switch (e.type) {
        case SDL_QUIT:
            _isRunning = false;
            break;
        case SDL_MOUSEBUTTONUP:
            handleMouseBtn(e);
            break;
        case SDL_MOUSEMOTION:
            handleMouseMotion(e);
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
    // if (DEBUG) cout << "SDL Event: keydown: " << (int) e.key.keysym.sym << endl;
    switch (e.key.keysym.sym) {
        default:
            break;
    }
}


void Game::handleMouseBtn(SDL_Event e)
{
    // if (DEBUG) cout << "SDL Event: mouse button: " << (int) e.button.button << endl;
    switch (e.button.button) {
        case SDL_BUTTON_WHEELUP:
            _gController.renderer().camera().moveFront(-.01f);
            break;
        case SDL_BUTTON_WHEELDOWN:
            _gController.renderer().camera().moveFront(.01f);
            break;
        default:
            break;
    }
}


void Game::handleMouseMotion(SDL_Event e)
{
    if (_windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
        if (e.motion.xrel != 0) {
            _gController.renderer().camera().rotateLeft(-e.motion.xrel / 1.5f);
        }
        if (e.motion.yrel != 0) {
            _gController.renderer().camera().rotateUp(-e.motion.yrel / 1.5f);
        }
    }
}

}
