/*
 *  Copyright (c) 2020-2021 Lihowar
 *
 *  This software is licensed under OSEF License.
 *
 *  The "Software" is defined as the pieces of code, the documentation files, the config
 *  files, the textures assets, the Wavefront OBJ assets, the screenshot image, the sound
 *  effects and music associated with.
 *
 *  This Software is licensed under OSEF License which means IN ACCORDANCE WITH THE LICENSE
 *  OF THE DEPENDENCIES OF THE SOFTWARE, you can use it as you want for any purpose, but
 *  it comes with no guarantee of any kind, provided that you respects the license of the
 *  software dependencies of the piece of code you want to reuse. The dependencies are
 *  listed at the end of the README given in the directory root of the Lihowar repository.
 */
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
    if (cfg::DEBUG) cout << "[Game::Game] END" << endl
            << "================================" << endl << endl << endl;
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
        _gController.scene().player().moveRightward(
                ((cfg::DEBUG) ? 100. : 1.) * SDL_JoystickGetAxis(_joystick, 0) / (.5 * 65536.) );

        _gController.scene().player().moveForward(
                ((cfg::DEBUG) ? 100. : 1.) * -SDL_JoystickGetAxis(_joystick, 1) / (.5 * 65536.) );

        _gController.scene().player().moveUpward(
                ((cfg::DEBUG) ? 100. : 1.) * -SDL_JoystickGetAxis(_joystick, 2) / (.5 * 65536.) );

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
    switch (e.key.keysym.sym) {
        case SDLK_p:
            if (cfg::DEBUG) cout << "pos: " << _gController.scene().player().prs().pos() << endl;
            break;
        default:
            break;
    }
}


void Game::handleMouseBtn(SDL_Event e)
{
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
    if(e.wheel.y != 0)
        _gController.renderer().camera().zoomIn(-.01f * e.wheel.y);
}


void Game::handleJoyBtnDown(SDL_Event e)
{
    switch (e.jbutton.button) {
        default:
            break;
    }
}


void Game::initJoystick()
{
    if (SDL_NumJoysticks() == 0) {
        if (cfg::DEBUG) cout << "No joystick detected" << endl << endl;
        return;
    }

    _joystick = SDL_JoystickOpen(0);

    if (!_joystick) {
        if (cfg::DEBUG) cerr << "Joystick detected but unable to open it" << endl << endl;
        return;
    }

    if (cfg::DEBUG) cout << "[Game::initJoystick] name: "
            << SDL_JoystickName(_joystick) << endl
            << "[Game::initJoystick] # of axes:    " << SDL_JoystickNumAxes(_joystick) << endl
            << "[Game::initJoystick] # of hats:    " << SDL_JoystickNumHats(_joystick) << endl
            << "[Game::initJoystick] # of buttons: " << SDL_JoystickNumButtons(_joystick) << endl
            << "[Game::initJoystick] # of balls:   " << SDL_JoystickNumBalls(_joystick) << endl << endl;
}

}
