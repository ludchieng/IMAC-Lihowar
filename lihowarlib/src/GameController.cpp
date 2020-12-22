#include <lihowarlib/GameController.hpp>
#include <lihowarlib/LightPoint.hpp>
#include <lihowarlib/LightDirectional.hpp>
#include <lihowarlib/ObjectDynamic.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

GameController::GameController()
    : _scene(new Scene()),
      _assetManager(AssetManager::instance()),
      _gRenderer(GameRenderer::instance(_scene->player().prs().pos()))
{

    _scene->add(new Object(
            *_assetManager.meshes()[MeshName::CUBE],
            _assetManager.NO_TEXTURE,
            Object::PRS(
                    glm::vec3(0., -1.5, 0.),
                    glm::vec3(0.),
                    glm::vec3(.5))) );

    _scene->add(new Object(
            *_assetManager.meshes()[MeshName::ISLAND1],
            _assetManager.NO_TEXTURE,
            Object::PRS(
                    glm::vec3(70., -40., 0.),
                    glm::vec3(0., -195., 0.))) );

    _scene->add(new Object(
            *_assetManager.meshes()[MeshName::ISLAND1],
            _assetManager.NO_TEXTURE,
            Object::PRS(
                    glm::vec3(180., -40., -50.),
                    glm::vec3(0., 72., 0.))) );

    _scene->add(new LightPoint(
            glm::vec3(.25, .15, .1),
            _scene->player().prs().pos(),
            glm::vec3(0., 1., 0.)) );

    _scene->add(new LightDirectional(
            glm::vec3(.95, .85, .83), glm::vec3(0., -.8, 1.)) );

    _scene->add(new LightDirectional(
            glm::vec3(.21, .18, .13), glm::vec3(0., 1., 0.)) );


    /*_scene->player().add(new ObjectDynamic(
            *AssetManager::instance().meshes()[MeshName::CUBE],
            _assetManager.NO_TEXTURE,
            Object::PRS( glm::vec3(4.))) );*/

    SceneSerializer::save(*_scene);

    if (DEBUG) cout << "[GameController::GameController] END" << endl;
}


void GameController::update()
{
    _scene->skybox().setCenter(_gRenderer.camera().target());
    //_scene->player().translate( glm::vec3(0., 0., .05) );
    //_scene->player().applyForce( glm::vec3(0., 1., 0.) );
    //_scene->player().applyTorque( glm::vec3(0., 1., 0.) );
    _scene->player().applyTorque( glm::vec3(0., 0.0001, 0.) );
    _scene->player().update();
    auto it = _scene->objects().begin();
    while(it != _scene->objects().end()) {
        (**it).update();
        ++it;
    }
}

}
