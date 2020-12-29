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
#ifndef LIHOWAR_GAMECONTROLLER_HPP
#define LIHOWAR_GAMECONTROLLER_HPP

#include <list>
#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/GameRenderer.hpp>
#include <lihowarlib/Scene.hpp>
#include <lihowarlib/io/SceneSerializer.hpp>


namespace lihowar {

class GameController {

private:
    // MEMBERS
    std::unique_ptr<Scene> _scene;
    GameRenderer &_gRenderer;

private:
    // CONSTRUCTORS & DESTRUCTORS
    GameController();

    ~GameController() = default;

public:
    /// \brief get instance of the GameController singleton class
    static GameController& instance() {
        static GameController instance;
        return instance;
    }
    // prevent instance duplication
    GameController(const GameController&) = delete;
    GameController(GameController&&) = delete;
    GameController& operator=(const GameController&) = delete;
    GameController& operator=(GameController&&) = delete;

public:
    // INTERFACE
    Scene &scene() { return *_scene; }
    GameRenderer& renderer() { return _gRenderer; }

    void update();
    void render() { _gRenderer.render(*_scene); }

};

}


#endif //LIHOWAR_GAMECONTROLLER_HPP
