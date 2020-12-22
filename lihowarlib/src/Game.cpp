#include "lihowarlib/Game.hpp"

using namespace std;
using namespace lihowar;

namespace lihowar {


Game::Game(glimac::SDLWindowManager &wm)
:_gController(GameController::instance()),
_windowManager(wm)
{
    initJoystick();
}

void Game::update()
{
    SDL_PumpEvents();
    Uint8* keystate = SDL_GetKeyState(NULL);
    if(keystate[SDLK_LEFT]) {
        _gController.scene().player().applyForce( glm::vec3(0., 0., -.04) );
    }
    if(keystate[SDLK_RIGHT]) {
        _gController.scene().player().applyForce( glm::vec3(0., 0., .04) );
    }
    if(keystate[SDLK_UP]) {
        _gController.scene().player().applyForce( glm::vec3(.04, 0., 0.) );
    }
    if(keystate[SDLK_DOWN]) {
        _gController.scene().player().applyForce( glm::vec3(-.04, 0., 0.) );
    }
    if(keystate[SDLK_p]) {
        _gController.scene().player().applyForce( glm::vec3(0., .02, 0.) );
    }
    if(keystate[SDLK_m]) {
        _gController.scene().player().applyForce( glm::vec3(0., -.02, 0.) );
    }
    if(keystate[SDLK_g]) {
        _gController.scene().player().applyTorque( glm::vec3(.0005, 0., 0.) );
    }
    if(keystate[SDLK_h]) {
        _gController.scene().player().applyTorque( glm::vec3(0., .0005, 0.) );
    }
    if(keystate[SDLK_j]) {
        _gController.scene().player().applyTorque( glm::vec3(0., 0., .0005) );
    }

    if (isJoystickOpened()) {
        SDL_JoystickEventState(SDL_QUERY); // Set to query mode to retrieve axis current position
        SDL_JoystickUpdate();
        float valueRoll = SDL_JoystickGetAxis(_joystick, 0) / 65536.f;
        float valuePitch = - SDL_JoystickGetAxis(_joystick, 1) / 65536.f;
        float valueThrottle = - SDL_JoystickGetAxis(_joystick, 2) / 65536.f;
        _gController.scene().player().applyForce( valueRoll * glm::vec3(0., 0., .04) );
        _gController.scene().player().applyForce( valuePitch * glm::vec3(.04, 0., 0.) );
        _gController.scene().player().applyForce( valueThrottle * glm::vec3(0., .04, 0.) );

        SDL_JoystickEventState(SDL_ENABLE); // Back to event mode for jbutton handling
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
        case SDL_JOYBUTTONDOWN:
            handleJoyBtnDown(e);
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


void Game::handleJoyBtnDown(SDL_Event e)
{
    if (DEBUG) cout << "jbutton: " << (int) e.jbutton.button << "  " << (int) e.jbutton.which << endl;
}


void Game::initJoystick()
{
    if (SDL_NumJoysticks() == 0) {
        if (DEBUG) cout << "No joystick detected" << endl;
        return;
    }

    _joystick = SDL_JoystickOpen(0);

    if (!_joystick) {
        if (DEBUG) cerr << "Joystick detected but unable to open it" << endl;
        return;
    }

    if (DEBUG) cout << "Joystick detected and opened: " << SDL_JoystickName(0) << endl;
    if (DEBUG) cout << " - " << SDL_JoystickNumAxes(_joystick) << " axes" << endl;
    if (DEBUG) cout << " - " << SDL_JoystickNumHats(_joystick) << " hats" << endl;
    if (DEBUG) cout << " - " << SDL_JoystickNumButtons(_joystick) << " buttons" << endl;
    if (DEBUG) cout << " - " << SDL_JoystickNumBalls(_joystick) << " balls" << endl;
}

}
