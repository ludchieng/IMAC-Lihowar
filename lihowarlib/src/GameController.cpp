#include <lihowarlib/GameController.hpp>
#include <lihowarlib/LightPoint.hpp>
#include <lihowarlib/LightDirectional.hpp>
#include <lihowarlib/ObjectDynamic.hpp>
#include <lihowarlib/objects/Island.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

GameController::GameController()
    : _scene(new Scene()),
      _assetManager(AssetManager::instance()),
      _gRenderer(GameRenderer::instance(_scene->player().prs()))
{

    _scene->add(new Object(
            *_assetManager.meshes()[MeshName::CUBE],
            _assetManager.NO_TEXTURE,
            Object::PRS(
                    glm::vec3(0., -1.5, 0.),
                    glm::vec3(0.),
                    glm::vec3(.5))) );

    _scene->add(new Island(
            *_assetManager.meshes()[MeshName::ISLAND1],
            _assetManager.NO_TEXTURE,
            Object::PRS(
                    glm::vec3(70., -40., 0.),
                    glm::vec3(0., 0., 0.),
                    glm::vec3(2.))) );

    _scene->islands()[0]->add(new Object(
            *_assetManager.meshes()[MeshName::BEACON1],
            _assetManager.textureId(TextureName::BEACON1_DIFF),
            Object::PRS(
                    glm::vec3(-5.621, 28.893, 5.174),
                    glm::vec3(180., 0., 0.),
                    glm::vec3(2.))) );

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
    auto test = _scene->objects().begin()->get();
    test->prs().rot() += glm::vec3(1., 0., 0.);
    _scene->skybox().setCenter(_gRenderer.camera().targetPRS().pos());
    _scene->player().update();
    auto it = _scene->islands().begin();
    while(it != _scene->islands().end()) {
        (**it).update();
        ++it;
    }
}

}
