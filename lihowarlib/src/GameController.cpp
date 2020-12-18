#include <lihowarlib/GameController.hpp>
#include <lihowarlib/programs/MultiLightsProgram.hpp>
#include <lihowarlib/Skybox.hpp>
#include <lihowarlib/LightPoint.hpp>
#include <lihowarlib/LightDirectional.hpp>

#include <glimac/Sphere.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

GameController::GameController()
    : _assetManager(AssetManager::instance()),
      _gRenderer(GameRenderer::instance()),
      _scene(new Scene())
{

    _scene->add(new GameObject(
        *_assetManager.meshes()[MeshName::BALLOON]  ));

    _scene->add(new GameObject(
        *_assetManager.meshes()[MeshName::ISLAND1],
        0, //_assetManager.textureId(TextureName::MOON),
        GameObject::PRS( glm::vec3(70., -40., 0.),
             glm::vec3(0., -195., 0.)   )));

    _scene->add(new GameObject(
        *_assetManager.meshes()[MeshName::ISLAND1],
        0, //_assetManager.textureId(TextureName::MOON),
        GameObject::PRS(
            glm::vec3(180., -40., -50.),
            glm::vec3(0., 72., 0.)   )));

    _scene->add(new LightPoint(
            glm::vec3(.25, .15, .1), glm::vec3(0., 1., 0.)) );

    _scene->add(new LightDirectional(
            glm::vec3(.95, .85, .83), glm::vec3(0., .8, -1.)) );

    _scene->add(new LightDirectional(
            glm::vec3(.61, .48, .41), glm::vec3(0., -1., 0.)) );

    _scene->add(new LightDirectional(
            glm::vec3(.21, .18, .11), glm::vec3(.5, .4, .5)) );

    _scene->add(new LightDirectional(
            glm::vec3(.21, .18, .11), glm::vec3(-.5, .4, .5)) );

    SceneSerializer::save(*_scene);

    //if (DEBUG) cout << "[GameController::GameController] END" << endl;
}


void GameController::render()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*LightPoint *lp = dynamic_cast<LightPoint*>(_scene->lights().front().get());
    lp->pos() = glm::vec3(0., -1., 0.);*/

    GameObject &skybox = *_scene->skybox();
    skybox.program().use();
    _gRenderer.updateMatMV(skybox.matModel());
    _gRenderer.bindUniformVariables(skybox, *_scene);
    skybox.render();

    auto it = _scene->gObjects().begin();
    while (it != _scene->gObjects().end()) {
        GameObject &g = **it;
        g.program().use();
        _gRenderer.updateMatMV(g.matModel());
        _gRenderer.bindUniformVariables(g, *_scene);
        g.render();
        ++it;
        //if (DEBUG) cout << "\n---------------------- NEXT OBJECT\n" << endl;
    }

    //if (DEBUG) cout << "\n====================== NEXT FRAME\n\n" << endl;
}

}
