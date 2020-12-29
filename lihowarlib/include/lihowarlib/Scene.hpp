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
#ifndef LIHOWAR_SCENE_HPP
#define LIHOWAR_SCENE_HPP

#include <list>
#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/Object.hpp>
#include <lihowarlib/Light.hpp>
#include <lihowarlib/objects/Skybox.hpp>
#include <lihowarlib/objects/Player.hpp>
#include <lihowarlib/objects/Island.hpp>

namespace lihowar {

class Scene {

private:
    // MEMBERS
    std::vector< std::unique_ptr<Island> > _islands;
    std::list< std::unique_ptr<Object> > _objects;
    std::list< std::unique_ptr<Light> > _lights;
    std::unique_ptr<Skybox> _skybox;
    std::unique_ptr<Player> _player;
    std::unique_ptr<Light> _lightAmbient;

public:
    // CONSTRUCTORS & DESTRUCTORS
    Scene()
       :_skybox( std::unique_ptr<Skybox>(new Skybox()) ),
        _player( std::unique_ptr<Player>(new Player()) ),
        _lightAmbient( std::unique_ptr<Light>( new Light(_skybox->ambientColor()) ) )
   {}

    ~Scene() = default;

public:
    // INTERFACE
    std::vector< std::unique_ptr<Island> > &islands() { return _islands; }
    const std::vector< std::unique_ptr<Island> > &islands() const { return _islands; }

    std::list< std::unique_ptr<Object> > &objects() { return _objects; }
    const std::list< std::unique_ptr<Object> > &objects() const { return _objects; }

    std::list< std::unique_ptr<Light> > &lights() { return _lights; }
    const std::list< std::unique_ptr<Light> > &lights() const { return _lights; }

    Skybox &skybox() { return *_skybox; }
    Skybox &skybox() const { return *_skybox; }

    Player &player() { return *_player; }
    Player &player() const { return *_player; }

    Light &lightAmbient() { return *_lightAmbient; }
    Light &lightAmbient() const { return *_lightAmbient; }

    void add(std::unique_ptr<Island> island) { _islands.push_back(std::move(island)); }
    void add(Island *island) { _islands.push_back(std::unique_ptr<Island>(island)); }

    void add(std::unique_ptr<Object> object) { _objects.push_back(std::move(object)); }
    void add(Object *object) { _objects.push_back(std::unique_ptr<Object>(object)); }

    void add(std::unique_ptr<Light> light) { _lights.push_back(std::move(light)); }
    void add(Light *light) { _lights.push_back(std::unique_ptr<Light>(light)); }

};

}


#endif //LIHOWAR_SCENE_HPP
