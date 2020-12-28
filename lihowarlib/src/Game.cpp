#include "lihowarlib/Game.hpp"
#include "lihowarlib/GameConfig.hpp"

using namespace std;
using namespace lihowar;

namespace lihowar {


Game::Game(glimac::SDLWindowManager &wm)
: _gController(GameController::instance()),
  _window(wm)
{
    initJoystick();
}

void Game::update()
{
    SDL_PumpEvents();
    if(_window.isKeyPressed(SDL_SCANCODE_Q)) {
        _gController.scene().player().yawAntiClockwise((cfg::DEBUG) ? 100. : 1.);
    }
    if(_window.isKeyPressed(SDL_SCANCODE_E)) {
        _gController.scene().player().yawClockwise((cfg::DEBUG) ? 100. : 1.);
    }
    if(_window.isKeyPressed(SDL_SCANCODE_LEFT, SDL_SCANCODE_A)) {
        _gController.scene().player().moveLeftward((cfg::DEBUG) ? 100. : 1.);
    }
    if(_window.isKeyPressed(SDL_SCANCODE_RIGHT, SDL_SCANCODE_D)) {
        _gController.scene().player().moveRightward((cfg::DEBUG) ? 100. : 1.);
    }
    if(_window.isKeyPressed(SDL_SCANCODE_UP, SDL_SCANCODE_W)) {
        _gController.scene().player().moveForward((cfg::DEBUG) ? 100. : 1.);
    }
    if(_window.isKeyPressed(SDL_SCANCODE_DOWN, SDL_SCANCODE_S)) {
        _gController.scene().player().moveBackward((cfg::DEBUG) ? 100. : 1.);
    }
    if(_window.isKeyPressed(SDL_SCANCODE_LSHIFT)) {
        _gController.scene().player().moveUpward((cfg::DEBUG) ? 100. : 1.);
    }
    if(_window.isKeyPressed(SDL_SCANCODE_LCTRL)) {
        _gController.scene().player().moveDownward((cfg::DEBUG) ? 100. : 1.);
    }

    if (isJoystickOpened()) {
        SDL_JoystickEventState(SDL_QUERY); // Set to query mode for over time events
        SDL_JoystickUpdate();

        // Buttons
        if (SDL_JoystickGetButton(_joystick, 3))
            _gController.scene().player().yawAntiClockwise((cfg::DEBUG) ? 100. : 1.);

        if (SDL_JoystickGetButton(_joystick, 4))
            _gController.scene().player().yawClockwise((cfg::DEBUG) ? 100. : 1.);

        if (SDL_JoystickGetButton(_joystick, 2))
            _gController.scene().player().moveUpward((cfg::DEBUG) ? 100. : 1.);

        if (SDL_JoystickGetButton(_joystick, 1))
            _gController.scene().player().moveDownward((cfg::DEBUG) ? 100. : 1.);


        // Axis
        //if (cfg::DEBUG) cout << "Axis pitch: " << SDL_JoystickGetAxis(_joystick, 1) / 65536.f << endl;
        //if (cfg::DEBUG) cout << "Axis roll : " << SDL_JoystickGetAxis(_joystick, 0) / 65536.f << endl;
        _gController.scene().player().moveRightward( ((cfg::DEBUG) ? 100. : 1.) * SDL_JoystickGetAxis(_joystick, 0) / (.5 * 65536.f) );
        _gController.scene().player().moveForward( ((cfg::DEBUG) ? 100. : 1.) * -SDL_JoystickGetAxis(_joystick, 1) / (.5 * 65536.f) );
        _gController.scene().player().moveUpward( ((cfg::DEBUG) ? 100. : 1.) * -SDL_JoystickGetAxis(_joystick, 2) / (.5 * 65536.f) );
        //_gController.scene().player().roll( 25 * -SDL_JoystickGetAxis(_joystick, 0) / (.5 * 65536.f) );
        //_gController.scene().player().pitch( 25 * SDL_JoystickGetAxis(_joystick, 1) / (.5 * 65536.f) );
        //_gController.scene().player().moveUpward( 25 * -SDL_JoystickGetAxis(_joystick, 2) / (.5 * 65536.f) );

        SDL_JoystickEventState(SDL_ENABLE); // Back to event mode for one shot events
    }
    _gController.update();
}


void Game::handle(SDL_Event e)
{
    // if (cfg::DEBUG) cout << "SDL Event: type: " << (int) e.type << endl;
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
        case SDL_MOUSEWHEEL:
            handleMouseWheel(e);
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
    // if (cfg::DEBUG) cout << "SDL Event: keydown: " << (int) e.key.keysym.sym << endl;
    switch (e.key.keysym.sym) {
        case SDLK_RETURN:
            if (cfg::DEBUG) cout << "pos: " << _gController.scene().player().prs().pos() << endl;
            break;
        case SDLK_l:
            if (cfg::DEBUG) cout << _gController.scene().player().prs().rot() << endl;
        default:
            break;
    }
}


void Game::handleMouseBtn(SDL_Event e)
{
    // if (cfg::DEBUG) cout << "SDL Event: mouse button: " << (int) e.button.button << endl;
    switch (e.button.button) {
        case SDL_BUTTON_MIDDLE:
            _gController.renderer().camera().reset();
            break;
        default:
            break;
    }
}


void Game::handleMouseMotion(SDL_Event e)
{
    // if (cfg::DEBUG) cout << "SDL Event: mouse motion: " << (int) e.button.button << endl;
    if (_window.isMouseButtonPressed(SDL_BUTTON_LEFT)
        && _window.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
        if (e.motion.xrel != 0) {
            _gController.renderer().camera().moveLeft(e.motion.xrel / 50.f);
        }
        if (e.motion.yrel != 0) {
            _gController.renderer().camera().moveUp(-e.motion.yrel / 50.f);
        }
    } else if (_window.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
        if (e.motion.xrel != 0) {
            _gController.renderer().camera().rotateLeft(-e.motion.xrel / 1.5f);
        }
        if (e.motion.yrel != 0) {
            _gController.renderer().camera().rotateUp(-e.motion.yrel / 1.5f);
        }
    }
}

void Game::handleMouseWheel(SDL_Event e)
{
    // if (cfg::DEBUG) cout << "SDL Event: mouse wheel: " << (int) e.button.button << endl;
    if(e.wheel.y != 0)
        _gController.renderer().camera().zoomIn(-.01f * e.wheel.y);
}


void Game::handleJoyBtnDown(SDL_Event e)
{
    // if (cfg::DEBUG) cout << "SDL Event: jbutton: " << (int) e.jbutton.button << "  " << (int) e.jbutton.which << endl;
}


void Game::initJoystick()
{
    if (SDL_NumJoysticks() == 0) {
        if (cfg::DEBUG) cout << "No joystick detected" << endl;
        return;
    }

    _joystick = SDL_JoystickOpen(0);

    if (!_joystick) {
        if (cfg::DEBUG) cerr << "Joystick detected but unable to open it" << endl;
        return;
    }

    if (cfg::DEBUG) cout << "Joystick detected and opened: " << SDL_JoystickName(_joystick) << endl;
    if (cfg::DEBUG) cout << " - " << SDL_JoystickNumAxes(_joystick) << " axes" << endl;
    if (cfg::DEBUG) cout << " - " << SDL_JoystickNumHats(_joystick) << " hats" << endl;
    if (cfg::DEBUG) cout << " - " << SDL_JoystickNumButtons(_joystick) << " buttons" << endl;
    if (cfg::DEBUG) cout << " - " << SDL_JoystickNumBalls(_joystick) << " balls" << endl;
}

}
