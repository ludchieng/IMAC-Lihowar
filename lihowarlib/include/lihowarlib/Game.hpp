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
#pragma once
#ifndef LIHOWAR_GAME_HPP
#define LIHOWAR_GAME_HPP

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glimac/SDLWindowManager.hpp>
#include <lihowarlib/GameController.hpp>

namespace lihowar {

/**
 * @brief Singleton class to manage the Game high-level processing
 */
class Game {

private:
    // MEMBERS

    /**
     * @brief Asserts that the game should still be running
     * on the next loop iteration
     */
    bool _isRunning = true;

    /**
     * @brief Reference to the GameController instance
     */
    GameController &_gController;

    /**
     * @brief Reference to the glimac window instance
     */
    glimac::SDLWindowManager &_window;

    /**
     * @brief Reference to the SDL joystick instance
     */
    SDL_Joystick *_joystick;

private: // singleton
    // CONSTRUCTORS & DESTRUCTORS

    /**
     * Game class constructor
     * @param wm Window manager
     */
    explicit Game(glimac::SDLWindowManager &wm);

    /**
     * Game class default destructor
     */
    ~Game() = default;

public:
    /// \brief get instance of the Game singleton class
    static Game& instance(glimac::SDLWindowManager &wm) {
        static Game instance(wm);
        return instance;
    }
    // prevent instance duplication
    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

public:
    // INTERFACE

    /**
     * @brief Asserts that the game should still be running
     * on the next loop iteration
     * @return Returns true if the game should still be
     * running on the next loop iteration, false otherwise
     */
    bool isRunning() const { return _isRunning; }

    /**
     * @brief Asserts that the joystick is initialized in
     * the SDL context
     * @return Returns true if the joystick is initialized
     * in the SDL context
     */
    bool isJoystickOpened() const { return _joystick; }

    /**
     * @brief Updates state of the game
     */
    void update();

    /**
     * @brief Renders the current image frame for this loop iteration
     */
    void render() { _gController.render(); };

    /**
     * @brief Handles the given SDL event
     * @param event  SDL event to handle
     */
    void handle(SDL_Event event);

private:
    void handleKeydown(SDL_Event event);
    void handleMouseBtn(SDL_Event event);
    void handleMouseMotion(SDL_Event event);
    void handleMouseWheel(SDL_Event event);
    void handleJoyBtnDown(SDL_Event event);
    void initJoystick();
};

}


#endif //LIHOWAR_GAME_HPP
