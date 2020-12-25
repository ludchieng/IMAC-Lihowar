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
