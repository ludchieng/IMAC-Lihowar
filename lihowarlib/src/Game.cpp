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
    if(keystate[SDLK_a]) {
        _gController.scene().player().yawAntiClockwise(10.);
    }
    if(keystate[SDLK_e]) {
        _gController.scene().player().yawClockwise(10.);
    }
    if(keystate[SDLK_LEFT] || keystate[SDLK_q]) {
        _gController.scene().player().moveLeftward(25.);
    }
    if(keystate[SDLK_RIGHT] || keystate[SDLK_d]) {
        _gController.scene().player().moveRightward(25.);
    }
    if(keystate[SDLK_UP] || keystate[SDLK_z]) {
        _gController.scene().player().moveForward(25.);
    }
    if(keystate[SDLK_DOWN] || keystate[SDLK_s]) {
        _gController.scene().player().moveBackward(25.);
    }
    if(keystate[SDLK_LSHIFT]) {
        _gController.scene().player().moveUpward(20.);
    }
    if(keystate[SDLK_LCTRL]) {
        _gController.scene().player().moveDownward(20.);
    }

    if (isJoystickOpened()) {
        SDL_JoystickEventState(SDL_QUERY); // Set to query mode for over time events
        SDL_JoystickUpdate();

        // Buttons
        if (SDL_JoystickGetButton(_joystick, 3))
            _gController.scene().player().yawAntiClockwise(10);

        if (SDL_JoystickGetButton(_joystick, 4))
            _gController.scene().player().yawClockwise(10);

        if (SDL_JoystickGetButton(_joystick, 2))
            _gController.scene().player().moveUpward(20);

        if (SDL_JoystickGetButton(_joystick, 1))
            _gController.scene().player().moveDownward(20);


        // Axis
        //if (DEBUG) cout << "Axis pitch: " << SDL_JoystickGetAxis(_joystick, 1) / 65536.f << endl;
        //if (DEBUG) cout << "Axis roll : " << SDL_JoystickGetAxis(_joystick, 0) / 65536.f << endl;
        _gController.scene().player().moveRightward( 25 * SDL_JoystickGetAxis(_joystick, 0) / (.5 * 65536.f) );
        _gController.scene().player().moveForward( 25 * -SDL_JoystickGetAxis(_joystick, 1) / (.5 * 65536.f) );
        _gController.scene().player().moveUpward( 25 * -SDL_JoystickGetAxis(_joystick, 2) / (.5 * 65536.f) );
        //_gController.scene().player().roll( 25 * -SDL_JoystickGetAxis(_joystick, 0) / (.5 * 65536.f) );
        //_gController.scene().player().pitch( 25 * SDL_JoystickGetAxis(_joystick, 1) / (.5 * 65536.f) );
        //_gController.scene().player().moveUpward( 25 * -SDL_JoystickGetAxis(_joystick, 2) / (.5 * 65536.f) );

        SDL_JoystickEventState(SDL_ENABLE); // Back to event mode for one shot events
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
        case SDLK_RETURN:
            if (DEBUG) cout << "pos: " << _gController.scene().player().prs().pos() << endl;
            break;
        case SDLK_l:
            if (DEBUG) cout << _gController.scene().player().prs().rot() << endl;
        default:
            break;
    }
}


void Game::handleMouseBtn(SDL_Event e)
{
    // if (DEBUG) cout << "SDL Event: mouse button: " << (int) e.button.button << endl;
    switch (e.button.button) {
        case SDL_BUTTON_MIDDLE:
            _gController.renderer().camera().reset();
            break;
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
    if (_windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)
     && _windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
        if (e.motion.xrel != 0) {
            _gController.renderer().camera().moveLeft(e.motion.xrel / 50.f);
        }
        if (e.motion.yrel != 0) {
            _gController.renderer().camera().moveUp(-e.motion.yrel / 50.f);
        }
    } else if (_windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
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
    //if (DEBUG) cout << "jbutton: " << (int) e.jbutton.button << "  " << (int) e.jbutton.which << endl;
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
