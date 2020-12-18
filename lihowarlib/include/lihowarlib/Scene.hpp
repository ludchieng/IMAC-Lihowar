#ifndef LIHOWAR_SCENE_HPP
#define LIHOWAR_SCENE_HPP

#include <list>
#include <lihowarlib/common.hpp>
#include <lihowarlib/GameObject.hpp>
#include <lihowarlib/Light.hpp>
#include <lihowarlib/Skybox.hpp>

namespace lihowar {

class Scene {

private:
    // MEMBERS
    std::list< std::unique_ptr<GameObject> > _gObjects;
    std::list< std::unique_ptr<Light> > _lights;
    std::unique_ptr<Skybox> _skybox;
    std::unique_ptr<Light> _lightAmbient;

public:
    // CONSTRUCTORS & DESTRUCTORS
    Scene()
       :_skybox( std::unique_ptr<Skybox>(new Skybox()) ),
        _lightAmbient( std::unique_ptr<Light>( new Light(_skybox->ambientColor()) ) )
   {}

    ~Scene() = default;

public:
    // INTERFACE
    std::list< std::unique_ptr<GameObject> > &gObjects() { return _gObjects; }
    const std::list< std::unique_ptr<GameObject> > &gObjects() const { return _gObjects; }

    std::list< std::unique_ptr<Light> > &lights() { return _lights; }
    const std::list< std::unique_ptr<Light> > &lights() const { return _lights; }

    Skybox *skybox() { return _skybox.get(); }
    Skybox *skybox() const { return _skybox.get(); }

    Light *lightAmbient() { return _lightAmbient.get(); }
    Light *lightAmbient() const { return _lightAmbient.get(); }

    void add(std::unique_ptr<GameObject> gObject) { _gObjects.push_back(std::move(gObject)); }
    void add(std::unique_ptr<Light> light) { _lights.push_back(std::move(light)); }
    void add(GameObject *gObject) { _gObjects.push_back(std::unique_ptr<GameObject>(gObject)); }
    void add(Light *light) { _lights.push_back(std::unique_ptr<Light>(light)); }

};

}


#endif //LIHOWAR_SCENE_HPP
