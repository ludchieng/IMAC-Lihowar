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

/**
 * @brief Represents a game scene
 *
 * A game scene contains the game objects that may appear on the screen
 * and the game entities which may have an effect on the rendering
 */
class Scene {

private:
    // MEMBERS

    /**
     * @brief Vector of island game objects
     */
    std::vector< std::unique_ptr<Island> > _islands;

    /**
     * @brief List of "other" game objects
     */
    std::list< std::unique_ptr<Object> > _objects;

    /**
     * @brief List of light game entities
     */
    std::list< std::unique_ptr<Light> > _lights;

    /**
     * @brief Pointer to the Skybox game object
     */
    std::unique_ptr<Skybox> _skybox;

    /**
     * @brief Pointer to Player game object
     */
    std::unique_ptr<Player> _player;

    /**
     * @brief Pointer to the ambient light
     */
    std::unique_ptr<Light> _lightAmbient;

public:
    // CONSTRUCTORS & DESTRUCTORS

    /**
     * @brief Scene class constructor
     */
    Scene()
       :_skybox( std::unique_ptr<Skybox>(new Skybox()) ),
        _player( std::unique_ptr<Player>(new Player()) ),
        _lightAmbient( std::unique_ptr<Light>( new Light(_skybox->ambientColor()) ) )
   {}

   /**
    * @brief Scene class destructor
    */
    ~Scene() = default;

public:
    // INTERFACE

    /**
     * @brief Gets the vector of Island game objects
     * @return Returns the vector of Island game objects
     */
    std::vector< std::unique_ptr<Island> > &islands() { return _islands; }
    const std::vector< std::unique_ptr<Island> > &islands() const { return _islands; }

    /**
     * @brief Gets the list of "other" game objects
     * @return Returns the list of "other" game objects
     */
    std::list< std::unique_ptr<Object> > &objects() { return _objects; }
    const std::list< std::unique_ptr<Object> > &objects() const { return _objects; }

    /**
     * @brief Gets the list of light game entities
     * @return Returns the list of light game entities
     */
    std::list< std::unique_ptr<Light> > &lights() { return _lights; }
    const std::list< std::unique_ptr<Light> > &lights() const { return _lights; }


    /**
     * @brief Gets the skybox game object
     * @return Returns the skybox game object
     */
    Skybox &skybox() { return *_skybox; }
    Skybox &skybox() const { return *_skybox; }

    /**
     * @brief Gets the player game object
     * @return Returns the player game object
     */
    Player &player() { return *_player; }
    Player &player() const { return *_player; }

    /**
     * @brief Gets the ambient light game entity
     * @return Returns the ambient light game entity
     */
    Light &lightAmbient() { return *_lightAmbient; }
    Light &lightAmbient() const { return *_lightAmbient; }

    /**
     * @brief Adds an Island game object to the scene
     * @param island  Island game object to add
     */
    void add(std::unique_ptr<Island> island) { _islands.push_back(std::move(island)); }
    void add(Island *island) { _islands.push_back(std::unique_ptr<Island>(island)); }

    /**
     * @brief Adds an Object game object to the scene as "other" game objects
     * @param object  Object game object to add as "other" game objects
     */
    void add(std::unique_ptr<Object> object) { _objects.push_back(std::move(object)); }
    void add(Object *object) { _objects.push_back(std::unique_ptr<Object>(object)); }

    /**
     * @brief Adds an Light game object to the scene
     * @param light  Light game object to add
     */
    void add(std::unique_ptr<Light> light) { _lights.push_back(std::move(light)); }
    void add(Light *light) { _lights.push_back(std::unique_ptr<Light>(light)); }


    /**
     * @brief Traverses recursively the scene's game objects to find
     * all the instances of a given Object sub-class
     * @tparam T  Sub-class we are looking for
     * @return  Returns a list of sub-objects that matches the
     * requested sub-class
     */
    template<typename T>
    std::list<std::shared_ptr<T>> &findAll() {
        auto res = new std::list<std::shared_ptr<T>>();

        // Find all in the collection of islands game objects
        auto itIslands = _islands.begin();
        while (itIslands != _islands.end()) {
            // call findAll on subobjects and concatenate lists
            res->splice(res->end(), (**itIslands).findAll<T>());
            ++itIslands;
        }

        // Find all in the "other" game objects collection
        auto itObjects = _objects.begin();
        while (itObjects != _objects.end()) {
            // call findAll on subobjects and concatenate lists
            res->splice(res->end(), (**itObjects).findAll<T>());
            ++itObjects;
        }
        return *res;
    }

};

}


#endif //LIHOWAR_SCENE_HPP
