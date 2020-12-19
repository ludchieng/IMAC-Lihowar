#ifndef LIHOWAR_SCENE_HPP
#define LIHOWAR_SCENE_HPP

#include <list>
#include <lihowarlib/common.hpp>
#include <lihowarlib/Object.hpp>
#include <lihowarlib/Light.hpp>
#include <lihowarlib/Skybox.hpp>
#include <lihowarlib/Player.hpp>

namespace lihowar {

class Scene {

private:
    // MEMBERS
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
    std::list< std::unique_ptr<Object> > &objects() { return _objects; }
    const std::list< std::unique_ptr<Object> > &objects() const { return _objects; }

    std::list< std::unique_ptr<Light> > &lights() { return _lights; }
    const std::list< std::unique_ptr<Light> > &lights() const { return _lights; }

    Skybox *skybox() { return _skybox.get(); }
    Skybox *skybox() const { return _skybox.get(); }

    Player *player() { return _player.get(); }
    Player *player() const { return _player.get(); }

    Light *lightAmbient() { return _lightAmbient.get(); }
    Light *lightAmbient() const { return _lightAmbient.get(); }

    void add(std::unique_ptr<Object> object) { _objects.push_back(std::move(object)); }
    void add(std::unique_ptr<Light> light) { _lights.push_back(std::move(light)); }
    void add(Object *object) { _objects.push_back(std::unique_ptr<Object>(object)); }
    void add(Light *light) { _lights.push_back(std::unique_ptr<Light>(light)); }

};

}


#endif //LIHOWAR_SCENE_HPP
